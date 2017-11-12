#include <stdio.h>
#include "myToc.h"
#include "shell.h"
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <fcntl.h> //for read
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


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
   
     

       
