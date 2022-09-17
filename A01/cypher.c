#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Assigment 01
@uthor Jenifer Fabian Dubon
Date -  09/17/22
*/

int main() {
char str[100];  //string array that holds the word given by the user.
int shft;       // holds the shift integer given by the user

printf("Enter a word: " ); 
scanf("%s", str);       // scans the word given by the user

printf("Enter a shift: ");
scanf("%d", &shft);     // scans the shift givent by the user 

//int size = strlen(str);
char word;

//for loop that takes the word given by the user and encodes it using a shift cypher
//Replaces each letter with a letter that is in X positions from it in the alphabet
  for(int i = 0; str[i] != '\0'; i++){ 
      word = str[i];
      if (word >= 'a' && word <= 'z'){
        word = word + shft;
        if (word > 'z'){
          word = word - 'z' + 'a'-1;
        }
        str[i] = word;
      }
  }
  printf("Your cypher is %s \n", str);  //prints the ne cypher.

return 0;
}



 
 