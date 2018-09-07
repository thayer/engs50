// THIS EXAMPLE MAY NOT BE FOLLOWING CS50 STYLE GUIDELINES.
// File: unsafe threads

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

char s1[] = "abcdefg";
char s2[] = "xyz";

char* c;
void last_letter(char* a, int i) {
  printf("last_letter ( a is %s and i is %d)\n", a, i);
  sleep(i);
  //c = NULL;   // uncomment out, what is different?
  sleep(i);
  c = a;
  sleep(i); 
  while (*c) {
    c++;
  }
  printf("%c\n", *(c-1));
  return;
}


// This function will run concurrently.

void* aa(void *ptr) {
  last_letter(s2, 2);
  return NULL;
}

int main() {
  pthread_t t1;
  int iret1 = pthread_create(&t1, NULL, aa, NULL);
  if (iret1) {
    fprintf(stderr,"Cannot create thread, rc=%d\n", iret1);
  }
  last_letter(s1, 5);
  sleep(10);
  printf("Ended nicely this time\n");
  return 0; //never reached when c = NULL is not commented out.
}
