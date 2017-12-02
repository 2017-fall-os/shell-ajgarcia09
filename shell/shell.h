#ifndef ShellIncluded
#define ShellIncluded

char ** getPathList (char ** envp);

void freeTokens(char ** tokenVec);

char * concatStrings(char *str1, char * str2);

char ** updateInputList(char ** inputList, char * command);

void readInput(char * input);

void forkIt(char ** envp, char ** inputList);

void runIt(char ** inputList,char ** envp );

//checks if the user entered a command that uses a pipe
int checkForPipe(char * input);

void forkPipe(char ** commandOne, char ** commandTwo, char **envp, char ** inputList);
//void findCommandInPath(char ** envp, char **inputList){

#endif
