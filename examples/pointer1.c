/* 
 * pointer1 - a short program to demonstrate pointers.
 * 
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *CS = "Computer Science";

int main()
{
  printf(" CS = %12p, *CS = '%c', CS as string = '%s'\n", CS, *CS, CS);

  for (char *p = CS; *p != '\0'; p++) {
    printf(" p = %12p, *p = '%c'\n", p, *p);
  }

  return 0;
}
