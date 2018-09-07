/* 
 * guessprime1.c - a C version of our simple bash demo program guessprime
 *  (simple replacement for the bash program)
 * David Kotz, April 2016
 */

// This is a one-line comment; modern syntax
/* This is another one-line comment; traditional syntax */

#include <stdio.h>
#include <stdlib.h>

int main() {
  const int answer = 31;
  int guess;

  printf("Enter a prime between 1-100: ");
  scanf("%d", &guess);

  while (guess != answer) {
    printf("Wrong! try again\n");
    printf("Enter a prime between 1-100: ");
    scanf("%d", &guess);
  }

  return 0;  // exit status
}


