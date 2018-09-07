---
layout: page
title: Extra - Unix threads
---

This *Lecture extra* was written for earlier iterations of CS50 and has been touched up a little but not fully updated for this term.

### Goals

-   Creating a thread
-   Unpredictability
-   Safe and unsafe threads
-   Mutex
-   Deadlock issues

## Why threads?

From YoLinux:

> The POSIX thread libraries are a standards based thread API for C/C++.
It allows one to spawn a new concurrent process flow.
It is most effective on multi-processor or multi-core systems where the process flow can be scheduled to run on another processor thus gaining speed through parallel or distributed processing.
>
> Threads require less overhead than "forking" or spawning a new process because the system does not initialize a new system virtual memory space and environment for the process.
>
> While most effective on a multiprocessor or multi-core systems, gains are also found on uniprocessor systems which exploit latency in I/O and other system functions which may halt process execution.
(i.e., one thread may execute while another is waiting for I/O or some other system latency.) Parallel programming technologies such as MPI and PVM are used in a distributed computing environment while threads are limited to a single computer system.
All threads within a process share the same address space.
A thread is spawned by defining a function and its arguments which will be processed in the thread.
The purpose of using the POSIX thread library in your software is to execute software faster.

## What's *POSIX*?

It's not a Dr. Seuss character !

POSIX is an acronym for "Portable Operating System Interface [for Unix]" which is the name of a set of related standards specified by the IEEE.

## What's a thread?

What is a thread? Well we have studied the forking of process to support concurrency.
Threads are units of control that execute within the context of a single process representing multiple strands of indepenent execution.

What is the difference between forking processes and threads?
Well typically when a process is forked it executes as new independent process with its own PID and a copy of the code and resources of the parent process.
It is scheduled by the OS as a independent process.
A process has a single thread by default called `main()`.
Threads running in a process gettheir own stack and run concurrently and have access to process state such as open files, global variables, etc.

You will have to use multiple processes or threads for for the Amazing project - your choice.

In this lecture, we will just look at a number of simple examples of code to illustrate how threads are created and how we can implement mutual exclusion using `mutex` for shared resouces.
These notes are not meant to be exhaustive - they are not.

