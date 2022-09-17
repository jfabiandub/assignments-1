#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* creates a struct that holds the information for a restaurant */
struct restaurant{
  char name[100];
  int op_hour;
  int cl_hour;
  float star_rat;
};


int main() {
  struct restaurant rest1, rest2, rest3;  //declares 3 struct restaurants
  int hour;
  char snacks [100]= {"Cheetos, Tacos, and Rice Pudding\n"}; 
 
printf("Welcome to Jenii Struct's Restaurant List \n");
printf("The Special snakcs for today are %s", snacks);
printf("What hour is is (24 hr clock)? ");
scanf(" %d", &hour); //scans the time given by the user


strcpy(rest1.name, "Oishi"); //copys the information from struct restaurant  and adds new info.
rest1.op_hour = 11;
rest1.cl_hour = 23;
rest1.star_rat = 3.5;

printf(" 0) %s open: %d:00 close: %d:00 stars: %g \n", rest1.name, rest1.op_hour, rest1.cl_hour, rest1.star_rat);


rest2 = rest1;
strcpy(rest2.name, "Tacos Aranda");//copys the information from struct restaurant  and adds new info. 
rest2.op_hour = 17;
rest2.cl_hour = 02;
rest2.star_rat = 4.5;
printf(" 1) %s open: %d:00 close: %d:00 stars: %g \n", rest2.name, rest2.op_hour, rest2.cl_hour, rest2.star_rat);


rest3 = rest2;

strcpy(rest3.name, "Korean Noodle House"); //copys the information from struct restaurant  and adds new info.
rest3.op_hour = 06; 
rest3.cl_hour = 15;
rest3.star_rat = 4.1;
printf(" 3) %s open: %d:00 close: %d:00 stars: %g\n", rest3.name, rest3.op_hour, rest3.cl_hour, rest3.star_rat);

int rest_num;
printf("what restaurant do you want to visit? [0, 1, 2] ");
scanf("%d", &rest_num);
//int choice  = check_rest(rest_num);
  if (rest_num ==0){
    if(hour >= rest1.op_hour && rest1.cl_hour <=hour){
       printf(" %s is open\n", rest1.name);
    }
    
    else{
    
      printf(" %s isn't open until 11 o'clock!!\n", rest1.name); 
    }
  }
  else if(rest_num == 1){
    if(rest2.op_hour >=hour && rest2.cl_hour <=hour){
        printf("%s closed at %d o'clock!!\n", rest2.name, rest2.cl_hour);
    }
    else{
        printf("%s is open now\n", rest2.name);
    }
  }
  else if(rest_num == 2){
    if (rest3.op_hour >=hour && rest3.cl_hour <=hour){
      printf("%s closed at %d o'clock!!\n", rest3.name, rest3.cl_hour);
    }
    else{
      printf("Great choice. %s will be open until 3pm \n", rest3.name);
    }
  }


 return 0;
}
