#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <sys/stat.h>//for stat
#include <fcntl.h> //for read

#define BUFLEN 1024

int findCommand(char * command){
  printf("entered findCommand\n");
  struct stat buffer;
  //if successful, stat will return 0
  if(stat(command, &buffer) == 0 && buffer.st_mode & S_IXOTH){
    printf("found command!\n");
    return 1; //found executable
  }
  else{
    printf("didn't find executable :( \n");
    return 0; //didn't find executable    
  }
}


/*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  int pid;
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
    if(findCommand(inputList[0])){ //if search succeeded
      command = inputList[0];
      printf("found command: %s\n", command);
    }
    //search in all paths
      // printf("did not find inputList[0]: %s\n", inputList[0]);
    //else{
      char * pathList = getenv("PATH");
      printf("pathList is: %s\n", pathList);
      char ** pathTokens = mytoc(pathList, ':');
      // }
 
  }
}
