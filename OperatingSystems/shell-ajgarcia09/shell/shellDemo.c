#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <fcntl.h> //for read
#include <sys/wait.h>
#include "shell.h"


/*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  for(;;){
    char input[BUFLEN];
    char * command;
    write(1,"[ajgarcia09 shell]$ ",19);
    int numBytesRead = read(0,input,BUFLEN);
    input[numBytesRead-1] = '\0'; //remove new line char
    if(compStrings(input,"exit")==1){
      break;  //exit program
    }
   //tokenize input string
   char ** inputList = mytoc(input, ' ');
   //absolute path was entered
   if(access(inputList[0], X_OK) == 0){
     char * command = inputList[0];
     execve(command,inputList,envp);
     free(command);
   }
   else{//search for command in path list
     char ** path = getPathList(envp);
     int sizeOfInputListIndex = lengthOfTokenArray(inputList[0]);
     char * temp = (char*)malloc(sizeOfInputListIndex+1);
     for(int i = 0; i < sizeOfInputListIndex; i++){
       if(i == (sizeOfInputListIndex -1)){
	   temp[i] = '\0';
	 }
	 temp[i] = inputList[0][i];
      }
     
     for(int i =0; path[i]; i++){
       command = concatStrings( path[i],temp);
       inputList = updateInputList(inputList,command);
       execve(command,inputList,envp);
       free(command);
     }

  int pid = fork();
   if(pid == 0){ //child is running
     execve(command, inputList,envp);
     free(command);
   }
   else{
     wait(NULL); //wait for the child to finish
     freeTokens(inputList);
     free(inputList);
   }
   }
  }//for
}

