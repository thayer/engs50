/* 
 * names2.c - read in a list of names from stdin
 *   (truncating each name)
 * 
 * usage: names < infile
 * stdin: list of names, one per line; first name ends in period.
 * stdout: list of first names
 * 
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

int main()
{
  const int maxNames = 100;  // maximum number of names
  const int maxLength = 50;  // maximum length of a name
  char names[maxNames][maxLength];
  int n = 0;		     // number of names read

  // read the list of names
  for (n = 0; n < maxNames && !feof(stdin); ) {
    if (readline(names[n], maxLength))
      n++; // only increment if no error
  }

  // truncate the names at period (.)
  for (int i = 0; i < n; i++) {
    char *p = names[i];
    while (*p != '\0' && *p != '.')
      p++; // skip ahead until . is found
    *p = '\0'; // truncate
  }

  printf("%d names: ", n);
  // print the list of names
  for (int i = 0; i < n; i++) {
    printf("%s ", names[i]);
  }
  putchar('\n');
}
