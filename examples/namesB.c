/* 
 * namesA.c - read in a list of names from stdin
 *  (derived from names9.c, to use an external 'bag')
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: list of names, one per line
 * 
 * David Kotz, April 2016, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file.h"
#include "bag.h"

void printname(FILE *fp, void* item);

/* ********************************************************* */
int main()
{
  int n = 0;			       // number of names read
  char *name;

  bag_t *bag = bag_new();
  if (bag == NULL)
    exit(1);

  // read the list of names - any number of names!
  while (!feof(stdin)) {
    name = readlinep(stdin);
    if (name != NULL) {
      bag_insert(bag, name);
      n++;
    }
  }
  
  // print the list of names
  printf("%d names:\n", n);
  bag_print(bag, stdout, printname);
  putchar('\n');

  // delete the bag and call free(item) for each item
  bag_delete(bag, free);

  return 0;
}

/* printname, for use with bag_print */
void printname(FILE *fp, void* item)
{
  char *name=item;
  fprintf(fp, "%s", name);
}
