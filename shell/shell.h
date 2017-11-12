#ifndef ShellIncluded
#define ShellIncluded

char ** getPathList (char ** envp);

void freeTokens(char ** tokenVec);

char * concatStrings(char *str1, char * str2);

char ** updateInputList(char ** inputList, char * command);

void readInput(char * input);

#endif
