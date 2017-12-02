#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read and pipe
#include <fcntl.h> //for read
#include <string.h>
#include <stdlib.h>//for calloc, malloc
#include <sys/wait.h>//for wait

#define BUFLEN 1024


void readInput(char * input){
    write(1,"[ajgarcia09 shell]$ ",19);
    int numBytesRead = read(0,input,BUFLEN);
    input[numBytesRead-1] = '\0'; //remove new line char*/
}


//checks if the user entered a command that uses a pipe
int checkForPipe(char *input){
  while(*input){
    if(*input == '|'){
      return 1;
    }
    input++;
  }
  return 0;
}

/*function is a modification of Dr. Freudenthal's forkPipeDemo.c*/
void forkPipe(char ** commandOne, char ** commandTwo, char **envp, char ** inputList){
  int * pipeFds = (int *)calloc(2,sizeof(int)); //pipe file descriptors
  pipe(pipeFds);
  int pid = fork();

  if(pid ==0){ //parent is running
    close(1); //close file descriptor 1
    //take what is in pipeFds[1] and place it in the lowest free fds
    dup(pipeFds[1]);
    close(pipeFds[0]);
    close(pipeFds[1]);
    //run the command
    runIt(commandOne,envp);
    exit(2);
  }
  else{
      wait(NULL);//wait on the child
      int pid2 = fork();   
      if(pid2 ==0){
          close(0); //close file descriptor 0
          dup(pipeFds[0]);
          close(pipeFds[0]);
          close(pipeFds[1]);
          //run the command
          runIt(commandTwo, envp);
      }
   else{
     wait(NULL);//wait on the child
   }
  }
}
  

void runIt(char ** inputList,char ** envp ){
  //if it's not an absolute path, look in PATH variable
     char ** path = getPathList(envp);
     int sizeOfInputListIndex = lengthOfCharArray(inputList[0]);
     char * temp = (char*)malloc(sizeOfInputListIndex+1);
     for(int i = 0; i < sizeOfInputListIndex; i++){
       if(i == (sizeOfInputListIndex -1)){
         temp[i] = '\0';
       }
         temp[i] = inputList[0][i];
      }
      for(int i =0; path[i]; i++){
        char * command = concatStrings( path[i],temp);
        inputList = updateInputList(inputList,command);
        execve(command,inputList,envp);
	free(command);
	}     
}

void forkIt(char ** envp, char ** inputList){
  //printf("in forkIt\n");
  int pid = fork();
   if(pid == 0){
     execve(inputList[0],inputList,envp);

     //if it's not an absolute path, look in PATH variable
     runIt(inputList,envp);
     }
   else{
     wait(NULL); //wait on the child
     }
}

  
void freeTokens(char ** tokenVec){
  while(*tokenVec){
    free(*tokenVec);
    tokenVec++;
  }
 }

char * concatStrings(char * str1, char * str2){
  int newStringSize =lengthOfCharArray(str1)+lengthOfCharArray(str2)+2;
  char * newStr = malloc(newStringSize);
  int i =0;  
  while(str1[i]){
    newStr[i] = str1[i];
   i++;
  }
  newStr[i] = '/'; 
  i++;
  int j =0;
  while(str2[j]){
    newStr[i] = str2[j];
    j++;
    i++;
  }
  newStr[i] = '\0';
  return newStr;
}
  
char ** getPathList(char ** envp){
  char ** tokens; 
  for(int i = 0; envp[i]; i++){
    tokens = mytoc(envp[i], '=');
    if(compStrings(tokens[0],"PATH")){
      break;
    }
   }
  char ** path = mytoc(tokens[1], ':');
  return path;
  }

char ** updateInputList(char ** inputList, char * command){
  int commandSize = lengthOfCharArray(command); // null char
  inputList[0] = '\0';
  inputList[0] = malloc(commandSize+1);
  int i =0;
  for(; i < commandSize; i++){
    inputList[0][i] = command[i];
  }
  inputList[0][i] = '\0';
  return inputList;

}
   
     

       
