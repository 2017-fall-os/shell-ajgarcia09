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

   if(checkForPipe(input)){
     printf("found pipe! :D \n");
     char ** pipeCommands = mytoc(input, '|');
     printf("pipeCommands[0]: %s\n", pipeCommands[0]);
     printf("pipecommands[1]: %s\n", pipeCommands[1]);
     
     char ** commandOne = mytoc(pipeCommands[0], ' ');
     printf("commandOne[0]: %s\n", commandOne[0]);
     char ** commandTwo = mytoc(pipeCommands[1], ' ');
     printf("commandTwo[0]: %s\n",commandTwo[0]);
     printf("commandTwo[1]: %s\n", commandTwo[1]);
     //forkPipe(char ** commandOne, char ** commandTwo, char ** path, char **envp);
       
   }
   else{
       forkIt(envp,inputList);
   }
  }
    
}

