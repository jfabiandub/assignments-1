#include <stdio.h>


int max_val(int v, int d[4][4]){  //for loop that gets the largest value
  for(int i=0; i<4;i++){
    for(int j=0; j< 4; j++)
    if(v <(d[i][j]))
      v = d[i][j];
    //return 1;
  }
  return 0;
}

int main() {
  
  int matrix[4][4];
  int val;
  int largest;
  int sum;

  int i, j;        
  for(i=0;  i< 4; i++){          //for loop to read each value and assign it into the matrix
    for(j =0; j< 4; j++){   
     scanf("%d", &val);     
      matrix[i][j]= val;
    }
  }
  for (int i = 0; i< 4; i++){     //for loop that goes through each row
      int j;
      for (j = 0; j <4; j++){       // and column
        val = matrix[i][j];
        if(j < 3 && val == matrix[i][j+1]){   // shift to the right and checks the values
          sum = (val + matrix[i][j+1]);
          if(largest < sum){
            largest = sum;
          }
        }
        if ((j < 3) && (matrix[i][j+1] == 0)){   //condition that checks if the value is a 0
          int temp = j+1;
          while( temp < 3 && matrix[i][temp]==0){
            temp++;
          }
          if((val !=0) && val == matrix[i][temp]){
            sum= (val + matrix[i][temp]);
            if(largest < sum){
              largest = sum;
            }
          }
        }
        if(j >= 1 && val==matrix[i][j-1]){    // shift to the left and checks the values
          sum = (val+matrix[i][j-1]);
          if(largest <sum){
            largest = sum;
          }
        }
        if((j > 0) && (matrix[i][j-1] == 0)){
          int temp = j-1;
          while(temp > 0 && matrix[i][temp] ==0){
            temp--;
          }
          if((val !=0) && val== matrix[i][temp]){
            sum= (val +matrix[i][temp]);
            if(largest< sum){
              largest = sum;
            }
          }
        }
        if(i < 3 && val == matrix[i+1][j]){        // shift up and checks the values
          sum = (val + matrix[i+1][j]);
          if(largest < sum){
            largest = sum;
          }
        }
        if ((i<3) && (matrix[i+1][j] == 0)){   //condition that checks if the value is a 0
          int temp = i+1;
          while(temp < 3 && matrix[temp][j]==0){
            temp++;
          }
          if( (val !=0) && val == matrix[temp][j] ){
            sum= (val + matrix[temp][i]);
            if(largest < sum){
              largest = sum;
            }
          }
        }
        if(i >=1 && val == matrix[i-1][j]){      // shift down and checks the values
          sum = (val + matrix[i-1][j]);
          if(largest < sum){
            largest = sum;
          }
        }
        if ((i>0 )&& (matrix[i -1][j] == 0)){   //condition that checks if the value is a 0
          int temp = i-1;
          while(temp > 0 && matrix[temp][j]==0){
            temp--;
          }
          if((val !=0) && val == matrix[temp][j]){
             sum = (val + matrix[temp][j]);
            if(largest < sum){
              largest = sum;
            }
          }
        }
      }
  }


  if ( max_val(largest, matrix)==0){ 
    printf("The largest value is %d\n", largest);
  }
  return 0;
}

