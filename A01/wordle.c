#include <stdio.h>
#include <string.h>
#include <time.h>
#include "words.h"

/* Program that implemets the game Wordle.
*/

/*  check function that checks if the character of the given word is in the random word given by the program */
int check(char character, const char* word ){
  int size = strlen(word);
  for(int i=0; i < size ; i++){
    if(character == word[i]){
      return 1;
    }
  }
  return 0;
}

/* this function compares both strings and cheks if they are in the correct place */
int compare(char g[], const char* w){
  int len = strlen(w);
  int result=1;
  for (int i= 0; i< len; i++ ){
    if(g[i]==w[i]){
    printf(" %c is in the word AND in the correct spot\n", g[i]);
    }
    else if(check(g[i], w) == 1){ //implemets the check function to check for the individual char.
    result =0;
    printf("%c is in the word but not in the correct spot\n", g[i]); 
    }
    else{
      result= 0;
      printf(" %c is not in the word\n", g[i]); 
    } 
  }
  return result;
}    


/* Main function where the check and compare functions are implemented 
*/
int main() {
  srand(time(0));
  const char* word = chooseWord();
  char guess[100];
  //printf("cheat: %s\n", word); // prints the random word

  int g_Tries =0;   //tracks the number of tries
  int is_Right = 0;  //checks if the word is right

  printf("Welcome to Wordle! \n");

  //for(int i=0; i<len; i++)
  while(!is_Right && g_Tries <6){
    g_Tries++;                          
    printf("Please enter a 5-letter word: ");
    scanf("%s", guess);                 // scans the word given by the user
    is_Right = compare(guess, word);
  }
  if(is_Right ==1){       
    printf("You got it! The word is %s \n", word);
  }
  if (!is_Right && g_Tries >=6){
    printf("Sorry, you ran out of times. The correct word is %s  \n", word);
  }
  return 0;
}
