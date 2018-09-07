---
layout: page
title: Activity - C preprocessor
---

### Goals

* to use the C preprocessor
* to understand when linker might produce errors.

## Activity

Examine the source files in [~cs50/examples/seuss]({{site.examples}}/seuss), shown below.

1. Try to compile the program.
Why do you get an error?
is it the compiler or linker reporting the error?
what could you do to fix it?
2. Run `gcc -E seuss.c`, which runs the *C preprocessor* only; this output is what the compiler would consume.
Look at the output; ignore the `#` lines, which are annotations to help the compiler produce error messages that reference the original file name and line number.
Notice how the preprocessor has copied everything from the include files right into the input, at the point where they are included in `seuss.c`, and then stripped out all the comments.
3. After class, re-read the [Lecture extra about the C preprocessor]({{site.lectures}}/makefiles/preprocessor.html).

```c
/* seuss.c - uses thing one and thing two. */

#include "one.h"
#include "two.h"

int main()
{
  int fun = thing_one() + thing_two();
  return fun; // exit status
}
```
```
/* one.h */

int one = 1;
extern int thing_one(void);
```
```
/* two.h */

int two = 2;
extern int thing_two(void);
```
```
/* one.c */

#include "one.h"

int thing_one(void)
{
  return one;
}
```
```
/* two.c */

#include "two.h"

int thing_two(void)
{
  return two;
}
```

<!--
## Solution

When you compile the program:

```bash
[cs50@flume ~/demo/seuss1]$ mygcc -c one.c
[cs50@flume ~/demo/seuss1]$ mygcc -c two.c
[cs50@flume ~/demo/seuss1]$ mygcc -c seuss.c
[cs50@flume ~/demo/seuss1]$ mygcc seuss.o one.o two.o -o seuss
one.o:(.data+0x0): multiple definition of `one'
seuss.o:(.data+0x0): first defined here
two.o:(.data+0x0): multiple definition of `two'
seuss.o:/net/class/cs50/demo/seuss1/seuss.c:7: first defined here
collect2: error: ld returned 1 exit status
```

The linker `ld` complains because the global variables `one` and `two` are multiply defined.
This happens because the variables are defined (not just declared) in the respective `.h` files, and those `.h` files are included in the respective `.c` files *and* in `seuss.c`.

The solution is to move those global variables out of the `.h` file into the respective `.c` files.
They are only used in those files, anyway, so they should further be marked `static` (so they are invisible outside the file in which they are defined).
Thus,

```c
/* seuss.c - uses thing one and thing two. */

#include "one.h"
#include "two.h"

int main()
{
  int fun = thing_one() + thing_two();
  return fun; // exit status
}
```
```
/* one.h */

extern int thing_one(void);
```
```
/* two.h */

extern int thing_two(void);
```
```
/* one.c */

#include "one.h"
static int one = 1;  // this line moved and made static

int thing_one(void)
{
  return one;
}
```
```
/* two.c */

#include "two.h"
static int two = 2;  // this line moved and made static

int thing_two(void)
{
  return two;
}
```
-->
