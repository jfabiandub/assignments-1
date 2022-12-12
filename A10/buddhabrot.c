#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

pthread_mutex_t mutex;
pthread_barrier_t barrier;

struct thread_data{
struct ppm_pixel *pixels;
struct ppm_pixel *palette;
int start_col;
int end_col;
int start_row;
int end_row;
int size;
int maxIterations;
float xmin;
float ymin;
float xmax;
float ymax;
int id;
int *membership;
int *count;
int maxCount;
};


void *compute_mandelbrot(void *userdata){
struct thread_data *data = (struct thread_data *)userdata;
  for(int i = data->start_row; i<data->end_row; i++){
    for(int j = data->start_col; j<data->end_col; j++){
      float xfrac = ((float) (j))/data->size;
      float yfrac = ((float) (i))/data->size;
      float x0 = data->xmin  + xfrac * (data->xmax - data->xmin );
      float y0 = data->ymin  + yfrac * (data->ymax - data->ymin );
    
      float x = 0.0;
      float y = 0.0;
      int iter = 0;
      while (iter < data->maxIterations && x*x + y*y < 2*2){
      float xtmp = x*x - y*y + x0;
      y = 2*x*y + y0;
      x = xtmp;
      iter++;
      }
      if(iter < data->maxIterations){//escaped
        data->membership[i *data->size + j] = 0; // sets to false
      } 
      else{
        data->membership[i * data->size + j] = 1;  //sets to true
      }
    }
  }
return (void*) NULL;
}

void *compute_counts(void *userdata){
  struct thread_data *data = (struct thread_data *)userdata;
  for(int i = data->start_row; i<data->end_row; i++){
    for(int j = data->start_col; j<data->end_col; j++){
      if(data->membership[i *data->size +j] ==1){
        continue;
      }
      else{
        float xfrac = ((float) (j))/data->size;
        float yfrac = ((float) (i))/data->size;
        float x0 = data->xmin  + xfrac * (data->xmax - data->xmin );
        float y0 = data->ymin  + yfrac * (data->ymax - data->ymin );
        
        float x = 0.0;
        float y = 0.0;

        while( x*x + y*y < 2*2){
          float xtmp = x*x - y*y + x0;
          y = 2*x*y + y0;
          x = xtmp;

          int y_row = round(data->size * (y- data->ymin)/(data->ymax - data->ymin));
          int x_col = round(data->size * (x - data->xmin)/(data->xmax - data->xmin));
          if(y_row <0 || y_row >= data->size) {
            continue; //out of range
          }
          if (x_col<0 || x_col >= data->size) {
            continue; //out of range
          }
          pthread_mutex_lock(&mutex);
          data->count[y_row * data->size + x_col]++;
          if(data->count[y_row * data->size + x_col] > data->maxCount){
            data->maxCount = data->count[y_row * data->size + x_col];
          }
          pthread_mutex_unlock(&mutex);
        }
      }   
    }
  }
  return (void*) NULL;
}

void *compute_colors(void *userdata){
  struct thread_data *data = (struct thread_data *)userdata;
  float gamma = 0.681;
  float factor = 1.0/gamma;
  for(int i = data->start_row; i<data->end_row; i++){
    for(int j = data->start_col; j<data->end_col; j++){
      float value = 0;

      if(data->count[i * data->size + j] > 0){
        value = log(data->count[i* data->size + j]) / log(data->maxCount);
        value = pow(value, factor);
      }
      data->pixels[i* data->size + j].red = value *255;
      data->pixels[i * data->size + j].green = value * 255;
      data->pixels[i* data->size + j].blue = value * 255;
    }
  }
  printf("Thread %d) finished\n", data->id);
  return (void*) NULL;
}


void *start(void * data){
  compute_mandelbrot(data);
  compute_counts(data);
  pthread_barrier_wait(&barrier);  //wait for all threads to finish
  compute_colors(data);
  return (void*) NULL;
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

  // todo: your code here
  // compute image
   srand(time(0));

  /*  allocate memory for palette*/
  struct ppm_pixel *palette = malloc(sizeof(struct ppm_pixel)* maxIterations);
  for(int i=0; i<maxIterations; i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() %255;
    palette[i].blue = rand()% 255;
  }

  /* allocates memory for pixels*/
  struct ppm_pixel *pixels = malloc(sizeof(struct ppm_pixel)* size * size);

  int *membership = malloc(sizeof(int)* size *size);

  int *count = malloc(sizeof(int)*size * size);
  for(int i= 0; i<size*size; i++){
    count[i]=0;
  }

  /* creates timer to calculate the number of seconds needed to compute the image */
  double timer;
  struct timeval tstart, tend; 
  gettimeofday(&tstart, NULL);

  pthread_t threads[4];
  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barrier, NULL, 4);
  struct thread_data data_array[4];

