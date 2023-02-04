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
    new_client->parameters_of_r = NULL;
//    new_client->path = (char*)malloc(sizeof(char));
    new_client->path = NULL;
    new_client->port=NULL;
    new_client->url=NULL;
    new_client->text=NULL;
//    new_client->url = (char*)malloc(sizeof(char));
    new_client->text_length;
}
int http_parsing(int length_of_argv,char *kkkk[],Client* new_client){
    if(kkkk== NULL)exit(1);
    int flag_r = 0;
    int flag_p = 0;
    int number_of_slash = 0;
    int number_of_parameters = 0;
    // int size_of_text=0;
    int size_of_parameters = 1;
    int malloc_url = 0;
    char and_char = '&';
    char* temp_for_port = (char*)malloc(5*sizeof(char));
    client_init(new_client);
    for (int i = 1; i<length_of_argv; i++) {
//        printf("%d\n", i);
        if (flag_p == 1) {/*checks for the value of the flag of p and adds the text that comes afterwards to the */
            new_client->text_length = atoi(kkkk[i]);/*checks the value of the size of the text.*/
            // printf("size of text: %d\nand strlen is: %d",size_of_text,strlen(kkkk[i+1]));
            i++;
            if(kkkk[i]== NULL){/*check if the value of the text is not NULL*/
                char* error_messeage;
                sprintf(error_messeage,"kkkk[%d] is NULL",i);
                perror(error_messeage);
                return 1;
            }
            if(strlen(kkkk[i])<new_client->text_length || strstr(kkkk[i]," ") != NULL){
                printf("Usage: client [-p n <text>] [-r n < pr1=value1pr2=value2 …>] <URL>");
                return 1;
            }
            new_client->text = (char*)malloc((new_client->text_length+1)*sizeof(char));
            snprintf(new_client->text,new_client->text_length+1,"%s",kkkk[i]);
            // strcat(new_client->text,"\0");
            flag_p=0;
        }
        else if (flag_r == 1) {
            number_of_parameters = atoi(kkkk[i]);///enter the number of parameters into placeholder
            for(int k =i+1;k<=i+number_of_parameters;k++){
                for (int j = 0; kkkk[k][j] != '\0'; j++){
                    size_of_parameters++;
                }
            }
            new_client->parameters_of_r = (char*)malloc((size_of_parameters+(number_of_parameters)+1)*sizeof(char));
            new_client->parameters_of_r[0] = '?';
            i++;
            sprintf(new_client->parameters_of_r+1,"%s",kkkk[i]);
            number_of_parameters--;
            if(number_of_parameters>=1)strcat(new_client->parameters_of_r,"&");
            new_client->parameters_of_r[size_of_parameters+(number_of_parameters)] = '\0';
            flag_r = 0;
        }
        else if (number_of_parameters >= 1) {
            strcat(new_client->parameters_of_r, kkkk[i]);
            number_of_parameters--;

            if(number_of_parameters >= 1)
                strncat(new_client->parameters_of_r ,&and_char,1);

            ///check for the parameters of -r
            if (number_of_parameters == 0)///for making it not possible to enter -r twice.
                number_of_parameters = -1;
        }
        else {
            if((strstr(kkkk[i],"http://")!= NULL)){
                new_client->url = (char*)malloc((strlen(kkkk[i])-6)*sizeof (char));
                if(new_client->url == NULL){
                    printf("url is null");
                    exit(1);
                }
                new_client->url[0] = '\0';
                number_of_slash = 0;
                for (int j = 0; kkkk[i][j] != '\0'; j++){
//                    printf("****************\n");
                        if(kkkk[i][j]=='/' || kkkk[i][j] == ':')
                            number_of_slash++;
                        if(number_of_slash==3){
//                            strncat(new_client->url, &kkkk[i][j], 1);
                            // new_client->url[j-7] = kkkk[i][j];
                            strncat(new_client->url,&kkkk[i][j],1);
                            new_client->url[j-6] = '\0';
//                            printf("scanned url: %s\n", new_client->url);
                        }
                        else if(number_of_slash>3&&number_of_slash<5){
                            if (kkkk[i][j] == ':') { // check if there is a spacific port.
                                bzero(temp_for_port,5);
                                while(kkkk[i][j] != '/'&&kkkk[i][j]!='\0'){
                                    if(kkkk[i][j]!=':'){
                                        strncat(temp_for_port,&kkkk[i][j],1);
                                    }
                                    j++;
                                }
                                new_client->port = atoi(temp_for_port);
//                                strncat(new_client->path,&kkkk[i][j],1);/*adds the / to the path at place 0.*/
                                free(temp_for_port);
                            }
                            else{/*adds the value of the path to the placeholder char* path*/
                                int counter = 0;
                                new_client->path = (char*)malloc((strlen(kkkk[i])-j+3)*sizeof(char));
                                snprintf(new_client->path,strlen(kkkk[i])-j+2,"%s",kkkk[i]+j-1);
//                                printf("j = %d is: %c",j-1,kkkk[i][j-1]);
                                break;
//                                for(;kkkk[i][j]!='\0';j++) {
//                                    new_client->path[counter] = kkkk[i][j];
//                                    counter++;
//                                }
                            }
                    }
                }
                if(new_client->path[0]=='\0'){
                    char temp = '/';
                    strncat(new_client->path,&temp,1);
                }
            }
            else{
                for (int j = 1; j < strlen(kkkk[i]); j++) {
                    if (kkkk[i][0] == '-') {
                        if (kkkk[i][1] == 'r' && number_of_parameters != -1) {
                            flag_r = 1;
                        }
                        if (kkkk[i][1] == 'p') {
                            flag_p = 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
void make_http_request(Client* new_client){
    /*makes the http request and send it to the server*/
    struct sockaddr_in new_socket;
    struct hostent *hp;
    int nbytes;
    char buffer[512];
    char buffer_to_read[512];
    int flag_p = 0;
    int size_of_buf = 0;

    if(new_client->parameters_of_r!=NULL)size_of_buf+2;
    hp = gethostbyname(new_client->url);
//    printf("ip is : %s\nthe port is: %d\n",new_client->url,new_client->port);
    int fd = socket(PF_INET,SOCK_STREAM,0);
    new_socket.sin_addr.s_addr = ((struct in_addr*)(hp->h_addr_list[0]))->s_addr;
    new_socket.sin_family = PF_INET;
    new_socket.sin_port = htons(new_client->port);
    if(connect(fd,(struct sockaddr*)&new_socket,sizeof(new_socket))<0)
    {
        perror("connect");
        exit(1);
    }
    if(new_client->text_length >0){
        strcpy(buffer,"POST ");
        size_of_buf+=5;
    }
    else{
        strcpy(buffer,"GET ");
        size_of_buf+=4;
    }
    size_of_buf += sprintf(buffer+size_of_buf,"%s",new_client->path);
    // size_of_buf+=strlen(new_client->path);
    if(new_client->parameters_of_r!= NULL){
        strcat(buffer,new_client->parameters_of_r);
        size_of_buf+=strlen(new_client->parameters_of_r);
    }
    strcat(buffer," HTTP/1.0\r\n");
    size_of_buf+=strlen(" HTTP/1.0\r\n");
    strcat(buffer,"HOST: ");
    size_of_buf+=strlen("HOST: ");
//    size_of_buf += sprintf(buffer+size_of_buf,"%s")
    strcat(buffer,new_client->url);
    size_of_buf+=strlen(new_client->url);
    if(new_client->text_length!=0&&new_client->text!=NULL){
        /*enter the content length option to the buf.*/
        /*checks if the value of the text is null and adss it to buff*/
        int text_length_integer = new_client->text_length;
        int size_of_text_length = snprintf(NULL,0,"%d",new_client->text_length);
        char text_length[size_of_text_length+1];
//        sprintf(text_length,"%d",new_client->text_length);
//        text_length=itoa(new_client->text_length);
//        strcat(buffer,"\r\n");
//        size_of_buf+=strlen("\r\n");
        size_of_buf += sprintf(buffer+size_of_buf,"\r\nContent-length: %d\r\n\r\n",new_client->text_length);
//        size_of_buf+=strlen(text_length);
//        printf("%s\nLEN =%d ",buffer,size_of_buf);
//        strcat(buffer,"\r\n\r\n");
//        size_of_buf+=strlen("\r\n\r\n");
        write(fd,buffer,size_of_buf);
        write(fd,new_client->text,new_client->text_length);
//        write(fd,"\r\n\r\n",sizeof("\r\n\r\n"));
        printf("HTTP request =\n%s",buffer);
        printf("%s",new_client->text);
        printf("\nLEN = %d\n",(size_of_buf+new_client->text_length));
    }
    else{

        strcat(buffer,"\r\n\r\n");
        size_of_buf+= strlen("\r\n\r\n");
        write(fd,buffer,size_of_buf);
        printf("HTTP request=\n%s\nLEN =%d\n",buffer,size_of_buf);
    }

//    printf("The answer from the server is: \n");
    int total_read =0,read_now = 0;
    while ((read_now = read(fd,buffer_to_read,511))>0)
    {
        for(int i =0;i<read_now;i++){
            printf("%c",buffer_to_read[i]);
        }
//        printf("%s",buffer_to_read);
        total_read+=read_now;
        bzero(buffer_to_read,read_now);
    }


//    printf("%s",buffer_to_read);
    printf("\n Total received response bytes: %d\n",total_read);
//    // if((nbytes=)<0){
    //   perror("read");
    //   exit(1);
    // };
    // buffer_to_read[nbytes-1] = '\0';
}
void free_client(Client* client_to_free){
    /*
    frees the folowing malloced inside client:
    text
    url
    path
    parameters if not null
    client
    */
    if(client_to_free!= NULL){
        if(client_to_free->text_length > 0){
            free(client_to_free->text);
        }
        if(client_to_free->parameters_of_r!= NULL){
            free(client_to_free->parameters_of_r);
        }
        free(client_to_free->url);  
        free(client_to_free->path);
        free(client_to_free);
    }
}
int main(int argc,char* argv[]){
    /*a function to unite the other functions together and then free the malloced data.*/
    Client* client22 = (Client*)malloc(sizeof(Client));
    int check = 0;
    check = http_parsing(argc,argv,client22);
    if(check != 0) return 1;
//    printf("url:%s\nport:%d\npath:%s",client22->url,client22->port,client22->path);
    make_http_request(client22);
    
    free_client(client22);
    return 0;
}