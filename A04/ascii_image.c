#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

/*  assigns as ASCII character based on the intensity */
char find_char (int avg_int){
  if (avg_int >=0 && avg_int <= 25){
    return'@';
  }
  if (avg_int>=26 && avg_int <= 50){
    return '#';
  }
  if(avg_int >=51 && avg_int <= 75){
    return '%';
  }
  if(avg_int>76 && avg_int <=100){
    return '*';
  }
  if(avg_int>=101 && avg_int <= 125){
    return 'o';
  }
  if(avg_int>126 && avg_int <= 150){
    return ';';
  }
  if(avg_int>151 && avg_int <= 175){
    return ':';
  }
  if(avg_int>176 && avg_int <= 200){
    return ',';
  }
  if(avg_int>201 && avg_int <= 225){
    return '.';
  }
  else {
  return ' ';
  }
}



int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: ascii_image <file.ppm>\n");
    return 0;
  }

  int intensity;
  int w;
  int h;

  struct ppm_pixel* array;
  array = read_ppm( argv[1], &w, &h);
  if(array == NULL){
    printf("Error, not a valid file\n");
    exit(0);
  }

  printf("Reading %s with width %d and heigth %d\n", argv[1], w, h);
  char c;
  
  for (int i = 0; i<h; i++){
    for(int j= 0 ; j< w; j++){
    intensity = (array[i*w +j].red+ array[i*w +j].green + array[i*w +j].blue)/3;  //calculates for intensity I=(R+G+B)/3
    c = find_char(intensity);
    printf(" %c", c);
  }
  printf("\n");
}
  
free(array);
return 0;
}

