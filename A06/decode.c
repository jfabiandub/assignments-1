#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include <math.h>


int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w;
  int h;

  char* fp = argv[1];
  struct ppm_pixel* image;
  image = read_ppm(fp, &w, &h);
  if (image == NULL){
    printf("Error, not a valid file\n");
    exit(0);
  }
  printf("Reading %s with width %d and height %d \n", fp, w, h);

int count = w*h*3;
int* array = malloc(sizeof(int)* count); 
 count = 0;
  for (int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      struct ppm_pixel color = image[i*w +j];
       array[count]= color.red%2;
       count++;
       array[count]= color.green%2;
       count++;
       array[count]= color.blue%2;
       count++;
    }
  }
 
  count = (w*h*3)/8;
  printf("Max number of characters in the image: %d\n", count);
  int* secret_message =  malloc(sizeof(int)* count); 
  int d=0;
  
  for(int i=0; i<h*w*3; i+=8){ 
    int total=0;
    total+=array[i]*pow(2,7);
    total+=array[i+1]*pow(2,6);
    total+=array[i+2]*pow(2,5);
    total+=array[i+3]*pow(2,4);
    total+=array[i+4]*pow(2,3);
    total+=array[i+5]*pow(2,2);
    total+=array[i+6]*pow(2,1);
    total+=array[i+7]*pow(2,0);
    secret_message[d]=total;
    if(secret_message[d]==0){
      break;
    }
    else{
      printf("%c", (char) secret_message[d]);
      d++;
    }
  }

  printf("\n");
  free(image);
  free(array);
  free(secret_message);
  return 0;
}

