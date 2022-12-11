#include "Client.c"
#include "malloc.h"
int main(void) {
  char* new = (char*)malloc(sizeof(char*));
  new[0] = '/';
  char new_a = 'a';
  char* new_abv= "abv";
  char new_cc[3][2] = {"11","11"};
  // new_cc[0] = "11";
  // new_cc[1] = "11";
  strncat(new,new_cc[0],sizeof(new_cc[0]));
  // strncat(new,&new_abv,strlen(new_abv)-1);
  // for(int i =0;i<strlen(new_abv)-1;i++){
  //   strncat(new,&new_abv[i],1);
  // }
  printf("%s",new);
}