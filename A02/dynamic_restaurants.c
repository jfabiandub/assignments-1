#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* creates a struct that holds the information for a restaurant */
struct restaurant{
  char name[100];
  int op_hour;
  int cl_hour;
  float star_rat;
};

int main() {

  struct restaurant * arr_restaurant;
  char name[32];   //gets the name of restaurant
  int num_rest;  //number of rest input by the user

  
  printf("Enter a number of restaurants: ");
  scanf("%d", &num_rest );

  arr_restaurant = malloc(sizeof( struct restaurant)*num_rest);  //allocates space for the new array
  for(int i= 0; i< num_rest; i++ ){ 
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", name);
    strcpy(arr_restaurant[i].name, name);

    printf("Open time: ");
    scanf(" %d%*c", &arr_restaurant[i].op_hour);
 
    printf("Close time: ");
    scanf(" %d%*c", &arr_restaurant[i].cl_hour);

    printf("Stars: ");
    scanf("%e", &arr_restaurant[i].star_rat); 
  }

  printf("Welcome to Jenii's Restaurant Directory\n");

  for(int i=0; i< num_rest; i++){
    printf("%d) %-20s\topen: %02d:00\tclose: %02d:00\tstars: %0.1f\n",i, 
    arr_restaurant[i].name,
    arr_restaurant[i].op_hour,
    arr_restaurant[i].cl_hour,
    arr_restaurant[i].star_rat);
  }

  free(arr_restaurant);  //frees the space
  return 0;

}
