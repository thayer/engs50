---
layout: page
title: Allocating an array with calloc
---

We've seen the use of a one-dimensional array of pointers to strings, in [names3.c]({{site.examples}}/names3.c).
In that case, the number of slots in the array was a constant.
What if we don't know that number at compile time?

Here's a snippet of code to hint at how to allocate an array of `num` slots:

```c
// the number of elements in the array
int num = ...; // somehow obtained; below we assume num>=2
...
// array of ints
int *array = calloc(num, sizeof(int));
array[1] = 42;

// array of pointers to int
int **array = calloc(num, sizeof(int*));
array[1] = malloc(sizeof(int));
*array[1] = 42;

// for other types, the process is analogous
struct foo **array = calloc(num, sizeof(struct foo*);
array[1] = malloc(sizeof(struct foo));
array[1]->foomember = 42; // assuming foomember is an integer member of struct foo

// or, sometimes, you don't know how to initialize the structure
// because it provides a 'constructor' function. first step is the same:
struct foo **array = calloc(num, sizeof(struct foo*);
array[1] = foo_new(42); // let the constructor allocate and initialize a new foo.
```
