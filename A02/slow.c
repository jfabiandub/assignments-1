#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {  
  char buff[32];
  int length;
  char *slow_str;        

  printf("Pause length: ");
  scanf("%d", &length);

  printf("Text: ");
  scanf("%s", buff); 
  
  slow_str = malloc((length * (strlen(buff) + 1)) + strlen(buff) + 1);
  //memset(slow_str,0,(length+1) *(length)+1);


  int c=0;
  for(int i= 0; buff[i] != '\0'; i++){    //goes through the word
      slow_str[c] = buff[i];
      c++;
      for(int j = 0; j < length; j++){   //goes through the length
        slow_str[c] = '.';
        c++;
      }
  }
  slow_str[c] = '\0';
  printf("%s\n", slow_str );

//frees the memory 
  free(slow_str);
  return 0;
}


