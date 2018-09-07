---
layout: page
title: Modular data structures in C
---

In this class we focus on the design of reusable modules for common data structures.


### Goals

 * Understanding the importance of reusable modules.
 * Reiterating the use of header files to enable modules.
 * Reiterating `struct` and introducing `typedef`.
 * General-purpose data structures with `void*`.
 * Function pointers.

## Modularity and reuse

Some data structures are so common that it is valuable to code them once - lists, queues, stacks, trees, and hash tables - and then re-use that code for multiple programs (or multiple purposes within a program).
Code re-use saves time because you don't need to write everything from scratch.
By using robust, well-tested modules rather than fresh (buggy) code, your program is more reliable.
Finally, by separating 'business logic' from 'data structures', you the code is clearer and more flexible (e.g., if you later want to switch to a more-efficient data structure you can do so without rewriting all the business logic).

Object-oriented languages make this easier, because they make it simple to define a 'class' of objects and then to create new 'instances' as needed.
Many such languages go further by providing 'templates' and 'subclasses' as a way to derive new variants of the base class.

C has none of these capabilities.
But we can approximate some of these concepts through good style and careful design.

### Pointers to anything

In developing a general-purpose data-structure module, we would really like the module to be able to store arbitary "things" -- not just predetermined types -- but anything.
For example, instead of a linked-list of strings (as we built in the `names` program) we'd like a linked-list that could store pointers to anything.
Today we want a list of string things; tomorrow we might want a list of `struct student` things.

The solution is for the module to store *pointers to things*, rather than the things themselves.
The user's contract with the module is thus "I allocate and initialize a thing, and give you a pointer to remember; later, when I need that thing, I'll ask and you give me back that pointer.
When I ask you to print things, or delete things, I'll give you customized functions that know how to print and delete things of this type."

Java and other object-oriented languages do this with *templates*.
C has no suport for templates, but it does have a type for "pointer to anything":  `void*`.
Thus,

```c
char *p = "hello";	   // pointer to a char, in this case, a string
int x = 42, *xp = &x;  // pointer to an int
struct student * sp;   // pointer to a struct
sp = malloc(sizeof(struct student)); // initialize the pointer
sp->name = "David";  // initialize the struct at that pointer
sp->house = "West";  // ...initialize
sp->class = 1986;    // ...initialize

void *anything;       // a pointer to any type
anything = p;         // here, a pointer to a char on the stack
anything = &x;        // here, a pointer to an int on the stack
anything = sp;        // here, a pointer to a struct in the heap
```

Thus, our modules will accept and store `void*` pointers, and return them to the caller when asked.

### Pointers to functions

As noted above, the module may need help when it needs to print, compare, or delete "things".
The module's user must provide the module with special helper functions.
(In an object-oriented language, like Java, "things" are objects and objects know how to print themselves, compare themselves, or delete themselves.
C has no such support.)

Thus, the caller may pass a function to the module, when needed.
We can't actually pass the function - we have to pass the module a pointer to the function.

The concept of a *pointer to a function* can be confusing.
Like any other pointer, it is an address in memory.
Recall that the compiled code of the program lives in the code segment, in memory, so every function resides at some address.
A function pointer is simply that address.

We can refer to the function's address simply by naming the function, without the syntax of calling a function.
That is, `foo` is a function pointer, whereas `foo(a, b, c)` calls that function and passes arguments `a`, `b`, and `c`.
In our [pointer2.c]({{site.examples}}pointer2.c}}) example, we passed the address of functions `main` and `change` to `printf` so it could print those addresses for us to examine.

If I have a function called `myprint`, like this:

```c
void myprint(FILE *fp, char *key, void *item)
{
	int *valuep = item; // in this case, the "things" are integers
	fprintf(fp, "(%s, %d)", key, *valuep); // note *valuep derefs pointer
}
```

If I have a function pointer `printfunc`, I can initialize the function pointer and call through that pointer as follows:

```c
printfunc = myprint;
(*printfunc)(fp, key, thing);
```

In other words, I dereference the pointer to get a function, and then call that function.
Notice the `*` and parens, `(*printfunc)`.

How would I declare that variable `printfunc`?
pretty gnarly syntax:

```c
void (*printfunc)(FILE *fp, char *key, void *item);
```

declares variable `printfunc` to be a pointer to a function whose prototype looks like that of `myprint` above, that is, it takes the given three arguments and returns `void`.
Indeed, it looks almost like a common function prototype, except for that `(*variablename)` notation.
For this pointer to be useful, it must be initialized to the address of a function.


## Example - bags

Today we live-code a *bag* data structure and use it to make a bag version of our `names` series.
A *bag* is an unordered collection of (items).
The bag starts empty, grows as the caller adds one item at a time, and shrinks as the caller extracts one item at a time.
It could be empty, or could contain hundreds of items.
Items are indistinguishable, so the *extract* function is free to return any item from the bag.

We start from [names5.c]({{site.examples}}/names5.c) and modify it with the goal of coding functions that manipulate a generic "bag of things".

The first example demonstrates

 * structure types (like `struct bag_t` and `struct bagnode_t`).
 * typedefs to create new type names.
 * Heap memory (created via `malloc` in `bag_new`).
 * The use of pointers to build and manipulate a bag data structure.
 * The use of `void*` to represent "a pointer to anything" and its use to build a bag of generic things.
 * A reminder that strings - even constant strings, in double quotes - are stored in memory as arrays of characters and referenced by a `char*` pointer to their first character; thus even a constant string has an address and is passed as a pointer.

We extend the example to split the bag functions out as to a separate set of files, demonstrating

 * a *module*, which is as close as we get to a *class* in C.
 * A set of functions exported via `bag.h` to other C files.
 * Public types (like `struct bag_t`) - and opaque types.
 * Private types (like `struct bagnode_t`).
 * Private functions (like `bagnode_new`).
 * No need for global variables.  (We always try to avoid them!)

The result, after some cleanup, is [names9.c]({{site.examples}}/names9.c).

A complete *bag* module is included in the [Lab 3 starter kit]({{site.labs}}/Lab3/starter).

## Another example - binary trees

For a more complex example, demonstrating the use of binary trees as a "dictionary" data structure -- that is, one that stores (key,item) pairs -- study the [binary-tree module]({{site.examples}}/trees).

## Activity

In today's class [activity](activity.html), we add a counter to track the number of items in the bag.