For a in depth look at pthreads read the following tutorial - it may help answer questions that you may have not covered in the class: [POSIX Threads Programming, Blaise Barney, Lawrence Livermore National Laboratory](https://computing.llnl.gov/tutorials/pthreads/)

Also, type `man pthread` for information on syntax, etc.

### Thread Creation

You have to write C code to create a thread.
If you do it right, when it runs that C code will create a new thread of execution that runs at the same time!
Here's a very simple example ([print_i.c]({{site.examples}}/print_i.c)):

```c
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
```

and its output:

```bash
$ ./print_i
1
2
2
3
3
4
4
5
5
6
6
^C
$ 
```

### Unpredictability

You cannot always predict the exact sequence of execution of threads running in parallel.
Lots of factors affect how often and long a thread actually gets to execute: the amount of real memory, number of processors and/or cores, and what the thread's code is trying to do (e.g., I/O, computation, system call, etc.), among others.

In the following example, [random.c]({{site.examples}}/random.c), what gets output first?
We do not know what order the values will be written out.
If the main thread completes before the `print_i()` thread has executed then it will die.

```c
// THIS EXAMPLE MAY NOT BE FOLLOWING CS50 STYLE GUIDELINES.
// File: random.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// This function will run concurrently.
void* print_i(void *ptr) 
{
    printf("a\n");
    printf("b\n");
    return 0;
}

int main() 
{
  pthread_t t1;

  int iret1 = pthread_create(&t1, NULL, print_i, NULL);
  if (iret1) 
  {
        fprintf(stderr, "thread creation failed, rc=%d.\n", iret1);
        return (iret1);
  } 
  printf("c\n");

  return 0;
}
```

Here's the output from several runs:

```bash
$ ./random
c

$ ./random
c

$ ./random
c

$ ./random
c
a
a
b

$ ./random
c
a
a
b

$ ./random
c

$ 
```

### Functions that are not *thread safe*

Most (but not all) of the libraries you get with `gcc` are thread safe.
This means that regardless of how many threads might be executing the very same function's code,

-   the code still works as expected,
-   the threads cannot interact or interfere with each other,
-   if there is any data shared by all the threads, that data can only ever be accessed by one thread at a time

This is usually accomplished by ensuring all the variables used by the thread are stored on its stack (rather than global variables).
If there is shared data, access to that shared data is typically serialized using some sort of mutual exclusion mechanism (more on this later).

Here's the [unsafe.c]({{site.examples}}/unsafe.c) example:

```c
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
```

And here's the output, first with the `c = NULL` commented out, and then with it not commented out.

```bash
# comment out the "c = NULL;" line
$ vi unsafe.c

$ mygcc -o unsafe unsafe.c -lpthread

$ ./unsafe
last_letter ( a is abcdefg and i is 5)
last_letter ( a is xyz and i is 2)
z
g
Ended nicely this time

# uncomment the "c = NULL;" line
$ vi unsafe.c

$ mygcc -o unsafe unsafe.c -lpthread

$ ./unsafe
last_letter ( a is abcdefg and i is 5)
last_letter ( a is xyz and i is 2)
Segmentation fault (core dumped)

$ 
```

Can you see what happened?

### Mutual Exclusion (mutex) locks

Mutual Exclusion (mutex) is a mechanism to help manage concurrency in programs.
You can think of a *mutex* as a lock that controls when a process can enter specific sections of code.
There are two functions:

-   `pthread_mutex_lock(mutex)`:

    If the mutex is locked, this function will block until the lock is unlocked; then, it will lock the mutex.  On return, the mutex is locked.

-   `pthread_mutex_unlock(mutex)`:

    If the mutex is locked by some prior `pthread_mutex_lock()` function, this function will unlock the mutex; otherwise it does nothing.

In the following example, [mutex.c]({{site.examples}}/mutex.c), our goal is to ensure that at any time there is only one thread calling function `print()`.

```c
// THIS EXAMPLE MAY NOT BE FOLLOWING CS50 STYLE GUIDELINES.
// File: mutex.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

// try uncommenting and commenting the mutext below
// and look at the output

void print(char* a, char* b) {
  pthread_mutex_lock(&mutex1); // comment out
  printf("1: %s\n", a);
  sleep(1);
  printf("2: %s\n", b);
  pthread_mutex_unlock(&mutex1); // comment out
  
}


// These two functions will run concurrently.
void* print_i(void *ptr) {
  print("I am", " in i");
  return NULL;
}

void* print_j(void *ptr) {
  print("I am", " in j");
  return NULL;
}

int main() {
  pthread_t t1, t2;
  int iret1 = pthread_create(&t1, NULL, print_i, NULL);
  int iret2 = pthread_create(&t2, NULL, print_j, NULL);

  if (iret1 || iret2) {
    fprintf(stderr,"pthread_create failed: iret1=%d, iret2=%d\n", iret1, iret2);
  }
  else {
    sleep(8);
  }
  exit(0); //never reached.
}
```

Here's the output, first with the mutex commented out, and then with the mutex uncommented.

```bash
# mutex commented out
$ mygcc -o mutex mutex.c -lpthread

$ ./mutex
1: I am
1: I am
2:  in i
2:  in j

$ vi mutex.c
# mutex uncommented

$ mygcc -o mutex mutex.c -lpthread

$ ./mutex
1: I am
2:  in i
1: I am
2:  in j
$ 
```

### Deadlocks

Of course, you have to be careful with mutex - you could end up in a deadlock!
See the [deadlock.c]({{site.examples}}/deadlock.c) example below.

```c
// THIS EXAMPLE MAY NOT BE FOLLOWING CS50 STYLE GUIDELINES.
// File: deadlock.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;


// These two functions will run concurrently.
void* print_i(void *ptr) {
  pthread_mutex_lock(&mutex1);
  //sleep(1);         // comment and it works!
  pthread_mutex_lock(&mutex2);
  printf("I am in i\n");
  pthread_mutex_unlock(&mutex2);
  pthread_mutex_unlock(&mutex1);
  return NULL;
}

void* print_j(void *ptr) {
  pthread_mutex_lock(&mutex2);
  //sleep(1);         // comment and it works!
  pthread_mutex_lock(&mutex1);
  printf("I am in j\n");
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);
  return NULL;
}

int main() {
  pthread_t t1, t2;
  int iret1 = pthread_create(&t1, NULL, print_i, NULL);
  int iret2 = pthread_create(&t2, NULL, print_j, NULL);

 if (iret1 || iret2) {
    fprintf(stderr,"pthread_create failed: iret1=%d, iret2=%d\n", iret1, iret2);
  }
  else {
    sleep(4);
  }
  exit(0); //never reached.
}
```

Here's the output with the `sleep(1)` commented out, and then with the `sleep(1)` uncommented.

```bash
# sleep(1)'s commented out
$ mygcc -o deadlock deadlock.c

$ ./deadlock
I am in i
I am in j

# sleep(1)'s uncommented
$ mygcc -o deadlock deadlock.c

$ ./deadlock
$ 
```
