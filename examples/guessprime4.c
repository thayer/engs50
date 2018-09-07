/* 
 * guessprime4.c - a C version of our bash demo program
 *  (add isPrime() function; check bounds of input; args in prototypes)
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// function prototype *declarations*
int readGuess(void);
bool isPrime(const int p);

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
int readGuess(void) {
  int guess;

  printf("Enter a prime between 1-100: ");
  scanf("%d", &guess);

  if (guess < 1 || guess > 100) {
    printf("Hey! %d is out of range [1..100].\n", guess);
  }
    
  if (!isPrime(guess)) {
    printf("Hey! %d is not even a prime number.\n", guess);
  }

  return guess;
}


// determine whether the number is prime
// (assumes n <= 100)
bool isPrime(const int n) {
  if (n < 2) return false;
  if (n > 2 && n%2 == 0) return false;
  if (n > 3 && n%3 == 0) return false;
  if (n > 5 && n%5 == 0) return false;
  if (n > 7 && n%7 == 0) return false;
  return true;
}
