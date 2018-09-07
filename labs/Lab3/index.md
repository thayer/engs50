---
layout: page
title: Lab 3 - Data structures in C
---

**Due Friday, April 20, at 10pm**

In this lab you'll code a set of data structures that will support the needs of the Tiny Search Engine (TSE).

* TOC
{:toc}

In this lab you will develop some general-purpose data structures that, with modular design, can be re-used for other labs - most notably, the Tiny Search Engine.

Grading will focus on [CS50 coding style]({{site.resources}}/CodingStyle.html) - including consistent formatting, selection of identifier names, and use of meaningful comments - in addition to correctness and testing.

***Your C code must compile without producing any compiler warnings.***  You will lose points if the compiler produces warnings when using our CS50-standard compiler flags.

***If your submitted code fails to compile, or triggers a segmentation fault,*** we'll notify you and give you an opportunity to repair and resubmit.
(See *[programs that crash]({{site.logistics}}/index.html#crashes).*) Write defensive code: each function should check its pointer parameters for NULL, and take some appropriate (safe) action.

## Assignment

Obtain our [starter kit](starter), which implements the `bag` module and includes the *readlinep* and *memory* module. Your assignment is to add three new modules, each of which defines a different data structure.

* (30 points) *`set`*
* (30 points) *`counters`*
* (40 points) *`hashtable`*

You can copy the starter kit to your own work directory on the CS department systems:

```bash
# assuming you've logged into a CS system
mkdir -p ~/cs50/labs/lab3
cp -r ~cs50/public_html/Labs/Lab3/starter/* ~/cs50/labs/lab3/
```

or to your Mac using `scp`:

```bash
scp -r username@flume:~cs50/public_html/Labs/Lab3/starter lab3
```

### About the data structures

The specific data structures are defined in the sections below.

In the table below, we compare these data structures with the two we explored in class.
Most of these data structures allow you to store a collection of "items".
Both the `set` and `hashtable` are examples of an abstract data structure called a *dictionary*, which provide methods like `insert(key, item)` and `item = retrieve(key)`, where the `key` allows the structure to distinguish among the items it stores.


| Behavior                | `list`       | `bag`      || `set`    | `counters`        | `hashtable` |
|:----------------------- |:---------- |:-------- ||:------ |:--------------- |:--------- |
| stores an *item*        | yes        | yes      || yes    | no              | yes       |
| uses a *key*            | no         | no       || yes    | yes             | yes       |
| keeps items in order    | yes        | no       || no     | no              | no        |
| retrieval               | first item | any item || by key | by key          | by key    |
| insertion of duplicates | allowed    | allowed  || error  | increment count | error     |

Notice that

* a `list` keeps _items_ in order, but a `bag` or a `set` does not.
* a `set` and `hashtable` allow you to retrieve a specific _item_ (indicated by its *key*) whereas a `bag` might return any _item_.
* because the `bag` and `list` don't distinguish among _items_ they store, they can hold duplicates; the others cannot.
* the `counters` data structure maintains a set of counters, each identified by a _key_, but it stores no _items_.
Instead, it keeps a counter for each key. Attempting to insert a duplicate _key_ results in an increment of the counter.

### bag

A `bag` is an unordered collection of _items_.
The `bag` starts empty, grows as the caller adds one _item_ at a time, and shrinks as the caller extracts one _item_ at a time.
It could be empty, or could contain hundreds of _items_.
_Items_ are indistinguishable, so the _extract_ function is free to return any _item_ from the `bag`.

The starter kit includes our `bag` module, which contains:
- `bag.c` implements a bag of `void*`, and exports **exactly** the following functions through `bag.h`:

```c
/* Create a new (empty) bag; return NULL if error. */
bag_t *bag_new(void);

/* Add new item to the bag; a NULL bag is ignored; a NULL item is ignored. */
void bag_insert(bag_t *bag, void *item);

/* Return any data item from the bag; return NULL if bag is NULL or empty. */
void *bag_extract(bag_t *bag);

/* Print the whole bag; provide the output file and func to print each item.
 * If fp==NULL; do nothing. If bag==NULL, print (null).
 * If itemprint==NULL, print nothing for each item.
 */
void bag_print(bag_t *bag, FILE *fp,
               void (*itemprint)(FILE *fp, void *item));

/* Iterate over the whole bag; call the given function on each item,
 * passing both the item and an argument. Ignore if NULL bag or NULL itemfunc.
 */
void bag_iterate(bag_t *bag, void *arg,
                 void (*itemfunc)(void *arg, void *item) );

/* Delete the whole bag; ignore NULL bag.
 * Provide a function that will delete each item (may be NULL).
 */
void bag_delete(bag_t *bag, void (*itemdelete)(void *item) );
```


### set

A `set` maintains an unordered collection of _(key,item)_ pairs; any given _key_ can only occur in the `set` once.
It starts out empty and grows as the caller inserts new _(key,item)_ pairs.
The caller can retrieve _items_ by asking for their _key_, but cannot remove or update pairs.
Items are distinguished by their _key_.

Your `set.c` should implement a `set` of `void*` with `char*` _keys_, and export **exactly** the following functions through `set.h`:

```c
/* Create a new (empty) set; return NULL if error. */
set_t *set_new(void);

/* Insert item, identified by a key (string), into the given set.
 * The key string is copied for use by the set.
 * Return false if key exists, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool set_insert(set_t *set, const char *key, void *item);

/* Return the item associated with the given key;
 * return NULL if set is NULL, key is NULL, or key is not found.
 */
void *set_find(set_t *set, const char *key);

/* Print the whole set; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL set.
 * Print a set with no items if NULL itemprint.
*/
void set_print(set_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) );

/* Iterate over all items in the set, in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If set==NULL or itemfunc==NULL, do nothing.
 */
void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete the whole set; ignore NULL set.
 * Provide a function that will delete each item (may be NULL).
 */
void set_delete(set_t *set, void (*itemdelete)(void *item) );
```

### counters

A _counter set_ is a `set` of counters, each distinguished by an integer _key_.
It's a `set` - each _key_ can only occur once in the `set` - but instead of storing _(key,item)_ pairs, it tracks a `counter` for each _key_.
It starts empty.
Each time `counters_add` is called on a given _key_, that _key_'s `counter` is incremented.
The current `counter` value can be retrieved by asking for the relevant _key_.

Your `counters.c` should implement a set of integer counters with `int` _keys_ (where _keys_ must be non-negative) and export **exactly** the following functions through `counters.h`:

```c
/* Create a new (empty) counter structure; return NULL if error. */
counters_t *counters_new(void);

/* Increment the counter indicated by key; key must be >= 0.
 * If the key does not yet exist, create a counter for it and initialize to 1.
 * Ignore if ctrs is NULL or key is negative.
 */
void counters_add(counters_t *ctrs, const int key);

/* Return current value of counter associated with the given key;
 * return 0 if ctrs is NULL or if key is not found.
 */
int counters_get(counters_t *ctrs, const int key);

/* Set the current value of counter associated with the given key;
 * If the key does not yet exist, create a counter for it and initialize to
 * the given value. Ignore if ctrs is NULL, if key < 0, or count < 0.
 */
void counters_set(counters_t *ctrs, const int key, int count);

/* Print all counters; provide the output file.
 * Ignore if NULL fp. Print (null) if NULL ctrs.
 */
void counters_print(counters_t *ctrs, FILE *fp);

/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 * If ctrs==NULL or itemfunc==NULL, do nothing.
 */
void counters_iterate(counters_t *ctrs, void *arg,
                      void (*itemfunc)(void *arg, const int key, int count));

/* Delete the whole counters. ignore NULL ctrs. */
void counters_delete(counters_t *ctrs);
```

### hashtable

A `hashtable` is a `set` of _(key,item)_ pairs.
It acts just like a `set`, but is far more efficient for large collections.

Your `hashtable.c` should implement a `set` of `void*` with `char*` _keys_, and export *exactly* the following functions through `hashtable.h`:

```c
/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots);

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item);

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key);

/* Print the whole table; provide the output file and func to print each item.
 * Ignore if NULL fp. Print (null) if NULL ht.
 * Print a table with no items if NULL itemprint.
 */
void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item));

/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) );

/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) );
```

The starter kit provides code for the hash function.		

### General notes

* Your modules must implement *exactly* the above interface.
Do not modify those function prototypes.
* If you need helper functions or data types (likely `struct` types), those should be defined within your `module.c` and marked `static` so they are not visible to users of the module.
* Your modules must print *nothing* (except, of course, in the `xxx_print()` function).
If you want to add debugging `printf`s, they must be protected by something like `#ifdef DEBUG` or `#ifdef TEST`.
(You can see some examples in `bag.c` where we've protected some debugging code with `#ifdef MEMTEST`, and a spot in the `bag/Makefile` that controls that flag from the compiler command line.)
* Your modules must have no global variables.
* Your modules must have no `main()` function; as modules, they are meant to be used by other programs.
Recall how the module defined by `bag.c` and `bag.h` is used by a test program `bagtest.c`.
* Your modules store `void*` items; this type is C's way of describing a "pointer to anything".
The caller (user of your module) must pass a pointer (address of some item) to your code; your data structure holds that pointer, and later returns it to the caller in response to an 'extract' or 'find' operation.
Your module doesn't know, or doesn't care, what kind of things the items are.
Your module doesn't allocate memory for items, free memory for items, or copy items - it just tracks the *pointer* to the item.
* For all modules, the *caller* is responsible for the *item* pointer, which must be allocated (somehow) by the caller.
The modules' `_delete` function (like a destructor) allows the caller to provide a custom `itemdelete` function that knows how to free any memory consumed by an item.
* For this reason, the caller must avoid inserting the same item (same address) multiple times; later, the `itemdelete` method would be called multiple times on that item... which could lead to trouble.
* Both `set` and `hashtable` work with string-type keys.
When adding a new item with `set_insert()` or `hashtable_insert()`, both modules make their own copy of the string - presumably in memory allocated by `malloc()`.
(The module is then responsible for this memory - and later freeing it - just like any other memory it allocates.)  This 'copy' semantic is convenient for the caller, who need not worry about how to allocate and manage the key string after inserting it into the set or hashtable.
* You may assume that a non-NULL `key` is a proper C string; that is, it is null-terminated.
* You may use the *memory* module - or use the native `malloc` and `free`, and you
may use `valgrind` - or not.
However, we will be checking your code for memory leaks.
* Your modules must each have a `Makefile` to compile and test the module code.
* Your directory for module `x` must, therefore, have an `xtest.c` program.

## Hints

You are encouraged to follow the style and layout of the `bag` module when developing new modules.

You can also learn a lot from our [binary trees]({{site.examples}}/trees) example.
You are welcome to copy snippets of code from this (or any other) CS50 example code as long as you add a comment indicating you've done so.

We suggest implementing the `set` and `counters` as simplified linked lists, much like we did for `bag`.
Each should be a separate implementation because they differ in detail and semantics.

Your `hashtable` module, on the other hand, should make use of the `set` data structure.
Indeed, your hashtable will be an array of pointers to sets.
Allocating an array of pointers can be tricky; consider these [tips](array-allocate.html).

***Linked lists*** were demonstrated in [names6.c]({{site.examples}}/names6.c), although for a specialized case; you will need to generalize.
They were also covered in CS10; see the [notes](http://www.cs.dartmouth.edu/~tjp/cs10/notes6.php).

***Hashtables were also covered in CS10:***
[notes](http://www.cs.dartmouth.edu/~tjp/cs10/notes11.php),
[slides](cs10-hashtables.pdf).

## What to hand in, and how

Make sure to compile and test your solutions on one of the [CS Linux systems](http://www.cs.dartmouth.edu/~wbc/suditour/011/index.html) before submission.
If you choose to develop your solutions on some other system, you are responsible to ensure that the work you submit runs correctly on a CS system --- which is where where we will test it!

Indeed, you must place your solutions in your `cs50/labs/lab3` directory on the department Linux servers.
(If you worked on your laptop, use `scp` to copy files from your laptop to the server.)


In addition to your code, each of the four subdirectories of `lab3` must include two simple text files:

1. `README`,
         which describes how your program should be compiled and executed, along with an explanation of any assumptions you made about the assignment.
See the [README.md](starter/bag/README.md) for the `bag` module.

2.  `TESTING`,
         which describes how you tested the program, including any test inputs, test programs, and test scripts; these test files should be included in your submission.
See the [TESTING.md](starter/bag/TESTING.md) for the `bag` module in the starter kit.

> These examples are written in [Markdown]({{site.resources}}/index.html#markdown) format; hence the filename extension `.md`.
> You'll need to use Markdown in later labs, so now's a great time to learn.
> In this lab, the use of Markdown is optional.

Think of your audience for each file:

* the `README` file is written for the user of your module.
For example, [bag/README.md](starter/bag/README.md) refers to the interface (`bag.h`) and describe any assumptions, implementation details, or compilation instructions (basically, `make bag.o`).
* the `TESTING` file is written for your grader.
For example, [bag/TESTING.md](starter/bag/TESTING.md) describes how we tested `bag.c`, by referring to `bagtest.c` and including the results of a test run in `bagtest.out`.
If your test requires some input files, include those data files in your submission and refer to them in your `TESTING` file.
(In the solution, the Makefile generates the necessary input files by downloading them from the web.)


Your `lab3` directory must contain the following:

 * Five subdirectories:
	 * `bag` with `Makefile`, `bagtest.c`, `bag.c`, `bag.h`.
	 * `set` with `Makefile`, `settest.c`, `set.c`, `set.h`, `README`, `TESTING`
	 * `counters` with `Makefile`, `counterstest.c`, `counters.c`, `counters.h`, `README`, `TESTING`
	 * `hashtable` with `Makefile`, `hashtabletest.c`, `hashtable.c`, `hashtable.h`, `README`, `TESTING`
	 * `common` directory with contents inherited from our starter kit
 * Each `README` (or `README.md`) explains any assumptions and acknowledges any limitations.
 * Each `TESTING` (or `TESTING.md`) shows how you tested the module.
 * Include any special input files you used for testing.


#### Submitting your lab
Before the deadline, run

```
~cs50/labs/submit 3
```
Make sure it confirms success.
If you need to update your submission, run the same command again; it will overwrite the prior submission with the current contents of your `lab3` directory.

***If you wish to use one of your 24-hour extensions,*** run this command *before the deadline*:

```
~cs50/labs/submit 3 extension
```
This command deletes any submission you may have made previously, and leaves a single file "extension" there as an indication you are requesting an extension.
When you are later ready to submit your work, do so as above:

```
~cs50/labs/submit 3
```

This overwrites any prior submission - even the extension request.
(Thus, if you submit before the deadline, you effectively 'cancel' your request for an extension.) We will grade the first submission present at 0h, 24h, 48h, or 72h after the original deadline.
To avoid confusion, ***please blitz `cs50 AT cs.dartmouth.edu` if you want a late submission to be graded instead of your on-time submission.***
