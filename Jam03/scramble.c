#include <stdio.h>
#include <string.h>

int main() {
 char message[32];
  printf("Please enter a phrase: ");
  fgets(message, 31, stdin);
  message[31] = '\0';

  unsigned char leftmask = 0x8;
  unsigned char rightmask = 0x4;
  unsigned char mask = 0xf3;


  // todo: modify message using bitwise operations
  for (int i=0; i<strlen(message); i++){
    char c = message[i];
    char c1 = c & leftmask;
    char c2 = c & rightmask;

    char c3 = mask & c;
    c1= c1 >> 1;
    c2 = c2<< 1;

    char result = c3 | c1 |c2;

  message[i]= result;

  }
  printf("scramble: %s\n", message);
}
