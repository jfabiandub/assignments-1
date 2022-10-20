#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: glitch <file.ppm>\n");
    return 0;
  }

  int w;
  int h;

  char* filename = argv[1];
  struct ppm_pixel* pixels;
  pixels = read_ppm( filename, &w, &h);
  if(pixels == NULL){
    printf("Error, not a valid file\n");
    exit(0);
  }
  char* new_fp = "argv[1]-glitch";  //this should save the new file with the new name
  printf("Reading %s with width %d and heigth %d\n", argv[1], w, h);
  write_ppm(filename,w, h);
  
  //free(pixels);
  //pixels = read_ppm(new_fp, &w, &h);
  //printf("Writing file %s", new_fp);
  
  int newcolorvalue;
  int oldcolorvalue;
  int old_pr=0;
  int old_pg=0;
  int old_pb=0;
  int new_pr = 0;
  int new_pg = 0;
  int new_pb = 0;
  for(int i = 0; i<h; i++){
    for (int j= 0; j<w; j++){
      struct ppm_pixel p = pixels[i*w +j];
      oldcolorvalue = p.red;
      oldcolorvalue = p.green;
      oldcolorvalue = p.blue;
      newcolorvalue = oldcolorvalue << (rand() % 2);

      /* or old_r = p.red 
      old_pr = p.red;
      new_pr = old_pr << (rand() % 2);
      */
    }
    //printf("%d", newcolorvalue);
  }
  //printf("Reading %s with width %d and heigth %d\n", argv[1], w, h);
  //newcolorvalue = oldcolorvalue << (rand() % 2);
  //for loop
  // inside we shift the frame by 1.

  // todo: your code here

  return 0;
}

