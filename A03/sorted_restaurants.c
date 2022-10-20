#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct restaurant{
  char name[100];
  int op_hour;
  int cl_hour;
  float star_rat;
};

struct node {
  struct restaurant rest;
  struct node* next;
};

/* fuction that inserts the restaurants into a lsit */
struct node* insert_sorted( struct node* head, struct restaurant rest){
  struct node* newNode = malloc(sizeof(struct node));
  if(newNode == NULL){
    printf("Out of space\n");
    exit(1);
  }
  newNode->rest = rest;
  newNode->next = NULL;
  if(head == NULL){
    return newNode;
  }
  if(head->rest.star_rat < rest.star_rat){ //checks if the head restauratn rating is the highest
    newNode->next = head;
    return newNode;
  }

  struct node* current = head;
  while (current->next != NULL){  //cehcks for the current start rating.
    if(current->next->rest.star_rat > rest.star_rat){
      current = current->next;
    }
    else{
      break;
    }
  }
  newNode->next = current->next;
  current->next = newNode;
  return head;
}

/* prints the list */
void printList(struct node* list){
  struct node* temp;
  temp = list;
  int count = 1;
  if(temp == NULL){
    printf("List is empty");
  } 
  else{
    while(temp){
      printf("(%d) %s\topen: %d:00\tclose: %d:00\tstars: %0.1f\n", count,
    temp->rest.name,
    temp->rest.op_hour,
    temp->rest.cl_hour,
    temp->rest.star_rat);
    temp= temp->next;
    count++;
    }
  }
}

/* clears the list */
void clear(struct node* list){
  struct node* n;
  while(list){
    n = list->next;
    free(list);
    list = n;
  }
}

int main() {
  
  struct node* list = NULL;
  //list = malloc(sizeof(struct node));

  int num_rest; //number of rest input by the user
  printf("Enter a number of restaurants: ");
  scanf("%d", &num_rest );

  struct restaurant restaurant;
  //restaurant = malloc(sizeof( struct restaurant)*num_rest); 

  char name[32];   //gets the name of restaurant

  for(int i= 0; i< num_rest; i++ ){ 
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", name);
    strcpy(restaurant.name, name);

    printf("Open time: ");
    scanf(" %d%*c", &restaurant.op_hour);

    printf("Close time: ");
    scanf(" %d%*c",  &restaurant.cl_hour);
   
    printf("Stars: ");
    scanf("%e", &restaurant.star_rat); 
    list = insert_sorted(list, restaurant);
  }

  printf("Welcome to Jenii's Restaurant Directory\n");
  printList(list);
  clear(list);

  //free(list);
  list=NULL;
  return 0;
}

