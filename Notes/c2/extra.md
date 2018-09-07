---
layout: page
title: Lecture Extra - The Standard C Libraries
---

These notes are meant to complement the "[lecture](index.html)".

***Warning: the examples in (or cited by) this "lecture extra" may not follow CS50 programming style."***

## The standard I/O library

The C language itself does not define any particular file or character-based input or output routines (nor any windowing routines), unlike Java.
Instead any program may provide its own.
Clearly this is a daunting task, and so the *standard C library* provides a collection of functions to perform file-based input and output.
The standard I/O library functions provide efficient, buffered I/O to and from both terminals and files.

C programs requiring standard I/O should include the line:

```c
#include <stdio.h>
```

NOTE: the `#include` preprocessor directive simply instructs the compiler to go find the `stdio.h` file in the usual system place and include its contents at this point in the source stream.
We'll learn more about the preprocessor later.

All transactions through the standard I/O functions require a *file pointer*:

```c
  FILE *fp;

  fp = fopen("file.dat", "r");
  ...
  fclose(fp);
```

Although a 'file pointer' is, strictly speaking, a C pointer, we don't care much about what it is - we simply pass this pointer to functions in the standard C library.

> Some texts will refer to this pointer as a *file stream* (and C++ confused this term even more), but these should not be confused with nor be described as akin to Java's "streams".

The standard I/O library (aka 'stdio') predefines three file pointers: `stdin`, `stdout`, and `stderr`, which are already opened for you (by the shell or other program that executed your C program) and which you can read, write, or manipulate using stdio functions.

Several functions are provided to check the status of file operations on a given file pointer, including:

```c
  feof(fp)      /* checks for end-of-file */
  ferror(fp)    /* checks for an error on a file */
```

The standard I/O functions all return `NULL` or `1` (as appropriate) when an error is detected.
For example:

```c
  #include <stdio.h>

  int main(int argc, char *argv[]) {

    FILE *fp;

    if((fp=fopen("/etc/passwd", "w")) == NULL) {
       error message ...
    } else {

      /* process the file */
      ...
      fclose(fp);
    }
  }
```
> In the preceding, notice how it embeds an assignment statement inside the condition of the `if` statement!
> That's ok, because an assignment statement is an expression that itself has a value - the value that is assigned to the variable on the left-hand side - and that value is then used in the outer expression (here, a conditional expression testing equality).
> Thus, the `if` statement could have been written as

```c
    fp=fopen("/etc/passwd", "w");
    if(fp == NULL) {
	...
```

> but such a construct appears so often that they are often combined.
> When the assignment is included in the `if` condition, it was wrapped in parentheses just to be sure that it's treated as a whole, as the left-hand-side of the `==` comparison operator.

The most frequently used functions in the C standard I/O library perform output of formatted data.
We also see here the most frequent use of C's acceptance of functions receiving a variable number of arguments:

```c
  fprintf(FILE *fp, char *format, (T)arg1, (T)arg2, ...);
```

The `fprintf` function is a generalization of `printf`.
Put another way, `printf(format, arg...)` is shorthand for `fprintf(stdout, format, arg...)`.

```c
   int class = 50;
   char *department = "Computer Science";

   fprintf(fp, "Course: %s %02d\n", department, class);
```

Many standard I/O functions accept a *format specifier*, which is a string describing how the following arguments are to be interpreted.
This mechanism is in contrast to Java's `toString` facility in which each object knows how to output/display itself as a `String` object.
There are many possible format specifiers, the most common ones being `c` for character values, `d` for decimal values, `f` for floating-point values, and `s` for character strings.
Format specifiers may be preceded by a number of *format modifiers*, which may further specify their data type and may indicate the width of the required output (in characters).

The C standard I/O library provides efficient "buffering".
This means that although it appears that the output has gone to the `FILE` pointer, it may still be held within an internal character buffer in the library (and will hence not be actually written to the hard disk or to the screen until more output is accumulated and the buffer becomes full).
We often need to "flush" our output to allow us to *know* when the output will be written to disk or the screen:

```c
  /* ... format some output ...*/
  fflush(fp);
```

As you might expect, `FILE` pointers are automatically flushed when a file is closed or the process exits.

