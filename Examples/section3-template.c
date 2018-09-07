/* 
 * section3.c - for Section meeting, week 3: exercise with pointers and malloc.
 * A program to read two lines from input and then output their concatenation.
 * 
 * you will need to 
 *  cp ~cs50/examples/section3-template.c section3.c
 *  cp ~cs50/examples/readlinep.[ch] .
 * and compile with
 *  mygcc section3.c readlinep.c -o section3
 *
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readlinep.h"  // from ~cs50/examples

/* main program */
int main(const int argc, char *argv[])
{
  char *line1 = readlinep();
  char *line2 = readlinep();

  if (line1 == NULL || line2 == NULL)
    exit(1);

  // allocate space for the result (and the terminating null)
  char *result = ...;

  // copy line1 into result

  // copy line2 into result

  // terminate string

  // print result
  puts(result);

  // clean up
  free(line1);
  free(line2);
}
