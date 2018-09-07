/* seuss.c - uses thing one and thing two. */

#include "one.h"
#include "two.h"

int main()
{
  int fun = thing_one() + thing_two();
  return fun; // exit status
}