As well as outputting to `FILE` pointers, we may also perform formatted output to a character array (a string), with a very similar series of functions:

```c
   int class = 50;
   char *department = "Computer Science";
   char buffer[BUFSIZ];

   sprintf(buffer, "Course: %s %02d\n", department, class);
```

> Security alert! What is the potential exposure in the code above?

C's standard I/O library may also be used to input values from `FILE` pointers and character arrays using `fscanf()` and `sscanf()`.
Because we want the contents of C's variables to be modified by the standard I/O functions, we need to pass them *by reference*, which in C is accomplished by passing the 'address' of the variables using the `&` operator:

```c
  fscanf(fp, format, &arg1, &arg2, ...);
```

like this:

```c
  int i, res;
  char buffer[BUFSIZ];
  fscanf(fp, "%d %d", &i, &res);
  sscanf(buffer, "%d %d", &i, &res);
```

We'll talk more about addresses and pointers in a couple of days.

When using the C standard I/O functions, we must pay attention to the particular return values from those functions.
The functions themselves may return `NULL` file pointers, the number of input items read, the number of characters written, or special non-zero values that indicate the end of a file or some other error condition.
Always check the `man` page to be sure.
Some of the special return values have constants defined in the system include files for convenience, improved code readability, and consistency.
Here are some sample code snippets:

```c
#include <stdio.h>  
#define MAXLINE 80

  int i, sum;
  char line[MAXLINE];

  for(;;) {
    fgets(line, sizeof(line), fp);
    if(feof(fp))
       break;

    /* ... process the line just read ...*/

  }
  fclose(fp);
  ...
  for (numlines=0, (fp=fopen("thefile",'r')); feof(fp); numlines++ ) {
      fgets(fp, buffer, sizeof(buffer), fp);
      ...
  }
  ...
  sum = 0;
  while(fscanf(fp, "%d", &i) == 1)
     sum += i;
  fclose(fp);
```

Here is a code snippet that uses `fopen(),` `fgets()`, `strlen()`, `printf()`, `sscanf()`, and `fclose()`.
It reads frmo the file into to a character array, and then applies `sscanf()` to that array to extract information from the array into various variables.

**Example: [files.c]({{site.examples}}/files.c)**
>See the full C code in [files.c]({{site.examples}}/files.c)
>and a sample input file [input]({{site.examples}}/files-input.txt).


## Why not to use gets( ): an example of dangerous code

There is a saying - you learn from your mistakes, so make lots of them.
There is another one: don't make the same mistake twice.
The use of the stdio function `gets()` is a mistake.
Lots of programmers have made this mistake, and caused headaches for millions of computer users around the world.
The lesson: *never use `gets()`.*

Let's look at the following `buffer-overflow.c`, which could have been named `really-bad-code.c`.

Apart of the use of `gets()`, this is a nice little string manipulation program that uses a number of other C library calls that are of interest.

**Example: [buffer-overflow.c]({{site.examples}}/buffer-overflow.c)**

```c
/*
   File:  buffer-overflow.c

   Description: This is a bad program! But it's fun. The basic idea of
                of the program to input and manipulate strings using
                arrays of chars is fun. However, there is a serious flaw
                in the program. The book uses the function gets(). This
                is a seriously dangerous function call. DON'T USE IT.

   Revised code taken from pg. 457 (Program 9.5) (Bronson) "First Book on ANSI C"

*/

#include <stdio.h>
#include <string.h> /* required for the string function library */

#define MAXELS 50

int main()
{

  char string1[MAXELS] = "Hello";
  char string2[MAXELS] = "Hello there";
  int n;

  n = strcmp(string1, string2);

  if (n < 0)
    printf("%s is less than - %s\n\n", string1, string2);
  else if (n == 0)
    printf("%s is equal to - %s\n\n", string1, string2);
  else
    printf("%s is greater than -  %s\n\n", string1, string2);

  printf("The length of string1 is %d characters\n", strlen(string1));
  printf("The length of string2 is %d characters\n\n", strlen(string2));

  strcat(string1," there World!");

  printf("After concatenation, string1 contains the string value\n");
  printf("%s\n", string1);
  printf("The length of this string is %d characters\n\n",
                                                   strlen(string1));

  printf("Please enter a line of text for string2, max %d characters: ",
                                                   sizeof(string2));

  /* In the code below comment and uncomment the gets() code */

  gets(string2);

  /* In the code below comment and uncomment the fgets() code segment */

  /*  fgets(string2, sizeof(string2), stdin); */

  printf ("Thanks for entering %s\n", string2);

  strcpy(string1, string2);

  printf("After copying string2 to string1");
  printf(" the string value in string1 is:\n");
  printf("%s\n", string1);
  printf("The length of string1 is %d characters\n\n",
                                                 strlen(string1));
  printf("\nThe starting address of the string1 string is: %x\n",
                                                 string1);
  printf("\nThe starting address of the string2 string is: %x\n",
                                                 string2);
  return 0;
}
```

