/* 
 * stringcopy - a naive implementation, and buggy call
 *
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>

void stringcopy(char *sp, char *dp);

int main()
{
  char *src = "Computer Science 50";
  char *dest; 

  // copy src to dest and print them out
  stringcopy(src, dest);
  printf("src  = '%s'\n", src);
  printf("dest = '%s'\n", dest);
  return 0;
}

/* stringcopy - copy string from source sp to destination dp */
void stringcopy(char *sp, char *dp)
{
  while (*sp != '\0') {
    *dp++ = *sp++;
  }
  *dp = '\0';
}
