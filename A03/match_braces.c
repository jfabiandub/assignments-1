#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
  int line;
  int column;
  struct node* next;
}; 

/* pushes the elements into the stack */
void push (struct node** s, int line, int column){
  struct node* newNode;
  newNode = malloc(sizeof(struct node));
  if (!newNode){
    printf("Error");
    exit(1);
  }
  newNode->line = line;
  newNode->column = column;
  newNode->next = *s;
  //newNode- s = top;
  *s = newNode;
  //top= newNode;
}

/* pop the element form the stack */
void pop(struct node** s){
    //struct node* curr = s;
    //if(*s !=NULL){
      struct node* newnode = *s;
      *s = (*s)->next;
    //curr = s->next;
    free(newnode);
    //*s= NULL;
  //}
}

/*  clears the stack */
void clear(struct node* s){
struct node* n;
  while(s){
    n = s->next;
    free(s);
    s = n;
  }
}



int main(int argc, char** argv) {
  if (argc !=2){
    printf("usage: %s \n", argv[0]);
    exit(0);
  }
  FILE* infile;   
  infile = fopen(argv[1], "r");
  if(infile == NULL){
    printf("Cannot open file: %s\n", argv[1]);
    exit (1);
  }
  
  /* check for braces  and performs the push and pop functions*/
  char ch;
  int col = 0;
  int line = 1;
  struct node* top = NULL;

  while((ch = fgetc(infile)) !=EOF){
    //printf("%c", ch);
    if(ch == '\n'){
      line++;
      col=0;
    }
    else {
      if(ch == '{'){
      push(&top,line,col);
      }
      else if(ch== '}'){
      if(top == NULL){
        printf("Unmatched brace on Line %d and Column %d \n", line, col);
      }
      else if(ch == '}'){
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n",top->line, top->column, line, col);
        pop(&top);
      }
    }
    }
    col++;
  }
  while(top!= NULL){
    printf("Unmatched brace on Line %d and Column %d \n", top->line, top->column);
        pop(&top);
  }

  clear(top); 
  free(top);
  fclose(infile); //closes the file
  return 0;


//CHECK FOR THE LEAKSSS 
}