Let's look at the output when running the program first with `gets()` and then with the safer `fgets()`.
If we run the code with `gets()` we get a segmentation fault when entering 51 characters.

```bash
    $ ./buffer-overflow
    Hello is less than - Hello there

    The length of string1 is 5 characters
    The length of string2 is 11 characters

    After concatenation, string1 contains the string value
    Hello there World!
    The length of this string is 18 characters

    warning: this program uses gets(), which is unsafe.
    Please enter a line of text for string2, max 50 characters: 01234678901234567890123456789012345678901234567890
    Thanks for entering 01234678901234567890123456789012345678901234567890
    Segmentation fault
```

If we comment out `gets()`, uncomment `fgets()`, and recompile we are safe:

```bash
    $ ./buffer-overflow
    Hello is less than - Hello there

    The length of string1 is 5 characters
    The length of string2 is 11 characters

    After concatenation, string1 contains the string value
    Hello there World!
    The length of this string is 18 characters

    Please enter a line of text for string2, max 50 characters:  01234678901234567890123456789012345678901234567890
    Thanks for entering  012346789012345678901234567890123456789012345678
    After copying string2 to string1 the string value in string1 is:
     012346789012345678901234567890123456789012345678
    The length of string1 is 49 characters


    The starting address of the string1 string is: bffff87a

    The starting address of the string2 string is: bffff848
```

This is a bad program!
The basic idea of the program is to accept and manipulate strings using arrays of chars.
However, there is a serious flaw in the program.
Some older books use the function `gets()`; it is a seriously dangerous function call.
***Do not use gets()!***

The program defines a buffer of 50 chars in length.
The user types in characters from the keyboard and they are written to the buffer, i.e., `string1` and `string2`.

The input parameter to `gets()` is the name of the array (which is a pointer - more on pointers later).
The function does not know how long the array is!
It is impossible to determine the length of `string1` and `string2` from a pointer alone.

If we run the program and type in 50 characters, including the newline, all is safe.
But if we type 51 or 60 or more characters, we over run or 'overflow' the buffer.
We end up writing past the end of the array!
This overflow can happen even without calling an unsafe function such as `gets()`, so it's an important lesson to learn.
Buffer overflows can have rather spectacular results!

Bugs often happen at boundary conditions and one important boundary is the end of the array.
If we overwrite `string1`, we might write into `string2`.
Recall that, by convention, C strings are terminated by `\0` (aka `NULL`).
If this character is overwritten then a piece of code operating on the array will keep on scanning until it finds a `\0`.

If we run this code and type in more than 50 chars (as we did above) anything can happen; for example: 1) the code could work with no visible affect of the bug; 2) immediate segfault; 3) segfault later in the code stream; 3) mistakes happen in unrelated functions (e.g., strcat() in our code).

Some books use `gets()` and promote its use.
Just Say NO!
Instead, use the safe `fgets()` as it is a buffer-safe function.
Its prototype is:

```c
    char *fgets(char *s, int size, FILE *stream);
```

It requires you to identify *which file*, yes, but more importantly, it requires you to identify the size of the character buffer into which it will write characters; `fgets` will not write more characters than the size of the buffer.

Example:

```c
    fgets(buf, sizeof(buf), stdin);
```

The `fgets()` function shall read bytes from stream into the array pointed to by `buf`, until `sizeof(buf)-1` bytes are read, or a newline is read and transferred to `buf`, or an end-of-file condition is encountered.
The string is then terminated with a NULL byte.

We replace `gets()` with `fgets()` in the above code and now we are safe.

