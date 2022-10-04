#include <stdio.h>

int main() {


float arr[3];
float arr2[3];

  printf("Please enter values for the first vector");
  scanf("%f %f %f", &arr[0], &arr[1], &arr[2]);

  printf("Please enter values for the first vector");
  scanf("%f %f %f", &arr2[0], &arr2[1], &arr2[2]);


float sum = 0;
  for(int i = 0; i< 3; i++){
    sum = arr[i] * arr2[i] + sum;
  }
  if(sum==0){
    printf("dot product is %f", sum);
    printf("the vectors are perpendicular");
  }
  else{
  printf("dot product is %f", sum);
  printf("the vectors are not perpendicular");
  }
  
  return 0;
}
