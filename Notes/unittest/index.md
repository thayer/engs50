---
layout: page
title: Unit testing
---

The goal of effective unit testing is to isolate each functional part of the system and to demonstrate that each of those parts is working properly.

A short online reference is Jeff Canna's *[Testing, Fun, Really](http://www.ibm.com/developerworks/library/j-test.html)*.
Although he is talking mostly about Java, his insights on unit testing are superb.

> "Unit tests tell a developer that the code is doing things right; functional tests tell a developer that the code is doing the right things." -- Jeff Canna, *[Testing, Fun, Really](http://www.ibm.com/developerworks/library/j-test.html)*.

> "Unit tests are written from the developer's perspective and focus on particular methods of the class under test." -- Jeff Canna, *[Testing, Fun, Really](http://www.ibm.com/developerworks/library/j-test.html)*.

Use these guidelines when writing unit tests (from Jeff Canna, *[Testing, Fun, Really](http://www.ibm.com/developerworks/library/j-test.html)*):

 * "Write the unit test before writing code for class it tests.
 * "Capture code comments in unit tests.
 * "Test all the public methods that perform an "interesting" function (that is, not getters and setters, unless they do their getting and setting in some unique way).
 * "Put each test case in the same package as the class it's testing to gain access to package and protected members.
 * "Avoid using domain-specific objects in unit tests."

### Unit testing of our binary tree

Today's Terminal [script](script.txt) is available.

Unzip the [tree examples file]({{site.examples}}/trees.zip). The tree9 example
demonstrated a binary-tree data structure. Here we enhance it to become treeA (to a computer scientist, `A` comes next after `9`).

Look at treeA/tree.c and its Makefile and you'll notice three things:

 * The code now has a `main()` function at the bottom of the file.
It is protected inside `#ifdef UNIT_TEST ... #endif` so it is only compiled-in when we want to compile a unit test.
 * Preceding `main()` is an `#include "unittest.h"` to pick up several *preprocessor macros*, which we explain below.
 * The `Makefile` now has a `unittest` target, which builds a distinct executable, and a `unit` target, which runs it.

 > The `unittest` target is unusual in that it explicitly mentions dependency on `test.c`.
Normally Make automatically recognizes the dependency between `.o` files and `.c` files, so we rarely see rules with dependency on `.c` files.
Here, because there is no `unittest.c`, we always build `unittest` from `tree.c` with a special `-D` flag and do not use `tree.o`; we must explicitly list all the pieces that go into building `unitest`.

***Preprocessor macros.***

The unit test makes heavy use of some *macros*, which are recognized and textually replaced by the C preprocessor before the C compiler even runs.
They are so useful I've put them in a separate `unittest.h` file, and textually include them in `test.c` when `UNIT_TEST` has been defined.
I show the core of `unittest.h` below.

These are *macros.*
Note how I define fragments of code with each `#define`; the first two even take parameters.
When scanning C code, the preprocessor does *textual substitution* for each defined symbol - it does not evaluate the code at all, it just substitutes the remainder of the line (after the symbol and after a space) into the C program wherever it sees that symbol, optionally inserting the parameter wherever it appears in the macro body.
Because each definition must appear on one "line", I had to use a *line continuation* character (backslash in the last character of the line) to let me format the definitions in a human-readable way.
I lined up the backslashes so they all look neat.

```c
// each test should start by setting the result count to zero
#define START_TEST_CASE(name) int _failures=0; char *_testname = (name);

// Check a condition; if false, print warning message.
// e.g., EXPECT(dict->start == NULL).
// note: the preprocessor 
//   converts __LINE__ into line number where this macro was used, and
//   converts "#x" into a string constant for arg x.
#define EXPECT(x)                                               \
  if (!(x)) {                                                   \
    _failures++;                                                \
    printf("Fail %s Line %d: [%s]\n", _testname, __LINE__, #x); \
  }

// return the result count at the end of a test
#define END_TEST_CASE                                                   \
  if (_failures == 0) {                                                 \
    printf("PASS test %s\n\n", _testname);                              \
  } else {                                                              \
    printf("FAIL test %s with %d errors\n\n", _testname, _failures);    \
  }

#define TEST_RESULT (_failures)
```

The preprocessor defines a special macro `__LINE__` that is set to the line number of the original source file, as each source line is processed; this is great for printing out the line number where our test case failed.

The preprocessor also has special syntax `#parameter` that substitutes a C string constant for the text of the parameter.
You can see it right at the end of the `EXPECT` macro.
Thus, `EXPECT(tree != NULL)` will produce code that ends with `"tree != NULL");` enabling us to print the line number *and* the condition that failed.
You can't do that with C, only with the preprocessor!

*Warning: I strongly discourage the use of preprocessor macros.*
There are times, however, where they are the right tool for the job, and this is one of those times.

The macros are meant to be used for constructing small unit tests like this one:

```c
/////////////////////////////////////
// create and validate an empty tree
int test_newtree0()
{
  START_TEST_CASE("newtree0");
  tree_t *tree = tree_new();
  EXPECT(tree != NULL);
  EXPECT(tree->root == NULL);

  EXPECT(tree_find(tree, "hello") == NULL);

  tree_delete(tree, NULL);
  EXPECT(count_net() == 0);

  END_TEST_CASE;
  return TEST_RESULT;
}
```

In the above test, I create a new (empty) tree, try to find something in it, and delete the tree.
Notice, though, that I actually peek *inside* the `struct tree` to verify that all its members are set correctly.

Note, too, how I used those new macros - using `START_TEST_CASE()` to give the test a name and initialize everything, `EXPECT()` to indicate the conditions I expect to be true, `END_TEST_CASE` to print the summary and clean up, and `return TEST_RESULT` to provide a return value for this function.
Here's how that code looks after running it through the preprocessor with `gcc -DUNIT_TEST -E tree.c`:

```c
int test_newtree0()
{
  int _failures=0; char *_testname = ("newtree0");;
  tree_t *tree = tree_new();
  if (!(tree != ((void *)0))) { _failures++; printf("Fail %s Line %d: [%s]\n", _testname, 244, "tree != NULL"); };
  if (!(tree->root == ((void *)0))) { _failures++; printf("Fail %s Line %d: [%s]\n", _testname, 245, "tree->root == NULL"); };

  if (!(tree_find(tree, "hello") == ((void *)0))) { _failures++; printf("Fail %s Line %d: [%s]\n", _testname, 247, "tree_find(tree, \"hello\") == NULL"); };

  tree_delete(tree, ((void *)0));
  if (!(count_net() == 0)) { _failures++; printf("Fail %s Line %d: [%s]\n", _testname, 250, "count_net() == 0"); };

  if (_failures == 0) { printf("PASS test %s\n\n", _testname); } else { printf("FAIL test %s with %d errors\n\n", _testname, _failures); };
  return (_failures);
}
```

If you look closely, you can see the original bits of code (like `tree_delete(tree, NULL)` (with `NULL` expanded!) as well as the expanded `EXPECT` and other macros.

Then the `main()` program runs a series of unit tests, and prints an error if any of them failed:

```c
int
main(const int argc, const char *argv[])
{
  int failed = 0;

  failed += test_newtree0();
  failed += test_newtree1();
  failed += test_treeleft();
  failed += test_treefind();

  if (failed) {
    printf("FAIL %d test cases\n", failed);
    return failed;
  } else {
    printf("PASS all test cases\n");
    return 0;
  }
}
```

Here's what the output looks like when everything passes:

```
$ make unit
gcc -Wall -pedantic -std=c11 -ggdb    -c -o memory.o memory.c
gcc -Wall -pedantic -std=c11 -ggdb  -DUNIT_TEST tree.c memory.o -o unittest
./unittest
PASS test newtree0

PASS test newtree1

PASS test treeleft

  ann(1)
   bob(2)
    cheri(3)
 dave(4)
PASS test treefind

PASS all test cases
```

To see what it looks like when a failure occurs, I could either break the tree code (which I'd rather not do!) or break the test code; I'll do the latter by changing one line

```c
  EXPECT(tree_find(tree, "abcd") == &data);
```

to

```c
  EXPECT(tree_find(tree, "abcd") == NULL);
```

and run the test again:

```
$ make -k unit
gcc -Wall -pedantic -std=c11 -ggdb  -DUNIT_TEST tree.c memory.o -o unittest
./unittest
PASS test newtree0

Fail newtree1 Line 271: [tree_find(tree, "abcd") == NULL]
FAIL test newtree1 with 1 errors

PASS test treeleft

  ann(1)
   bob(2)
    cheri(3)
 dave(4)
PASS test treefind

FAIL 1 test cases
make: *** [unit] Error 1
```

Notice how Make exited with error; that's because `unittest` exited with non-zero status: note the code at end of `main()`.

## CUnit test framework

Although we don't have time to study any professional frameworks, there are several C unit testing frameworks available on the Internet: [Check](https://libcheck.github.io/check/) and [CUnit](http://cunit.sourceforge.net/).
Here's an [example](http://cunit.sourceforge.net/example.html) using CUnit.

## Activity

In today's [activity](activity.html) your group will design a unit test for one of our other modules.