If you want to read in just characters from the screen one at a time you can use `getchar()`.
But remember that if you enter a character on the keyboard and then hit return, the 'newline' character is also in the stream.
Take a look at this code and run it.

**Example: [getchar.c]({{site.examples}}/getchar.c)**

### The C/Operating system interface

Operating systems (such as Unix, Linux, MacOS X, and Windows 10) will always execute C programs by calling the function `main()` with two parameters:

1.  an integer argument count (`argc`),
2.  an array of pointers to character strings (`argv`)

Notice that in many previous examples we've provided a `main()` without any parameters all.
Remember that C does not check the length and types of parameter lists of functions which it does not know about ones that have not been prototyped.
In addition, the function `main()` has no special significance to the C compiler.
Only the linker requires `main()` as the apparent starting point of any program.
Most C programs you see will look like this:

```c
    int main(int argc, char *argv[])
```

I prefer to declare them as constant so we let the C compiler help us avoid modifying these input parameters:

```c
    int main(const int argc, const char *argv[])
```

So how do you get "an array of pointers to char" out of a mouthful like `char *argv[]`?
It's all about operator precedence.

The highest precedence of everything is variable names and literals.
Then the next highest precedence thing is the subscripting operator `[ ]`.
About halfway down the list of operators is the indirection operator `*`, so its precedence is lower than the subscripting operator.
Thus, the above declaration is read as: *argv is an array of pointers to char*.

The following program prints out its command line.
Note that `argv[0]` is the command name and `argv[1]` ... `argv[N]` are the command-line arguments (after any expansion or subsitutions done by the shell).

**Example: [arguments.c]({{site.examples}}/arguments.c)**

Look at the following snippet:

```c
#include <stdio.h>

int main(int argc, char *argv[]) {

  int i;

  printf("%d items were input on the command line\n", argc);
  for (i = 0; i < argc; i++)
    printf("argument %d is %s\n", i, argv[i]);
}
```

```bash
[cs50@flume] $ ./arguments 1 two 3.1415 4 "F i v e"
6 items were input on the command line
argument 0 is ./arguments
argument 1 is 1
argument 2 is two
argument 3 is 3.1415
argument 4 is 4
argument 5 is F i v e
[cs50@flume] $
```

We declared `argv` as *array of pointers to char*.
For any given argument *i*, `argv[i]` is one of those pointers; that is, `argv[i]` is of type `char*`.
We can pass that pointer to functions like `printf`, wherever it expects a string.

A more interesting snippet of code shows that the command line is stored as a set of string arguments in memory and that the address of the location of the first character for each string argument is stored in the `argv[]` array.

***Example: [command.c]({{site.examples}}/command.c)***

Lets look at the following snippet:

```c
#include

int main(int argc, char *argv[])
{
  int i;

  printf("\nThe number of items on the command line is %d\n\n",argc);
  for (i = 0; i < argc; i++)
  {
    printf("argument %d is \"%s\"`\n", i, argv[i]);
    printf("The address stored in argv[%d] is %p\n", i, argv[i]);
    printf("The first character pointed to there is \'%c\'\n", *argv[i]);
  }

  return 0;
}
```

If you run the program you will see the following output -
note that the hexadecimal address of the first character for each argument is printed out too.

```bash
[cs50@flume] $ ./command hello cs50 ready to go skating?

The number of items on the command line is 7

argument 0 is "./command"`
The address stored in argv[0] is 0x7fff5d056376
The first character pointed to there is '.'
argument 1 is "hello"`
The address stored in argv[1] is 0x7fff5d056380
The first character pointed to there is 'h'
argument 2 is "cs50"`
The address stored in argv[2] is 0x7fff5d056386
The first character pointed to there is 'c'
argument 3 is "ready"`
The address stored in argv[3] is 0x7fff5d05638b
The first character pointed to there is 'r'
argument 4 is "to"`
The address stored in argv[4] is 0x7fff5d056391
The first character pointed to there is 't'
argument 5 is "go"`
The address stored in argv[5] is 0x7fff5d056394
The first character pointed to there is 'g'
argument 6 is "skating?"`
The address stored in argv[6] is 0x7fff5d056397
The first character pointed to there is 's'

[cs50@flume] $
```