/*  for loop that goes through the 4 threads */
  for (int i=0; i<4; i++){
    if(i ==0){
      printf("Thread %d) Sub-image block: cols (0, 240) to rows (0,240)\n", i);
      data_array[i].id = i;
      data_array[i].pixels = pixels;
      data_array[i].start_col = 0;
      data_array[i].end_col = 240;
      data_array[i].start_row = 0;
      data_array[i].end_row = 240;
      data_array[i].palette = palette;
      data_array[i].size = size;
      data_array[i].maxIterations = maxIterations;
      data_array[i].xmin = xmin;
      data_array[i].ymin = ymin;
      data_array[i].xmax = xmax;
      data_array[i].ymax = ymax;
      data_array[i].membership = membership;
      data_array[i].count = count;
      data_array[i].maxCount = 0;
      pthread_create(&threads[i], NULL, start, (void*) &data_array[i]);
    }
    else if(i==1){
      printf("Thread %d) Sub-image block: cols (240, 280) to rows (0,240)\n", i);
      data_array[i].id = i;
      data_array[i].pixels = pixels;
      data_array[i].start_col = 240;
      data_array[i].end_col = 480;
      data_array[i].start_row = 0;
      data_array[i].end_row = 240;
      data_array[i].palette = palette;
      data_array[i].size = size;
      data_array[i].maxIterations = maxIterations;
      data_array[i].xmin = xmin;
      data_array[i].ymin = ymin;
      data_array[i].xmax = xmax;
      data_array[i].ymax = ymax;
      data_array[i].membership = membership;
      data_array[i].count = count;
      data_array[i].maxCount = 0;
      pthread_create(&threads[i], NULL, start, (void*) &data_array[i]);
    }
    else if (i ==2){
      printf("Thread %d) Sub-image block: cols (0, 240) to rows (240,480)\n", i);
      data_array[i].id = i;
      data_array[i].pixels = pixels;
      data_array[i].start_col = 0;
      data_array[i].end_col = 240;
      data_array[i].start_row = 240;
      data_array[i].end_row = 480;
      data_array[i].palette = palette;
      data_array[i].size = size;
      data_array[i].maxIterations = maxIterations;
      data_array[i].xmin = xmin;
      data_array[i].ymin = ymin;
      data_array[i].xmax = xmax;
      data_array[i].ymax = ymax;
      data_array[i].membership = membership;
      data_array[i].count = count;
      data_array[i].maxCount = 0;
      pthread_create(&threads[i], NULL, start, (void*) &data_array[i]);
    }
    else if (i ==3){
      printf("Thread %d) Sub-image block: cols (240, 480) to rows (240,480)\n", i);
      data_array[i].id = i;
      data_array[i].pixels = pixels;
      data_array[i].start_col = 240;
      data_array[i].end_col = 480;
      data_array[i].start_row = 240;
      data_array[i].end_row = 480;
      data_array[i].palette = palette;
      data_array[i].size = size;
      data_array[i].maxIterations = maxIterations;
      data_array[i].xmin = xmin;
      data_array[i].ymin = ymin;
      data_array[i].xmax = xmax;
      data_array[i].ymax = ymax;
      data_array[i].membership = membership;
      data_array[i].count = count;
      data_array[i].maxCount = 0;
      pthread_create(&threads[i], NULL, start, (void*) &data_array[i]);
      }
    }

    for (int i = 0; i<4; i++){
      pthread_join(threads[i], NULL);
    }

  gettimeofday(&tend, NULL);

  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec-tstart.tv_usec)/1.e6;
  int timestamp = time(0);
  printf("Computed buddhabrot set (%dx%d) in %f seconds\n", size, size,timer);

  /* outputs the file with the image */
    char fp[100];
    sprintf(fp, "buddhabrot-%d-%d.ppm", size, timestamp);
    printf("Writing file: %s\n", fp);
    write_ppm(fp, pixels, size, size);


    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);
    free(pixels);
    free(palette);
    free(membership);
    free(count);

}




