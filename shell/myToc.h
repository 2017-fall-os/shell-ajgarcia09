#ifndef MyTocIncluded
#define MyTocIncluded

/*Counts how many words are in the user input.
Works with strings that have multiple spaces in between words:
 "Hello    World" yields wordCount = 2
*/
int countWords(char * str, char delim);

/*Deletes the initial spaces at the beginning of each token:
    "   Ana" becomes "Ana"
*/
char *  trimInitialSpaces(char * str);

/*Get the number of chars before each space:
  token: "Ana "
  tokenSize = 3
*/
int getTokenSize(char * token);

/*Allocates space for a token and copies it into an array 
  that will go into an index of tokenVec*/
char * allocateToken(char *token, char delim, int tokenSize);
  
/*Allocates each token in an array and
  returns a pointer to this array*/ 
char ** mytoc(char *str, char delim);

/*Print each token in a new line */
void printTokenVec(char ** tokenVec, int wordCount);

//Calculates the length of the each token in order to print it
int lengthOfCharArray(char * str);

/*Returns 1 if two strings are equal.
  Used to exit the program*/
int compStrings(char *str1, char *str2);

#endif
