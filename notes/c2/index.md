---
layout: page
title: The Standard C Libraries
---

In this lecture, we continue our accelerated introduction to the C programming language.

### Goals

We learn several things today:

-  the standard I/O library, and a useful `readline()`
-  opening and reading from files
-  arrays, and arrays of strings
-	command-line arguments
-   compiling code from multiple files into one program

You may also want to read the "[lecture extra](extra.html)", which has lots more information that I do not have time to cover in class.

## Activity

Today's classroom [activity](activity.html) takes a look at the nature of C strings as arrays, and why you need to keep that in mind.

## Live demos

See my Terminal [script](script.txt) from today's class.

 * [names0.c]({{site.examples}}/names1.c): (read a list of names into an array and print it back out)
 * [names1.c]({{site.examples}}/names1.c): (pulls `readline()` out to [readline.c]({{site.examples}}/readline.c) and [readline.h]({{site.examples}}/readline.h))
 * [names2.c]({{site.examples}}/names2.c): (read from a file, if provided, instead of from stdin); leverages [freadline.c]({{site.examples}}/freadline.c) and [freadline.h]({{site.examples}}/freadline.h)


***Bonus example:*** [strings.c]({{site.examples}}/strings.c): how C strings work.
We will not get to explore this example - but it is well worth playing with it on your own.

## Key concepts

[names0.c]({{site.examples}}/names1.c): (read a list of names into an array and print it back out)

### names0.c

**preamble**

* `bool` data type and `stdbool.h`

**main**

* the notion of `char*` representing a string, and that strings are arrays of characters
* use of `const` for values that will never change.
* declaration of `names` as two-dimensional array; think of it as a one-dimensional array of strings.
* `for` loop with three parts:
	* 1: `n=0` initializer
	* 2: two reasons to end (`names` is full, or file reaches EOF)
	* 3: empty
* `printf` loop does not include `\n` because each name includes a newline character, per the contract with `readline`.

**readline**

* we could use `gets(s)` to read a line from stdin, but it can easily overwrite the space allocated to string `s`
* we could use `fgets(s, len, stdin)`, which will not overwrite a string `s` of size `len`, but may not read a whole line from the input.
* let's write our own `readline` function instead.
* detailed comment describing the *contract* between caller and the function.
* `while` loop that runs until EOF or buffer is full. (why `pos < len-1` instead of `pos < len`?)
* use of `pos++` notation to step through array.
* need to null-terminate the string with `\0`
* `return` from inside the loop.
* need to strip excess characters from an over-length line, until we reach EOF or newline.


### names1.c

 [names1.c]({{site.examples}}/names1.c): (pulls out `readline()` to [readline.c]({{site.examples}}/readline.c) and [readline.h]({{site.examples}}/readline.h))

**names1.c**

* `#include "readline.h"` - note the quotes, rather than brackets.
this means it will be sought in the the current directory, rather than in a standard place where C libraries live.

**readline.h** - *textually included* in names1.c at the point where `#include` was used.

* use of `extern` on the prototype to indicate this function will be provided in another .c file
* `readline` header comment is here, not in the .c file, so it is easily readable by users of this function.
* use of `#ifndef` to protect against repeated inclusion of this file

```
#ifndef __READLINE_H__
#define __READLINE_H__
...
#endif //  __READLINE_H__
```

**readline.c**

* also `#include "readline.h"` - not strictly necessary in this case, but it gives the compiler a chance to check that prototype (from .h file) matches the definition (from .c file).


### names2.c

[names2.c]({{site.examples}}/names2.c): (read from a file, if provided, instead of from stdin); leverages [freadline.c]({{site.examples}}/freadline.c) and [freadline.h]({{site.examples}}/freadline.h)

* `main` takes arguments
* code checks arguments for validity
* use of `fopen` to open a file for reading (`"r"`)
* error messages printed to `stderr` with `fprintf`
* `fclose(fp)` later called to close the file
* `freadline` is like `readline` except it uses `getc(fp)` instead of `getchar()`
* note the type of `fp` is `FILE*`; it's a pointer to an object of type FILE.
More on that later.

## Activity

Today's classroom [activity](activity.html) explored what happens when you overwrite the end of a string.
