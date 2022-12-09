/* write parsing function that takes argv given in the main to it and parase
   it and make the http command.*/
#include "string.h"

char* http_parsing(char *argv[]){
  int flag_r = 0;
  int flag_p = 0;
  int flag_in_url = 0;
  int check_next = 0;
  int number_of_parameters = 0;
  char *url = "";
  char *path = "/";
  char *parmeters_of_r = "?";
  char *check_com = "";
  for (int i = 0; argv[i] != NULL; i++) {
    // if (flag_p == 1) {
    //   argv[i]
    // }
    if (flag_r == 1) {
      number_of_parameters = atoi(argv[i]);///enter the number of parameters into placeholder
      flag_r = 0;
    } 
    else if (number_of_parameters >= 1) {
      strcat(argv[i] , '&');
      strcat(parmeters_of_r, argv[i]);
      ///check for the parameters of -r
      number_of_parameters--;
      if (number_of_parameters == 0)///for making it not possible to enter -r twice.
        number_of_parameters = -1;
    } 
    else {
      if(strstr(argv[i],"http://")){
        flag_in_url = 1;
        for (int j = 0; argv[i][j] != NULL; j++) {
          if (flag_in_url == 1) {
            /// runs while in the url and adds to the *url and to *check_com.
            strncat(url, argv[i][j],1);
            if(strlen(check_com)>=4){
              /*checks if the number of values in check_com is more than 4 to delete the first one and add the new one to the end*/
              for (int i = 0; i < 4; i++)
              {
                check_com[i] = check_com[i+1];
              }
            }
            strncat(check_com, argv[i][j],1);
            if (strcmp(check_com, ".com")) {
              // checks if we are at the end of the url.
              flag_in_url = 0;
            }
          } 
          else {
            if (argv[i][j] == ':') { // check if there is a spacific port.
              whlie(argv[i][j] != '/'){
                strncat(port, argv[i][j],1);
                j++;
              }
            }
            else{/*adds the value of the path to the placeholder char* path*/
              strncat(path,argv[i][j],1);
            }
          }
        }
      }
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
