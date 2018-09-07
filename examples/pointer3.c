/* 
 * pointer3 - a short program to demonstrate memory addresses.
 * 
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char *hello = "hello world!";
  char buf[15];

  strcpy(buf, "something"); // initialize buf

  // local variables are on the stack
  printf(" hello @ %12p has value '%s', which resides at %12p\n", &hello, hello, hello);
  printf(" buf @ %12p has value '%s', which resides at %12p\n", &buf, buf, buf);

  // malloc allocates space on the heap
  hello = (char *)malloc(10);
  strcpy(hello, "new stuff");
  printf(" now hello @ %12p has value '%s', which resides at %12p\n", &hello, hello, hello);
  // free lets the heap re-use that space
  free(hello);
  printf(" note hello @ %12p still points to %12p\n", &hello, hello);
  
  return 0;
}
