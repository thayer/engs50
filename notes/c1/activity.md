---
layout: page
title: Activity - C program
---

## Goals

To experience use of `mygcc` to compile C programs, to use editor to edit a C program, and to write some simple C code.

## Tasks

* Copy the `guessprime` program into your own directory, and compile it:

```bash
cd ~/cs50
cp ~cs50/examples/guessprime4.c guessprime.c
mygcc -o guessprime guessprime.c
```

* Try running the program a few times.

* Edit `guessprime.c` to add and call a new function:

```c
    // print the list of prime numbers from min to max inclusive
    void listPrimes(const int min, const int max);
```

and arrange to call it when the player gets the right answer:

```
Enter a prime between 1-100: 31
You win! here's a list of primes in [1..100]:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 
```

