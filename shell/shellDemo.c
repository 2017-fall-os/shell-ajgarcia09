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

    if(checkIfBackgroundProc(input)){ //background process entered
     removeAmpersand(input);
     char ** backgroundCommands = mytoc(input, ' ');
     runItInBackground(envp,backgroundCommands);
     }
   else{ //not a background process
       //tokenize input string
       char ** inputList = mytoc(input, ' ');
   
       //command is change directory (cd)
       if(inputList[0][0] == 'c' && inputList[0][1] == 'd'){
           chdir(inputList[1]);
         }
							 
       if(checkForPipe(input)){
         char ** pipeCommands = mytoc(input, '|');
         char ** commandOne = mytoc(pipeCommands[0], ' ');
         char ** commandTwo = mytoc(pipeCommands[1], ' ');
         forkPipe(commandOne,commandTwo,envp,inputList);       
       }
   
       else{
           forkIt(envp,inputList);
       }
      }
    }
}

