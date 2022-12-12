/* write parsing function that takes argv given in the main to it and parase
   it and make the http command.*/
#include "string.h"
#include "stdlib.h"
#include <stdio.h>
#include <netdb.h>
struct Client
{
  int port;
  int text_length;
  char* url;
  char* path;
  char* parameters_of_r;
  char* text;
}typedef Client;

void client_init(Client* new_client){
  new_client->parameters_of_r =(char*)malloc(sizeof(char));
  new_client->path = (char*)malloc(sizeof(char));
  new_client->path[0] = '\0';
  new_client->port = 80;
  new_client->text = (char*)malloc(sizeof(char));
  new_client->url = (char*)malloc(sizeof(char));
  new_client->text_length = 0;
}
Client* http_parsing(int length_of_argv,char *argv[],Client* new_client){
  int flag_r = 0;
  int flag_p = 0;
  int flag_in_url = 0;
  int number_of_slash = 0;
  int check_next = 0;
  int number_of_parameters = 0;
  int size_of_text = 0;
  int size_of_parameters = 0;
  client_init(new_client);
  char *check_com = (char*)malloc(sizeof(char*));/*check for if the value inside the http:// if we arrived to the value .com*/
  for (int i = 0; i<length_of_argv; i++) {
    if (flag_p == 1) {/*checks for the value of the flag of p and adds the text that comes afterwards to the */
      size_of_text = atoi(argv[i]);/*checks the value of the size of the text.*/
      i++;
      if(argv[i]== NULL){/*check if the value of the text is not NULL*/
        perror("argv is null");
        exit(1);
      }
      strncat(new_client->text,argv[i],size_of_text);
      new_client->text_length = size_of_text;
      flag_p=0;
    }
    if (flag_r == 1) {
      number_of_parameters = atoi(argv[i]);///enter the number of parameters into placeholder
      for(int k =i+1;k<=i+number_of_parameters;k++){
        for (int j = 0; argv[k][j] != NULL; j++){
          size_of_parameters++;
        }
      }
      new_client->parameters_of_r = (char*)malloc(size_of_parameters*sizeof(char));
      new_client->parameters_of_r[0] = '?';
      flag_r = 0;
    } 
    else if (number_of_parameters >= 1) {
      char and_char = '&';
      strcat(new_client->parameters_of_r, argv[i]);
      number_of_parameters--;

      if(number_of_parameters >= 1)
       strncat(new_client->parameters_of_r ,&and_char,1);

      ///check for the parameters of -r
      if (number_of_parameters == 0)///for making it not possible to enter -r twice.
        number_of_parameters = -1;
    } 
    else {
      if(strstr(argv[i],"http://")!=NULL){
        flag_in_url = 1;
        for (int j = 0; argv[i][j] != NULL; j++) {
          if (flag_in_url == 1) {
            
            if(number_of_slash==2){
              strncat(new_client->url, &argv[i][j],1);
            }
            if(argv[i][j]=='/')number_of_slash++;
            /// runs while in the url and adds to the *url and to *check_com.
            if(strlen(check_com)>=4){
              /*checks if the number of values in check_com is more than 4 to delete the first one and add the new one to the end*/
              for (int k = 0; k < 4; k++)
              {
                check_com[k] = check_com[k+1];
              }
            }
            strncat(check_com,&argv[i][j],1);
            if (strcmp(check_com, ".com")==0) {
              // checks if we are at the end of the url.
              flag_in_url = 0;
              strncat(new_client->url,"\0",1);
            }
          } 
          else {
            if (argv[i][j] == ':') { // check if there is a spacific port.
              char* temp_for_port = (char*)malloc(sizeof(char));
              while(argv[i][j] != '/'&&argv[i][j]!=NULL){
                if(argv[i][j]!=':'){
                  strncat(temp_for_port,&argv[i][j],1);
                }
                j++;
              }
              new_client->port = atoi(temp_for_port);
              strncat(new_client->path,&argv[i][j],1);/*adds the / to the path at place 0.*/
              free(temp_for_port);
            }
            else{/*adds the value of the path to the placeholder char* path*/
              strncat(new_client->path,&argv[i][j],1);
            }
          }
        }
        if(new_client->path[0]=='\0'){
          char temp = '/';
          strncat(new_client->path,&temp,1);
        }
      }
      else{
        for (int j = 0; j <= strlen(argv[i]); j++) {
          if (argv[i][j] == '-') {
            check_next = 1;
          } else if (check_next == 1) {
            if (argv[i][j] == 'r' && number_of_parameters != -1) {
              flag_r = 1;
            } 
            else if (argv[i][j] == 'p') {
              flag_p = 1;
            }
            check_next = 0;
          }
        }
      }
    }
  }
  return new_client;
}
void make_http_request(Client* new_client){
  /*makes the http request and send it to the server*/
  struct sockaddr_in new_socket;
  struct hostent *hp;
  int nbytes;
  char* buffer;
  char buffer_to_read[400];
  int flag_p = 0;
  int size_of_buf = 14 + strlen(new_client->text)+strlen(new_client->path)+strlen(new_client->parameters_of_r);
  if(new_client->text_length!= 0){
    size_of_buf+3;
    flag_p = 1;
  }
  if(new_client->parameters_of_r!=NULL)size_of_buf+2;
  buffer = (char*)malloc(size_of_buf*sizeof(char));
  hp = gethostbyname(new_client->url);
  new_socket.sin_addr.s_addr = ((struct in_addr*)(hp->h_addr_list[0]))->s_addr;
  new_socket.sin_family = AF_INET;
  if(connect(htons(new_client->port),(struct sockaddr*)&new_socket,sizeof(new_socket))<0)
    {
      perror("connect");
      exit(1);
    }
  if(flag_p ==1){
    strcat(buffer,"POST ");
  }
  else{
    strcat(buffer,"GET ");
  }
  strcat(buffer,new_client->path);
  strcat(buffer,new_client->parameters_of_r);
  strcat(buffer," HTTP/1.0");
  if((nbytes = write(htons(new_client->port),buffer,size_of_buf))<0){
    perror("write");
    exit(1);
  }
  if((nbytes=read(htons(new_client->port),buffer_to_read,sizeof(buffer_to_read)))<0){
    perror("read");
    exit(1);
  };
  buffer_to_read[nbytes-1] = '\0';
  printf("Answer for the server is: %s",buffer_to_read);
}