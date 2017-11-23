#include <stdio.h>
#include <sys/types.h>//for read
#include <unistd.h>//for read
#include <sys/stat.h>//for read
#include <fcntl.h> //for read
#include <stdlib.h>
#include <assert.h>
#include "myToc.h"

#define BUFLEN 1024

/*Counts how many words are in the user input.
Works with strings that have multiple spaces in between words:
 "Hello    World" yields wordCount = 2
*/
int countWords(char * str, char delim){
  int wordCount = 0;
  while(*str){
    while(*str == delim){
      str++;
    }
    if(*str != 0){
      wordCount++;
    }
    while(*str && (*str != delim)){
      str++;
    }
  }
  return wordCount;
 }

/*Copies each character from the current
    token in str into strCopy*/
char * copyToken(char *str, int tokLength){
  char * strCopy = (char *)malloc(tokLength +1);
  for(int i = 0; i< tokLength; i++){
    strCopy[i] = str[i];
  }
  strCopy[tokLength] = 0; //terminate copy
  return strCopy;
  
}

/*Deletes the initial spaces at the beginning of each token:
    "   Ana" becomes "Ana"
*/
char * trimInitialSpaces(char * str){
  while(*str == ' '){
    str++;
  }
  return str;
 }

/*Allocates space for a token and copies it into an array 
  that will go into an index of tokenVec*/
char * allocateToken(char * token, char delim, int tokenSize){

  //allocate space for the token
  char * tokenVecIndex = (char *)malloc(tokenSize +1);
  tokenVecIndex[tokenSize] = '\0'; //zero terminator
  tokenVecIndex = copyToken(token, tokenSize);
  return tokenVecIndex;
  }
     
//Calculates the length of the each token in order to print it

int lengthOfCharArray(char * str){
  int length = 0;
  while(*str){
    length++; //increment counter while the string isn't empty
    str++;
  }
  return length;
 }

/*Get the number of chars before each space:
  token: "Ana "
  tokenSize = 3
*/

 int getTokenSize(char *token){
   int tokenSize = 0;
       while(*token != ' '){
	 tokenSize++;
	 token++;
         }
       return tokenSize;
     }
		    
/*Print each token in a new line */
void printTokenVec(char ** tokenVec, int wordCount){
  int numBytes = 0;
  for(int i = 0; i < wordCount; i++){
    numBytes = lengthOfCharArray(tokenVec[i]);
     write(1,tokenVec[i],numBytes);
     write(1, "\n", 1);
    }
  }

/*Returns 1 if two strings are equal.
  Used to exit the program*/
int compStrings(char *str1,char  *str2){

   while(*str1 && *str2){
     if(*str1 != *str2){
       return 0;
     }
     *str1++;
     *str2++;
   }
   return 1;
 }


/*Allocates each token in an array and
  returns a pointer to this array*/ 
 char ** mytoc(char *str, char delim){

 int wordCount = countWords(str, delim);
 //printf("wordCount: %d\n", wordCount);
 char** tokenVec = (char **)calloc(wordCount+1,sizeof(char *));
 tokenVec[wordCount] = (char *)0;//zero pointer terminator
 //printf("right before for loop\n");
 for(int i = 0; i < wordCount; i++){
   char * token = trimInitialSpaces(str);
   int tokenSize = getTokenSize(token);
   tokenVec[i] = allocateToken(token,delim, tokenSize);
   str = token + tokenSize;
 }
  printTokenVec(tokenVec,wordCount);
  return tokenVec; 
}
