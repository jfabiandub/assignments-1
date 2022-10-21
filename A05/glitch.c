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
  printf("Reading %s with width %d and heigth %d\n", argv[1], w, h);
/*
  for(int i = 0; i<h; i++){
    for (int j= 0; j<w; j++){
      struct ppm_pixel p = pixels[i*w +j];
      p.red= p.red<< (rand() % 2);
      p.green = p.green << (rand() % 2);
      p.blue = p.blue<< (rand() % 2);
    }
  }

  char* new_fp = malloc(sizeof(char*)+8); //this should save the new file with the new name
//use the crnmpy to copy 
 //strncmp(filename, "-glitch.ppm", 4);
 
//new_fp = d;

  printf("Reading %s with width %d and heigth %d\n", argv[1], w, h);
  write_ppm(new_fp, pixels,w, h);
  
  free(pixels);
  pixels = read_ppm(new_fp, &w, &h);
  printf("Writing file %s", new_fp);


  
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
     p.red= << (rand() % 2);
      oldcolorvalue = p.green;
      oldcolorvalue = p.blue;
      newcolorvalue = oldcolorvalue << (rand() % 2);

      or old_r = p.red 
      old_pr = p.red;
      new_pr = old_pr << (rand() % 2);
    
    }
    //printf("%d", newcolorvalue);
  }
  
 //fclose(filename);
 free(new_fp);
*/
  return 0;
}

