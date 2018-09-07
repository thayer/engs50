/* 
 * guessprime2.c - a C version of our bash demo program guessprimefunction
 *  (add readGuess() function)
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>

// Prompt for, and read, one guess
int readGuess() {
  int guess;

  printf("Enter a prime between 1-100: ");
  scanf("%d", &guess);

  return guess;
}


// Main loop - ask for a guess, quit when it matches the answer
int main() {
  const int answer = 31;
  int guess;

  guess = readGuess();
  while (guess != answer) {
    printf("Wrong! try again\n");
    guess = readGuess();
  }

  return 0;  // exit status
}


