/* 
 * pointer2 - a short program to demonstrate memory addresses.
 * 
 * David Kotz, April 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables
const int fifteen = 15;

void change(int *a, int b);

int main()
{
  // local variables are on the stack
  int x = 2, y = 5;

  // global variables; note they are in low memory addresses
  printf("globals\n");
  printf(" fifteen @ %12p has value %d\n", &fifteen, fifteen);

  // main() is a function, and its code is at an address too!
  printf("main @ %12p\n", main);

  // local variables are on the stack
  printf(" x @ %12p has value %d\n", &x, x);
  printf(" y @ %12p has value %d\n", &y, y);

  // pass x by reference, y by value
  change(&x,y);

  // see whether those changed
  printf("main @ %12p\n", main);
  printf(" x @ %12p has value %d\n", &x, x);
  printf(" y @ %12p has value %d\n", &y, y);

  return 0;
}

void change(int *a, int b)
{
  // as above, change() is a function, and its parameters and local variables are on the stack
  printf("change @ %12p\n", change);  
  printf(" a @ %12p has value %d at %12p\n", &a, *a, a);
  printf(" b @ %12p has value %d\n", &b, b);
  // attempt to change the values
  *a = 99;
  b = 99;
}
