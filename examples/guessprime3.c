/* 
 * guessprime3.c - a C version of our bash demo program guessprimefunction
 *  (move readGuess() function to bottom, declare function prototype)
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>

int readGuess(); // function prototype *declaration*

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


// Prompt for, and read, one guess
// function *definition*
int readGuess() {
  int guess;

  printf("Enter a prime between 1-100: ");
  scanf("%d", &guess);

  return guess;
}


