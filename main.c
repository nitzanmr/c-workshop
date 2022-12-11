#include "Client.c"
#include "malloc.h"
int main(void) {
  char* argv[5] = {"-r","2","city=dallas","state=texas","http://www.ptsv2.com:8/t/ex2"};
  Client* new_client;
  new_client = http_parsing(5,argv);
  printf("%s",new_client->parameters_of_r);
}