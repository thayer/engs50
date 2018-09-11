---
layout: page
title: Dynamic memory allocation; linked lists
---

### Goals

* To understand that `malloc` and `free` allocate and de-allocate memory from the heap.
* To use dynamic memory to build a linked list.

Terminal [script](script.txt) from today's class.

### Background

We'll be working with C code that builds and manipulates *linked lists*.
You learned about linked lists in CS10, and may want to review the CS10 linked-list notes and implementation:

* slides in [pdf](cs10-lists.pdf) or [Powerpoint](cs10-lists.pptx)
* [SinglyLinked.java](SinglyLinked.java)
* [SimpleList.java](SimpleList.java)

# Dynamic memory allocation

Before we dive in, check out this [animated explanation of pointers](https://www.youtube.com/watch?v=5VnDaHBi8dM).
Fun!

C does not have language support for dynamically allocating new 'things'.
Instead, the programmer has to call a library function called `malloc()` to allocate a new chunk of memory from the *heap segment*, and later call `free()` to return that chunk of memory to the heap.
The programmer has to remember to initialize the chunk of bytes received from `malloc()` -- which otherwise should be assumed to contain random data.
The programmer has to be careful allocate a large enough chunk to hold the data she intends to store there, and not to use pointers to write "outside" that chunk of memory.
Lots of flexibility and power - but as with any great power, you must take great care in using it.

> In Java, you can use `new` to dynamically create a new object, and `delete` to discard an object created with `new`, but for the most part the Java compiler and runtime handles object deletion and memory recovery automatically - it's called 'garbage collection.'


There are four related functions you should understand:

* **malloc** `p = malloc(n)` - allocates `n` bytes of heap memory; the memory contents remain uninitialized.
* **calloc** `p = calloc(count, size)` allocates `count*size` bytes of heap memory and initializes it all to zero; this call is appropriate when you want to allocate an array of `count` items, each of `size` bytes.
* **realloc** `p = realloc(p, n)` - where `p` is a pointer to heap memory - expands (or shrinks) its allocation to `n` bytes.
* **free** `free(p)` - where `p` is a pointer to heap memory - releases that portion of heap memory for future use.

Our examples today show how to use `malloc` to allocate space to store a string, and later, a `struct` holding aggregate types.
For an example using `calloc` and `realloc`, read about [how readlinep() works]({{site.lectures}}/malloc/readlinep.html).

## Memory leaks and stray pointers

***For every `malloc` there must be a matching `free`.***

* If you allocate space but never free it, you've created a *memory leak*; as the program runs, the process memory size will grow and grow, and eventually run out of memory.
* If you free a pointer you've never allocated - or free the same pointer twice - you may cause the heap manager to corrupt its data structures and trigger a segmentation fault at some future time - often a seemingly random time.

Whenever you write `malloc`, write the corresponding `free` call; or, document whose responsibility is to `free` that pointer.

Whenever you call `free(p)`, it's good practice to immediately set `p=NULL`.
Not because you have to - it makes no difference to the heap - but because that step will prevent you from accidentally re-using that now-defunct pointer `p` - you'll get a clean segmentation fault instead of unpredictable behavior.

> When the process exits, all its memory is free - the four segments (code, global, stack, and heap) disappear.

## Coding style - memory allocation

Avoid sprinking calls to `malloc()` and `free()` throughout your code.
Instead, think about the kinds of things you need to create and destroy, and write type-specific wrapper for each such type.
For example, if your program manipulates things of type `struct listnode`, you would write two functions:

```c
    struct listnode *listnode_new(...);
    void listnode_free(struct listnode *node);
```

The first function calls `malloc(sizeof(struct listnode))` and initializes all of its contents, perhaps using parameters passed by the caller.
The second calls `free(node)`.
Both involve careful error-checking code.
See example [names7.c]({{site.examples}}/names7.c).

There are many advantages to this approach:

* The mainline code is more readable, because it's clear what `listnode_new()` is doing.
* The `new` function acts like a 'constructor' in object-oriented languages and can ensure the newly returned memory is initialized, or at least, not random bytes.
* Code involving `malloc` can sometimes be tricky, and you isolate that trickiness in one spot and focus on getting it right once.
* Some new types might need multiple `malloc` calls, as in our linked-list examples [names5.c]({{site.examples}}/names5.c) [names6.c]({{site.examples}}/names6.c) [names7.c]({{site.examples}}/names7.c).
All those `malloc` calls (and corresponding `free` calls) can be in the `new`/`free` functions.
* You can insert debugging output or reference-counting logic, or set debugger breakpoints, in these `new`/`free` functions and immediately have that feature apply to *all* occurrences of your program's work with this type.

# Data structures in C

C is not an object-oriented language like Java, Python, or C++.
It does not provide any language features to declare a 'class' or create and manipulate object 'instances' of that class.

But C does provide two kinds of aggregate data: arrays and structures.


## Arrays

We've seen examples with arrays of characters (aka strings) and arrays of character pointers, and even two-dimensional arrays of characters.
But one can also define arrays of other types:

```c
	char names[NumStudents][NameLength];
	int ages[NumStudents];
	float grades[NumStudents];
```

and so forth.

> Sometimes you need to understand that an array name is, in effect, a pointer to the first spot in memory where that array's data lives; thus, `ages` is of type `int*` and is a pointer to the first entry in the array, but `ages[0]` is of type `int` and is the value of that first entry in the array.
> This concept comes up mostly in arrays of characters; `names` is of type `char**`, and even `names[0]` is of type `char*`, and `names[0][1]` is of type `char`.
> In effect, `names` is an array of strings, and `names[0]` is the first string in the array; like other strings, `names[0]` is of type `char*`.

## Structs

C allows you to define an aggregate called a 'struct'; like an object, it has data members.
Unlike an object, it has no methods (function members).

Continuing our above example, we could have defined a `struct` for each student, and then an array of `structs`, as follows:

```c
   struct student {
       char name[NameLength];
       int age;
       float grade;
   };
   struct student students[NumStudents];
```

Now we can refer to the first student as `student[0]`, the second student as `student[1]`, and so forth.
We can refer to the name of the first student as `student[0].name` and the age of the second student as `student[1].age`.

In our classtime examples, [names5.c]({{site.examples}}/names5.c), [names6.c]({{site.examples}}/names5.c), and [names7.c]({{site.examples}}/names7.c), we declare a `struct listnode` and use it to build a linked list.
There we see a different notation: instead of `.` to refer to a member of a struct, we have to use `->` to dereference the pointer and refer to member of the pointee.

```c
   struct student alice;        // a single struct representing alice
   struct student *sp = &alice; // a pointer, initialized to point at alice

   // the following three all do the same thing.
   int age = alice.age;
   int age = sp->age;
   int age = (*sp).age;
```

## Linked lists

In the examples below we construct a simple linked list comprising nodes that each have a pointer to a string and a pointer to the next node.
The list includes a dummy *head node* to simplify list management.
The variable `head` is a pointer to that dummy node.

```c
// A structure for each node in linked list
struct listnode {
  char *name;
  struct listnode *next;
};
struct listnode head = {NULL, NULL}; // dummy node at head of empty list
```

After adding three nodes, the list might look like this:

![](linked-list.png)

## Examples

We first live-coded a simple revision of the `names` program, using an array of pointers instead of a two-dimensional array of characters:

* [names3.c]({{site.examples}}/names3.c): array of pointers; use of `readlinep`

Here, the two-dimensional `names` array is replaced by a one-dimensional array of string pointers, which is more common in C, and which allows the names to be of any length - each array entry points to a dynamically allocated memory from the heap, big enough to hold that name.

We use a new `freadlinep` function; after the next lecture, I recommend you read about its [implementation](../readlinep.html).

We don't have time in class, but we can extend this code to sort the array using `qsort()` quicksort:

* [names4.c]({{site.examples}}/names4.c): sort names; `void*`; casting

Then we live-coded a linked-list version of the `names` program:

* [names5.c]({{site.examples}}/names5.c) -  revises names3.c to use linked list instead of array

You should look at two more versions of the `names` program:

* [names6.c]({{site.examples}}/names6.c) - extends names5.c to keep the list sorted
* [names7.c]({{site.examples}}/names7.c) - extends names6.c to remove duplicates

## Activity

Today's [activity](activity.html) deletes the list.
