#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  int w;
  int h;

  char* fp = argv[1];
  struct ppm_pixel* pixels;
  pixels = read_ppm(fp, &w, &h);  //reads the file, width and height
  printf("%d\n", h);
  if(pixels == NULL){
    printf("Error, not a valid file\n");
    exit(0);
  }
  printf("Reading %s with width %d and heigth %d\n", fp, w, h);

  int max_letter= w*h* 3/8;
  printf("Max number of characters in the image: %d\n", max_letter);
  
  char* secret_message = malloc(sizeof(char)*max_letter +1);
  printf("Enter a phrase: ");
  scanf("%[^\n]%*c", secret_message);

  char* image = (char*)pixels;
  char mask = 0x1;
  for (int i=0; i< (strlen(secret_message)+1)*8; i++){
    char least_bit = secret_message[i/8] & (mask <<(7- i%8));

    least_bit>>= (7 -i%8);
    if(least_bit){
      image[i]= least_bit;
    }
    else{
      least_bit = 0x1;
      least_bit= ~least_bit;
      image[i]&= least_bit;
    }
    
  } 

  char* new_fp = malloc(strlen(fp)+8); //this should save the new file with the new name
 
  /* saves the new file with a new name */
  strcpy(new_fp, fp);
  new_fp[strlen(new_fp)-4] = '\0';
  strcat(new_fp, "-encode.ppm");
  printf("Writing file %s\n", new_fp);

  write_ppm(new_fp, (struct ppm_pixel*) image, w, h);
 // printf("%02s", image);

  free(pixels);
  free(new_fp);

  return 0;
}

