#include "client.c"
#include "malloc.h"
int main(void) {
  char* argv[5] = {"http://www.google.com:80/","-r","2","city=dallas","state=texas"};
  client(5,argv);
  // Client* client22 = (Client*)malloc(sizeof(Client));
  // http_parsing(5,argv,client22);
  // printf("\n%s\n",new_client->parameters_of_r);
  // make_http_request(new_client);
  // make_http_request(client22);
  // struct hostent* hp;
  // struct sockaddr_in *new_socket =(struct sockaddr_in*)malloc(sizeof(new_socket));

  // char* name = "www.google.com";
  // hp = gethostbyname(new_client->url);
  // new_socket->sin_addr.s_addr = ((struct in_addr*)hp->h_addr_list[0])->s_addr; 
  // printf("%d\n", new_socket->sin_addr.s_addr);
  //make_http_request(new_client);
  // printf("the parameters are: %s\nthe host is: %s\n",new_client->parameters_of_r,new_client->url);
  // printf("The text is: %s\n the port is: %d\n the path is: %s",new_client->text,new_client->port,new_client->path);
  // char* args[8] = {"-p","5","blabl","-r","2","city=dallas","state=texas","http://www.google.com:80/t/ex2"};
  // Client* new_client =(Client*)malloc(sizeof(Client));


}