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

char * concatStrings(char *str1, char * str2){
  //measure length of str1
  int i = 0;
  for(; str1[i]; i++);
  printf("length of str1: %d\n", i);

  int j = 0;
  //measure length of str2
  for(; str2[j]; j++);
  printf("length of str2: %d\n", j);

  char newString[i+j+2];

  int k =0;
  while(*str1){
    newString[k] = *str1;
    str1++;
    k++;
  }
  newString[k] = '/';
  k++;
  while(*str2){
    newString[k] = *str2;
    str2++;
    k++;
  }
  newString[k] = '\0';
  printf("newString is: %s\n", newString);
  return newString;
}
  
 
/*argc, argv and envp are used to get environment
  variables used to find the PATH variable.*/

int main(int argc, char **argv, char **envp){
  int pid;
  int waitValue;
  int waitStatus;
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
    int foundCommand = 0;
    printf("inputList[0] :%s\n", inputList[0]);
    if(findCommand(inputList[0])){ //if search succeeded
      command = inputList[0];
      foundCommand = 1;
      printf("found command: %s\n", command);
    }
    //search in all paths
    else{
      char * pathList = getenv("PATH");
      printf("pathList is: %s\n", pathList);
      char ** pathTokens = mytoc(pathList, ':');
      for(int i =0; pathTokens[i]; i++){
	char * currentCommand = concatStrings(pathTokens[i],inputList[0]);
	if(findCommand(currentCommand)){
	  command = currentCommand;
	  break;
	}
      }
    }
    printf("foundCommand : %d\n", foundCommand);
   if(foundCommand == 0){
      printf("Command Not Found: %s\n", command);
    }
    pid = fork();
    if(pid == 0){ //if the child process is running
      execve(command,inputList,envp);
    }
    else{
      
      waitValue = waitpid(pid, &waitStatus, 0);//wait until the child process ends
    }
    }
  }

