#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <sys/stat.h>//for read
#include <fcntl.h> //for read

#define BUFLEN 1024

/*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  int pid = 0;
  for(;;){
    char *input[BUFLEN];
    write(1,"[hello poochy] $ ",17);
    read(0,input,BUFLEN);
if(compStrings(input,"exit")==1){
      //exit proogram
      break;
    }
    else{
      printf("entered: %s", input);
    /*//tokenize input string
    char ** inputList = mytoc(input, ' ');
    char * command = inputList[0];
    prin*/
    }
  }
}
  