A common activity at the start of a C program is to search the argument list for command-line switches commencing with a dash character.
The remaining command-line parameters are often assumed to be filenames.

***Example: [nosort.c]({{site.examples}}/nosort.c)***

The program below parses the command line of a `sort` command.
It will process:

```c
    nosort -n
    nosort -r
    nosort -u
    nosort -r -u -n
```
Any variation of the above is also supported, but not:

```c
    nosort -run
```

An example of defensive programming: If the user enters a bad option then the user is informed with a usage message:

```bash
    [cs50@tahoe] ./nosort -y
    Usage: bad option -y
```

The program [nosort.c]({{site.examples}}/nosort.c) (no sort code is included, only the command line parsing) looks like this:

```c
    / The program parses the input switches to sort
    // supports command lines such as sort -r -u -n
    // but not sort -run which you will need for
    // the Lab3

    #include<stdio.h>

    int main(int argc, char *argv[]) {

      int unique, reverse, numsort;
      char *progname;

      progname = argv[0];
      numsort=reverse=unique = 0;

      // run through the input commands looking 
      // for switches

      while((argc > 1) && (argv[1][0] == '-')) {

        // argv[1][1] is the actual option

        switch (argv[1][1]) {

        case 'r':
            printf("Switch is %c\n", argv[1][1]);
            reverse = 1;
            break;
        case 'u':
            printf("Switch is %c\n", argv[1][1]);
            unique = 1;
            break;
        case 'n':
            printf("Switch is %c\n", argv[1][1]);
            numsort = 1;
            break;

        default:
             printf("Error: bad option \'%c\'\n", argv[1][1]);
             printf("Usage:  %s [-r] [-u] [-n] \n", progname);
             break;
        }

        // decrement the number of arguments left
        // increment the argv pointer to the next argument

          argc--; argv++;
      }
      printf( "numsort=%d, unique=%d, reverse=%d\n", numsort, unique, reverse);

      // other processing

      return(0);
    }
```

The above demonstrates several things about C, and C idioms:

 1. the `switch` statement and its component `case` and `break` statements.
 2. the use of `argc--; argv++` as a way of stepping through an array.
	 * Note: each time `argv` is incremented, it changes the base address on which a subscript like `[1]` is interpreted. In effect, subscripting is a form of 'pointer arithmetic', adding the necessary amount to the base pointer so as to find the address of the relevant item in the array.  More on that when we discuss pointers.
 3. the syntax for subscripting a two-dimensional array, like `argv[1][0]`.
	 * Note: `argv` is not (strictly speaking) a two-dimensional array, and C does not (strictly speaking) support multi-dimensional arrays; the first subscript selects one of the `char*` pointers in the array-of-pointers that is `argv`; the second subscript selects one of the characters in the array of characters to which that pointer refers.


## getopt( )

***Example: [nosort-getopt.c]({{site.examples}}/nosort-getopt.c)***

Another way to process command-line arguments is to use the `getopt()` C library function, which is specifically designed to help parse switches in the common `-s` and `--switch` formats.
See `man 3 getopt`.

```c
// The program parses the input switches to sort
// supports command lines such as sort -r -u -n
// but not sort -run

#include<stdio.h>
#include <unistd.h>
#include <getopt.h>  /* how did we know to include this??? "man 3 getopt" */

int main(int argc, char *argv[]) {

  int unique, reverse, numsort;
  char ch;
  char *progname;

  progname = argv[0];

  // run through the input commands looking 
  // for switches using the handy-dandy getopt function!

  while ((ch = getopt(argc, argv, "run")) != -1)
  {
       switch (ch) 
       {//  while((argc > 1) && (argv[1][0] == '-')) {

       case 'r': 
            printf("Switch is %c\n", ch);
            reverse = 1;
            break;
       case 'u':
            printf("Switch is %c\n", ch);
            unique = 1;
            break;
       case 'n':
            printf("Switch is %c\n", ch);
            numsort = 1;
            break;

       default:
            printf("Error: bad option \'%c\'\n", ch);
            printf("Usage:  %s [-r] [-u] [-n] \n", progname);
            break;
       }
  }
  printf( "numsort=%d, unique=%d, reverse=%d\n", numsort, unique, reverse);

  // other processing

  return(0);
}
```

