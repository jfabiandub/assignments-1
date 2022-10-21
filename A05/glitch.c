#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <time.h>
#include "read_ppm.h"
#include "write_ppm.h"
//v//oid clean(struct ppm_pixel* image, int w, int h){
  //for(int i =0; i<h; i++){
    //free(image);
  //}
  //free(image);
//}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: glitch <file.ppm>\n");
    return 0;
  }
  
  //srand(time(0));
  int w;
  int h;

  char* filename = argv[1];
  struct ppm_pixel* pixels;
  pixels = read_ppm(filename, &w, &h);
  printf("%d\n", h);
  if(pixels == NULL){
    printf("Error, not a valid file\n");
    exit(0);
  }
  printf("Reading %s with width %d and heigth %d\n", filename, w, h);

  for(int i = 0; i< h; i++){
    for (int j= 0; j<w; j++){
      struct ppm_pixel p = pixels[i*w +j];
      p.red= p.red << (rand() % 2);
      p.green = p.blue << (rand() % 2);
      p.blue = p.green<< (rand() % 2);
      pixels[i*w +j]=p;
    }
  }

char* new_fp = malloc(strlen(filename)+8); //this should save the new file with the new name
 strcpy(new_fp, filename);
 new_fp[strlen(new_fp)-4] = '\0';
 strcat(new_fp, "-glitch.ppm");
 printf("Writing file %s\n", new_fp);
 

  //printf("Reading %s with width %d and heigth %d\n", argv[1], w, h);
  write_ppm(new_fp, pixels,w, h);
  
  free(pixels);
  //pixels = read_ppm(new_fp, &w, &h);
 // printf("Writing file %s", new_fp);


 //fclose(filename);
 //clean(pixels, w, h);

  free(new_fp);

  return 0;
}

