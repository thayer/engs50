/* quickie functions to read string and int from stdin, one per line */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

// Read a string from the stdin and return pointer to new string;
// caller is responsible to later free that string.
// Caller may assume this function always succeeds.
char *readstring()
{
  char buf[BUFSIZ];
  if (fgets(buf, BUFSIZ, stdin)) {
    buf[strlen(buf)-1] = '\0'; //strip the newline
    
    char *result = malloc(strlen(buf)+1);
    strcpy(result, buf);
    return result;
  } else {
    char *result = malloc(strlen("error")+1);
    strcpy(result, "error");
    return result;
  }
}


// Read an integer from the stdin and return that value.
// Assume this function always succeeds.
int readint()
{
  char buf[BUFSIZ];
  fgets(buf, BUFSIZ, stdin);

  int result = 0;
  sscanf(buf, "%d\n", &result); // we casually assume it succeeds
  return result;
}
