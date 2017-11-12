#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <fcntl.h> //for read
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"
#include "myToc.h"

#define BUFLEN 1024

/*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  char input[BUFLEN];
  for(;;){
    readInput(input);
    if(compStrings(input,"exit")==1){
      break;  //exit program
    }
   //tokenize input string
   char ** inputList = mytoc(input, ' ');
   forkIt(envp,inputList);
    
  }
    
}

