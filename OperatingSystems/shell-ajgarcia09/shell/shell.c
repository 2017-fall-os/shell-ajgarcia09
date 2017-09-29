#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <sys/stat.h>//for stat
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
  printf("entered concatStrings\n");
  printf("str1: %s\n",str1);
  printf("str2: %s\n", str2);
  int newStringSize =lengthOfTokenArray(str1)+lengthOfTokenArray(str2)+2;
  printf("newStringSize %d\n", newStringSize);
  char * newStr = malloc(newStringSize);
  while(*str1){
    *newStr = *str1;
    printf("current newStr %c\n", *newStr); 
    str1++;
    newStr++;
  }
  //*newStr = '/';
  //newStr++;
  while(*str2){
    *newStr = *str2;
    printf("current newStr %c\n", *newStr);
    str2++;
    newStr++;
  }
  *newStr = '\0';
  printf("newStr: %s\n", newStr);
  return newStr;
}
  
    
char ** getPathList(char ** envp){
  printf("in getPath\n");
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


  /*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  for(;;){
    char input[BUFLEN];
    char * pathConcat;
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
     command = inputList[0];
     printf("found command: %s\n",command);
   }
   else{//search for command in path list
     printf("didn't find command %s\n", inputList[0]);
     char ** path = getPathList(envp);
     for(int i =0; path[i]; i++){
       pathConcat = concatStrings(path[i],"/");
       //command = concatStrings(pathConcat,inputList[0]);
	 printf("pathConcat is: %s\n",pathConcat);
    }

  pid_t  pid = fork();
   if(pid == 0){ //child is running
     execve(command, inputList,envp);
   }
   else{
     wait(NULL);
     freeTokens(inputList);
     free(inputList);
   }
  }
  }
}
     

       
