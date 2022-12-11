#include "Client.c"
#include "malloc.h"
int main(void) {
  char* argv[1] = {"http://www.ptsv2.com/t/ex2"};
  Client* new_client;
  http_parsing(1,argv);
}