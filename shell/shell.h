#ifndef ShellIncluded
#define ShellIncluded

//searches for PATH variable in envp
char ** getPathList (char ** envp);

//frees memory in arrays of tokens created by tokenizer
void freeTokens(char ** tokenVec);

//checks whether there's an '&' in the user input
int checkIfBackgroundProc(char * input);

//to run the background process
void removeAmpersand(char * input);

//runs the background process
void runItInBackground(char ** envp, char ** backgroundCommands);

//concatenates str2 at the end of str1
char * concatStrings(char *str1, char * str2);

//updates the first index of inputList; used in running execve
char ** updateInputList(char ** inputList, char * command);

//reads user input
void readInput(char * input);

//creates a child process and run it
void forkIt(char ** envp, char ** inputList);

//runs a process by searching for it in the PATH variable and executing it
void runIt(char ** inputList,char ** envp );

//checks if the user entered a command that uses a pipe
int checkForPipe(char * input);

//creates two child processes and modifies file descriptors 0 and 1 
void forkPipe(char ** commandOne, char ** commandTwo, char **envp, char ** inputList);

#endif
