#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"
#include "write_ppm.h"

void compute_mandelbrot(struct ppm_pixel *pixels, int start_col , int end_col, int start_row, int end_row, struct ppm_pixel *palette, int size, int maxIterations, float xmin, float ymin, float xmax, float ymax){
for(int i= start_row; i<end_row; i++){
  for(int j=start_col; j<end_col; j++){
    float xfrac = ((float) (j))/size;
    float yfrac = ((float) (i))/size;
    float x0 = xmin + xfrac * (xmax - xmin);
    float y0 = ymin + yfrac * (ymax - ymin);
  
    float x = 0.0;
    float y = 0.0;
    int iter = 0;
    while (iter < maxIterations && x*x + y*y < 2*2){
      float xtmp = x*x - y*y + x0;
      y = 2*x*y + y0;
      x = xtmp;
      iter++;
    }
    if(iter < maxIterations){ //escaped
      pixels[i * size + j] = palette[iter];
    }
    else{
      pixels[i * size + j].red = 0;
      pixels[i * size + j].green = 0;
      pixels[i * size + j].blue = 0;
    }
  }
}
}


int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

int shmid1;
/* created and id for shared memeory  */
shmid1= shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * maxIterations, 0644 | IPC_CREAT);
if (shmid1 == -1) {
  perror("Error: cannot initialize shared memory\n");
  exit(1);
}

/* uses the id to allocate memory for palette*/
struct ppm_pixel *palette = shmat(shmid1, NULL, 0);
for(int i=0; i<maxIterations; i++){
  palette[i].red = rand() % 255;
  palette[i].green = rand() %255;
  palette[i].blue = rand()% 255;
}
/* created and id for shared memeory  */
int shmid;
shmid= shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * size * size, 0644 | IPC_CREAT);
if (shmid == -1) {
  perror("Error: cannot initialize shared memory\n");
  exit(1);
}
/* uses the id to allocate memory for pixels*/
struct ppm_pixel *pixels = shmat(shmid, NULL, 0);
if(pixels ==(void*)-1){
  perror("Error: cannot access shared memory\n");
    exit(1);
}
/* creates timer to calculate the number of seconds needed to compute the image */
double timer;
struct timeval tstart, tend; 
gettimeofday(&tstart, NULL);

/* for loop that cretes the 4 children */
for (int i= 0; i <4; i++){
  fflush(stdout);
  int pid =  fork();
  if (pid == 0){
    if ( i == 0){
      printf("%d)Sub-image block: cols (0, 240) to rows (0,240)\n", getpid());
      fflush(stdout);
      compute_mandelbrot(pixels, 0, 240, 0, 240,  palette, size,maxIterations, xmin, ymin, xmax,  ymax);
    }

    else if(i == 1){
      printf("%d)Sub-image block: cols (240, 480) to rows (0,240)\n", getpid());
      fflush(stdout);
      compute_mandelbrot(pixels, 240, 480, 0, 240,  palette, size,maxIterations, xmin, ymin, xmax,  ymax);
    }

    else if(i == 2){
      printf("%d)Sub-image block: cols (0, 240) to rows (240,480)\n", getpid());
      fflush(stdout);
      compute_mandelbrot(pixels, 0, 240, 240, 480,  palette, size,maxIterations, xmin, ymin, xmax,  ymax);
    }

    else if(i == 3){
      printf("%d)Sub-image block: cols (240, 480) to rows (240,480)\n", getpid()); 
      fflush(stdout);
      compute_mandelbrot(pixels, 240, 480, 240, 480,  palette, size,maxIterations, xmin, ymin, xmax,  ymax);
    }
     exit(0);
  }
  else{
    printf("Launched child process: %d\n", pid);
  }
}
  /* for loop that makes the children process wait for all to finish */
  for (int i = 0; i < 4; i++) {
    int status;
    int pid = wait(&status);
    printf("Child process complete: %d\n", pid);
  }
gettimeofday(&tend, NULL);

timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec-tstart.tv_usec)/1.e6;
int timestamp = time(0);
printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size,timer);

/* outputs the file with the image */
  char fp[100];
  sprintf(fp, "multi-mandelbrot-%d-%d.ppm", size, timestamp);
  printf("Writing file: %s\n", fp);
  write_ppm(fp, pixels, size, size);


/* cleans the shared memory */
  if (shmdt(pixels) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  } 

  if (shmdt(palette) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(shmid1, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  } 
}  


