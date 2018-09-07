---
layout: page
title: Extra - C header files
---

***Examples are not yet updated for CS50 in 17S, but the concepts are still correct.***

Let's look at the contents and purpose of `readline.h`.
That file was used in the recent examples:

* [names1.c]({{site.examples}}/names1.c): arrays of strings, reading and copying lines into an array.
* [names2.c]({{site.examples}}/names2.c): scanning a string and truncating it by overwriting a character with the null `\0` character.

These use

* [readline.c]({{site.examples}}/readline.c): a C file defining the function `readline`, used by `names*.c`.
* [readline.h]({{site.examples}}/readline.h): a C 'header' file that provides prototypes needed by any C program wanting to use `readline`.

Why did we need this include file, `readline.h`?
Because we compiled `names.c` and `readline.c` separately.
When we compiled `names.c`, we needed to declare the prototype for the function `readline`, just as we would have if `readline` had been defined within `names.c`.
Because the function was *not* defined within `names.c`, though, the prototype needs to be prefixed with `extern`, indicating that the function is external to the current C file.
The C compiler leaves that symbol (`readline`) unresolved, and hopes the linker will later be able to connect it to the actual function definition when `names.o` is linked with other object files.

We could have simply typed the prototype into `names.c`, but we put it in a separate file `header.h`, and then used the special compiler directive `#include` to literally copy the contents of `header.h` into the C file at that point.
(See the [lecture extra](08x-preprocessor.html) about the C preprocessor.) Just in case the header file gets included multiple times, the pair of directives `#ifndef` (if not defined) and `#define` (define) ensure the body of this file is only processed once per C file.

```c
/* 
 * readline.h - a utility function to safely read one line of input
 * See readline.c for documentation.
 *
 * David Kotz, April 2016
 */

#ifndef __READLINE_H__
#define __READLINE_H__

#include <stdbool.h>

extern bool readline(char *buf, const int len);

#endif //  __READLINE_H__
```

We also include `header.h` in `readline.c`.
This way, we write the prototype in only one place, and yet give the compiler information in both places where it is needed - and give the compiler a chance to help us catch any inconsistencies between the prototype and the function call in `names.c`, or between the prototype and the function definition in `readline.c`.

