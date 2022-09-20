#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {
srand(time(0));
int user_guess;
int actual = rand() % (5000-3000 + 1) + 3000;
int guess1 = rand() % (5000-3000 + 1) + 3000;
int guess2 = rand() % (5000-3000 + 1) + 3000;

  printf("Enter a guess to win a luxurious dishwasher: $");
  scanf("%d", &user_guess);
  printf("AI contestant #1 guesses %d\n", guess1);
  printf("AI contestant #2 guesses %d\n", guess2);
  printf("The dishwasher cost %d\n", actual);

  if(user_guess>actual && guess1>actual && guess2>actual){
    printf("Sorry. No one wins the dishwasher. I'm keeping it.\n");
  }
  else{
    int arr[3] = {user_guess, guess1, guess2};
    int closest = 1;
    int diff = 2001;
    for(int i = 0; i < 3; i++){
      if(arr[i] < diff){
        arr[i] = diff;
        closest = i;
      }

    
    }
    if (closest == 0){
      printf("Congratulations!! You win the dishwasher!\n");
    }
    if (closest == 1){
      printf("AI contestant #1 wins the dishwasher!\n");
    }
    if (closest == 2){
      printf("AI contestant #3 wins the dishwasher!\n");
    }
  }

 
  return 0;
}

