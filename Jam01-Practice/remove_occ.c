#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char str[6] = "hello";
    char* ptr = str;
    char letter = 'l';

    remove(ptr, letter);


}

void remove(char* ptr, char letter){
    int size = strlen(ptr);
    char occ =0;

    for(int i = 0; i <size; i++){
        if (ptr[i] == letter){
            ptr[i]==occ;
        }
    }
    printf("final result : %s", ptr);

}
