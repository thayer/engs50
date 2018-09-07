/* 
 * pointer0 - characters, and character pointers.
 * 
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char c = 'x';		      // a character
  char *p = &c;		      // a pointer to a character
  char **pp = &p;	      // a pointer to a pointer to a character

  printf("c  = '%c'\n", c);
  printf("p  = %12p, *p = '%c'\n", p, *p);
  printf("pp = %12p, *pp = %12p, **pp = '%c'\n", pp, *pp, **pp);

  return 0;
}
