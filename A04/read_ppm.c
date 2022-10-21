#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  

  //read PPM files stored in ASCII format. This function should 
  //take a filename as input and return a 2D array of struct pixel


/*returns null if filename is invalid */

  FILE* fp;
  fp = fopen(filename, "rb");   //gets file in binary mode
  if(fp ==NULL){
    printf("Error: unable to open file %s\n", filename);
    //exit (1);
    return NULL;
  }

  char image[100];
  char c[2];

  fgets(image, 100, fp);
  sscanf(image, " %s", c );
  if (c[0]!= 'P' || c[1] != '6'){
    printf("error");
    return NULL;
  }

  fgets(image, 100, fp);
  fgets(image, 100, fp);
  sscanf(image, "%d %d", w, h);
  struct ppm_pixel* array = malloc(sizeof(struct ppm_pixel)* (*w)*(*h));

  if(!array){
    printf("unable to allocate memmory\n");
    return NULL;
  }


 fgets(image, 100, fp);
 fread(array, sizeof(struct ppm_pixel), (*w)*(*h), fp);
  
  fclose(fp);
  //free(fp);
  return array;

  
}
/*
struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}
*/

