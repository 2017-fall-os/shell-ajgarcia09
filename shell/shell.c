#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <sys/stat.h>//for read
#include <fcntl.h> //for read

#define BUFLEN 1024

int findCommand(char * command){
  printf("entered findCommand\n");
  struct stat buffer;
  //if successful, stat will return 0
  int status = stat(command, &buffer);
  printf("findCommand returns: %d\n", status);
  return status;
}


/*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  int pid = 0;
  for(;;){
    char input[BUFLEN];
    char * command;
    write(1,"[hello poochy] $ ",17);
    int numBytesRead = read(0,input,BUFLEN);
    input[numBytesRead-1] = '\0'; //remove new line char
    if(compStrings(input,"exit")==1){
      break;  //exit program
    }
    //tokenize input string
    char ** inputList = mytoc(input, ' ');
    printf("inputList[0] :%s\n", inputList[0]);
    if(findCommand(inputList[0]) == 0){ //if search succeeded
      command = inputList[0];
      printf("found command: %s\n", command);
    }
    else{
      printf("did not find inputList[0]: %s\n", inputList[0]);
    }
 
  }
}
