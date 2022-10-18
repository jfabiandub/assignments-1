#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* locates the X in the mine */
char find(char* mine, int m, int n, int i, int j){
  int bomb=0;
  if(i-1 >= 0 && mine[(i-1)*n + j]=='X'){
    bomb++;
  }
  if(i+1 <m && mine[(i+1)*n + j] == 'X'){
    bomb++;
  }
  if(j-1 >= 0 && mine[i*n + j-1] == 'X'){
    bomb++;  
  }
  if(j+1 <n && mine[i*n + j+1]=='X'){
    bomb++;
  }
  if(i-1 >= 0 && j-1 >=0 && mine[(i-1)*n + j-1]== 'X'){
    bomb++;
  }
  if(i-1>= 0 && j+1<n && mine[(i-1)*n + j+1]=='X'){
    bomb++;
  }
  if(i+1<m && j-1 >=0 && mine[(i+1)*n + j-1]== 'X'){
    bomb++;
  }
  if(i+1<m && j+1<n && mine[(i+1)*n + j+1]=='X'){
    bomb++;
  }
  return bomb + '0';
}

int main(int argc, char** argv) {
  srand(time(0));  //creates random mines
  
  if (argc !=4){
    printf("usage: %s m n p\n", argv[0]);
    exit(0);
  }
  int m, n; //  hold the m x n grid.
  m = atoi(argv[1]);
  n = atoi(argv[2]); 
  float p; 
  p =atof(argv[3]);

  char* board = malloc(sizeof(char)* m * n);

  float r;
  for (int i=0; i< m; i++ ){
    for (int j=0; j<n; j++){   
       r = (float)rand()/RAND_MAX;
      if(r < p){
        board[i*n + j] = 'X';
      }
      else{
        board[i*n + j]= '.';
      }
      printf(" %c", board[i*n + j]);
    }
    printf("\n");
  }
  
  for (int i = 0; i<m; i++){
    for (int j = 0; j<n; j++){
      if(board[i*n + j == '.']){
        board[i*n + j ] = find(board, m, n, i, j);
      }
      printf(" %c", board[i*n + j]);
    }
    printf("\n");
  }


  free(board);
  return 0;
}