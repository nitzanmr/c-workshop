#include "Client.c"
#include "malloc.h"
int main(void) {
  char* argv[4] = {"-p","5","bbbbb","http://www.ptsv2.com:8/t/ex2"};
  Client* new_client;
  http_parsing(4,argv);
}