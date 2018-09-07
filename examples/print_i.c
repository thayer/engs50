// THIS EXAMPLE MAY NOT BE FOLLOWING CS50 STYLE GUIDELINES.
// File print_i.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// global variable to share data
int i;

// This function will run concurrently.
void* print_i(void *ptr) {
  while (1) {
    sleep(1);
    printf("%d\n", i);
  }
}

int main() {
  pthread_t t1;
  i = 1;
  int iret1 = pthread_create(&t1, NULL, print_i, NULL);
  while (1) {
    sleep(2);
    i = i + 1;
  }
  exit(0); //never reached.
}
