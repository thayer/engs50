---
layout: page
title: Extra - the C preprocessor
---

You will notice that a few lines, typically near the beginning of a C program, begin with the character `#`, aka 'hash', 'pound', or 'sharp'.
These lines are "C preprocessor directives" and are actually instructions (directives) to a special program called the "C preprocessor".
As its name suggests, the C preprocessor processes the text of a C program *before* the C compiler sees it.
The preprocessor directives (all beginning with `#`) should begin in column 1 (the 1st column) of any source line on which they appear.

The C preprocessor is very powerful but we will use it only for very specific purposes.
Most of the other common uses for preprocessor directives are either beyond the scope of this course, or unnecessary (and bad style) in modern C.

## Header file inclusion

The `#include` directive, often pronounced "pound include", should appear at the beginning of a C program.
It is used to literally copy the entire contents of another file at the point of the `#include` directive.
A common `#include` directive, seen at the beginning of most C files, is

```c
    #include <stdio.h>
```

This directive indicates that the contents of the file named `stdio.h` should be included at this point (the directive is replaced with the contents).
There is no limit to the number of lines that may be included with this directive and, in fact, the contents of the included file may contain other `#include` directives which are handled in the same way.
We say that the inclusions are nested and, of course, care should be taken to avoid duplicate or, even worse, recursive nestings!

The example using `<stdio.h>`, above, demonstrates two important points.
The filename itself appears between the characters `< >`.
The use of these characters indicates that the enclosed filename should be found in the standard include directory `/usr/include`.
The required file is then `/usr/include/stdio.h`.

The standard include files are used to consistently provide system-wide data structures or declarations that are required in many different files.
By having the standard include files centrally located and globally available, all C programmers are guaranteed of using the same data structures and declarations that they (all) require.

Alternatively, the `" "` characters may also be used, as in the following example:

```c
    #include "readline.h"
```

to include the contents of the file `readline.h` at the correct point in the C program.
Because double-quotes are used, the file is sought in the present working directory, that is `./readline.h`.
The filename in double-quotes can actually be a pathname, if your source code is spread over several directories; for example,

```c
    #include "includes/readline.h"
```

In both of the above examples the indicated filename had the `.h` extension.
Whereas we have previously said that the extension of `.c` is expected by the C compiler, the use of `.h` is only a convention within UNIX.
The `.h` indicates that the file is a *header file*, because they generally contain information required at the head (beginning) of a C program.
Header files typically (and should) contain only *declarations* of C constructs, like data types, data structures, and constants used throughout the C program.
In particular, **include files should contain only *declarations*, and no *definitions*, of variables or functions.**

You can also give the compiler a command-line flag to identify a directory where it can search for non-standard include files.
If, for example, you moved your `includes` directory up a level, you might write

```c
    #include "readline.h"
```
but then tell the compiler where to look for such files:

```bash
mygcc -I ../includes    -c readline.c
```

## Conditional compilation

Another often used feature of the C preprocessor is the use of "conditional compilation directives".

```c
#define DEBUG
...
#ifdef DEBUG
 ... code for use when DEBUG is defined
#else // DEBUG
 ... code for use when DEBUG is not defined
#endif // DEBUG
```

The C preprocessor actually includes some code, and strips out other code, before passing it to the C compiler.
In the above example, we define the preprocessor constant called `DEBUG`, and later test its value with `#ifdef`.
Notice the use of comments on the `#else` and `#endif` lines to help readability.

The above example is a common approach for debugging.
Even better, remove the `#DEBUG` line and let that be determined by the programmer at compile time:

```c
#ifdef DEBUG
 ... code for use when DEBUG is defined
#else // DEBUG
 ... code for use when DEBUG is not defined
#endif // DEBUG
```

```bash
  mygcc -DDEBUG program.c -o program
```

The program compiles (and behaves) differently with and without the compile-time switch `-DDEBUG`.

## Header file protection

The one place we really *must* use conditional compilation is in header files.
Look at our example [readline.h]({{site.examples}}/readline.h):

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

If the constant `__READLINE_H__` is not yet defined (`#ifndef`) then incude the remainder of the file up to `#endif`.
The first thing it does is to define that `__READLINE_H__`.
Thus, if a C file happens to include `readline.h` twice, which can happen in complex programs when header files include other include files, the C compiler won't see multiple copies of the included code.
That is,

```c
#include "readline.h"
#include "readline.h"
```

does not translate to

```c
extern bool readline(char *buf, const int len);
extern bool readline(char *buf, const int len);
```

but just to

```c
extern bool readline(char *buf, const int len);
```

The standard file `stdbool` protects itself this way, which is good, because a programmer may well write into her `.c` file something like

```c
#include <stdio.h>
#include <stdbool.h>
#include <readline.h>
```

and, because `readline.h` also includes `stdbool.h`, the latter might get imported several times without that protection.

> Why do we care?
> Some include files can safely be repeated and the C compiler won't care; actually, `readline.h` is one like that.
> But others, e.g., if they declare global constants, will cause the compiler to complain about multiply-defined variables.


### Testing header files

How can you be sure your header file has included all the relevant header files?
Compile it!
To compile the header file `foo.h` by itself,

```bash
mygcc -c foo.h
```

If there are any errors, it's probaby because you forgot one of the include files.

When done, `rm foo.gch` to clean up the compiler's output.


