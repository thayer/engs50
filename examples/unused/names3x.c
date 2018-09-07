/* 
 * names3.c - read in a list of names from stdin
 *   (use malloc; sort names; casting)
 *
 * usage: names < infile
 * stdin: list of names, one per line; first name ends in period.
 * stdout: list of first names, sorted
 * 
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"

void trunchar(char *p, char c);
int strcmpp(const void* a, const void* b);

int main()
{
  const int maxNames = 100;  // maximum number of names
  char *names[maxNames];
  const int lineLength = 50; // maximum length of a name
  char line[lineLength];     // buffer for reading lines
  int n = 0;		     // number of names read

  // read the list of names
  for (n = 0; n < maxNames && !feof(stdin); ) {
    if (readline(line, lineLength)) {
      // truncate at the first period ('.')
      trunchar(line, '.');
      // allocate memory to store the (shortened) name
      names[n] = malloc(strlen(line)+1);
      if (names[n] != NULL) {
	strcpy(names[n], line);
	n++; // only increment if no error
      }
    }
  }

  // sort the list
  qsort(names, n, sizeof(char*), strcmpp);

  printf("%d names: ", n);
  // print the list of names
  for (int i = 0; i < n; i++) {
    printf("%s ", names[i]);
  }
  putchar('\n');
}


// trunchar:  truncate string at given character 
void trunchar(char *p, char c)
{
  while (*p != '\0' && *p != c)
    p++; // skip ahead until . is found
  *p = '\0'; // truncate
}


// strcmpp: like strcmp but args passed as char** instead of char*,
// compatible with qsort.  Cast each argument as needed.
// from http://arstechnica.com/civis/viewtopic.php?f=20&t=607813
int strcmpp(const void* a, const void* b)
{
  return strcmp(*((char**) a), *((char**) b));
}

