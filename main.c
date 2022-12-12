#include "Client.c"
#include "malloc.h"
int main(void) {
  char* argv[8] = {"-p","5","blabl","-r","2","city=dallas","state=texas","http://www.google.com"};
  Client* new_client =(Client*)malloc(sizeof(Client));
  http_parsing(8,argv,new_client);
  make_http_request(new_client);
  printf("the parameters are: %s\nthe host is: %s\n",new_client->parameters_of_r,new_client->url);
  printf("The text is: %s\n the port is: %d\n the path is: %s",new_client->text,new_client->port,new_client->path);
}