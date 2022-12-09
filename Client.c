* // write parsing function that takes argv given in the main to it and parase
  // it and make the http command.*//
#include "string.h"
char* http_parsing(char *argv[]) {
  int flag_r = 0;
  int flag_p = 0;
  int flag_in_url = 0;
  int check_next = 0;
  int number_of_parameters = 0;
  char *url = "";
  char *path = "/";
  char *parmeters_of_r = "?";
  for (int i = 0; argv[i] != NULL; i++) {
    // if (flag_p == 1) {
    //   argv[i]
    // }
    if (flag_r == 1) {
      number_of_parameters = atoi(argv[i]);
      flag_r = 0;
    } 
    else if (number_of_parameters != 0) {
      parmeters_of_r += argv[i] + '&';
      number_of_parameters--;
    }
    else {
      if(strstr(argv[i],"http://"){
        flag_in_url = 1;
      }
      for (int j = 0; j <= strlen(argv[i]); j++) {
        if (argv[i][j] == '-') {
          check_next = 1;
        } else if (check_next == 1) {
          if (argv[i][j] == 'r') {
            flag_r = 1;
          } else if (argv[i][j] == 'p') {
            flag_p = 1;
          }
          check_next = 0;
        }
      }
    }
  }
}
