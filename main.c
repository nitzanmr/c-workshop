#include "Client.c"
#include "malloc.h"
int main(void) {
  char* argv[8] = {"http://www.google.com:80/","-p","1000","rRfiyCMjvcAJRtiJJQ7JMR3Pbi0meK48IocvxRak7sEISLvpD3sz49wZJMPp4nzItCG30ho5J9dtQEYUQVnkZJtLXbJinrfmswMt8iqTjsr3XMwgJoHFRfe3KMgfixUYKyOJgGlrcEAqNBxJmhyQwuTJlEgJAZodlTI2MAYdQoO3CmqN73K3JRsRL1spAnorbfiVSRFsyAoDZeo6RHravEurVarxbbvImTdJWJqh8hXEjeKG8vL3Qi9g3sgHXSIaKzgwaZVKLcAjxJgNk51CeXkLIDs5wDidNZ7vYEjZzLYYfl1DZX65gekER7J2BuEMmyoYnsYUcsCMj8s570kb5dxdmPvM4WBSOu2pPEF5wijYWNRVe737qn7tD7yVotbx0Yo23SPJClJ4cPwbnI2SZ7gsQ6krMOy9UcSL1HqoacMR6rIVvuw8go9XgaOhGgNEWcKjdhx8MGTRM8quauWa6ki88da20Z49INObyf5u1daTbz7Vr1LUEy5rwQv8fkNwOEW12raQuRbNUfvfRKTyOwRGjjsPcfOXxl9pAZE3UrJBCjPEsZsyDiXPoGcODWbn2KDqD2AcEjx07Wzzh0BpxcPS1v2hXDsH903hDGgbTlu39NdHAqFshzmTfNUnMqQTlhu8fLWDvaoCDUN36b05CuLOtjFJ1ZSrem1E6qhcfdE6tdna0HSuaoPu6cRHjsI0Yt8ms3fWOaro3XzdYxQ2WIYLThnbqFfGGlg8sdd5lVdzaaHR9XY6LeC0zdUTyRovhXaMrlS1Wn7WFpPQQy9Sp5c37rId8tBZTW4n08ve0P5T4gu9o9jlYwrE8tozfYthAB3u88inA0sSLCY93IHpXL7kzCq2PUkS4x7l3iLFEXaWMKmqxgYsx2QM3Gmvvtor4PKWHCM08YgANZudPZmnMME6aBcNfIfqzolWWOMoDIgeJUFydHobASjWoj1qAcjUlXePQjWk013h5Yhy7YnUQcdoTnrXZJl0Im0Z4uVm","-r","2","city=dallas","state=texas"};
  Client* client22 = (Client*)malloc(sizeof(Client));
  http_parsing(5,argv,client22);
  // printf("\n%s\n",new_client->parameters_of_r);
  // make_http_request(new_client);
  make_http_request(client22);
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