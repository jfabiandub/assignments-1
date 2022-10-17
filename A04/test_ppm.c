#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"



int main() {
  // load feep-raw and print out the grid of pixels
  int w;
  int h;
  
  struct ppm_pixel* image;
  image = read_ppm("feep-raw.ppm", &w, &h); 

  if(image == NULL){
    printf("Error, not a valid file");
    exit(0);
  }
  
  printf("Testing file feep-raw.ppm: %d %d\n ", w, h);

 for( int i = 0; i< h; i++){
    for(int j=0; j< w; j++){
        printf(" %d %d %d",
         image[i*h + j].red,
         image[i*h + j].green,
         image[i*h + j].blue);
        
    }
    printf("\n");
  }
  

  free(image);
  return 0;
}

