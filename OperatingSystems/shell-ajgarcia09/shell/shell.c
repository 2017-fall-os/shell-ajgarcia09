#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <fcntl.h> //for read
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>



#define BUFLEN 1024

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
    freeTokens(tokens);
    free(tokens);
   }
  char ** path = mytoc(tokens[1], ':');
  return path;
  }

char ** updateInputList(char ** inputList, char * command){
  int commandSize = lengthOfCharArray(command); //+ null char
  inputList[0] = '\0';
  inputList[0] = malloc(commandSize+1);
  int i =0;
  for(; i < commandSize; i++){
    inputList[0][i] = command[i];
  }
  inputList[0][i] = '\0';
  return inputList;

}
/*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
while(1){
    char input[BUFLEN];
    char * command;
    write(1,"[ajgarcia09 shell]$ ",19);
    int numBytesRead = read(0,input,BUFLEN);
    input[numBytesRead-1] = '\0'; //remove new line char*/
    if(compStrings(input,"exit")==1){
      break;  //exit program
    }
   //tokenize input string
   char ** inputList = mytoc(input, ' ');
   //absolute path was entered
   if(access(inputList[0], X_OK) == 0){
    char * command = inputList[0];
    int pid =  fork();
   if(pid ==0){
      execve(command,inputList,envp);
      free(command);
   }
   else{
     wait(NULL);
   }
}
   else{//search for command in path list
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
int pid = fork();
if(pid == 0){
execve(command,inputList,envp);
    free(command);
     }
 else{
   wait(NULL);
  }
}
printf("about to fork\n");
int pid = fork();
printf("forking with pid:%d\n",pid);
   if(pid == 0){ //child is running
       printf("child is running\n");
       execve(command, inputList,envp);
        }
     else{
       wait(NULL); //wait for the child to finish
       printf("parent is running\n");
       freeTokens(inputList);
       free(inputList);
     }
   }
  printf("End \n");
}
}
     

       
