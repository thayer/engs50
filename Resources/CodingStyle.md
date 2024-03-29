---
layout: page
title: Programming Style
---

Coding style
-------------

A computer program is meant for two audiences: the computer that
compiles and runs it, and the people who must read, modify, maintain
and test it.  Think about writing a program the same way you think
about writing a paper: structure, organization, word choice and
formatting are just as important as content.  A program that works but
has a terrible style is unreadable, and therefore useless.

Real-world software development teams use common programming style
guides.  For example, if you are working on the Linux kernel, you
would use [Linus' Coding
Style](https://www.kernel.org/doc/Documentation/process/coding-style.rst).
If you are working on a gnu project, you would closely follow the
instructions in Chapter 5 "Making the best use of C" of their [GNU
Coding
Standards](http://www.gnu.org/prep/standards/standards.html#Writing-C)
document.  Other organizations might adopt other long-respected coding
standards like the [NetBSD source code style
guide](http://cvsweb.netbsd.org/bsdweb.cgi/src/share/misc/style?rev=HEAD&content-type=text/x-cvsweb-markup),
or they might produce their own guidelines based on several others.
Your company will most likely have one they prefer.

Style guides include things like formatting your source code, comment
requirements, how certain C constructs should (or shouldn't) be used,
variable naming conventions, cross-platform compatibility
requirements, and more.

We realize that coding style can be a very personal choice, but in the
professional world you will seldom have the privilege of choosing your
own style.

### CS50 style

**For CS50 assignments involving C programming, you must follow these guidelines** (inspired by the [K&R C book](http://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/dp/0131103628/ref=sr_1_1?ie=UTF8&qid=1321068335&sr=8-1) and by [Linus](https://www.kernel.org/doc/Documentation/process/coding-style.rst)):

* Avoid placing multiple statements on a single line.
* Break long statements (more than 80 characters) over multiple lines.
* Indent appropriately; emacs and other C-savvy text editors can indent automatically. See below.
* Use braces `{ }` for every nested block - it can save you from accidental nesting bugs.
* Place the opening brace at the end of the line, e.g., in `if` and `for` statements.
* Use spaces around binary operators, except struct and pointer references.
Do not use spaces between a unary operator and its operand.
See below.
* Use parentheses liberally when it helps to make an expression clear.
Adding parentheses rarely hurts, and might actually prevent a mistake.
* Avoid calling `exit()` from anywhere other than `main()`.
Unwind back to `main` using error-return values and exit cleanly.
* Exception: in CS50 we recommend use of a function called `parse_args()`, and it's often cleanest for that function to exit when there are problems with command-line arguments.
* Always initialize variables, either when they are created, or soon thereafter.
Initialize pointers to NULL if target not yet known.
* Use `typedef` to designate abstract data types and use a name that ends in `_t` e.g. person_t, car_t, queue_t, hashtable_t, bag_t etc.
* When using pointers, use names that are suggestive of pointers: spacep, linep, endp, etc.
* Declare function prototypes with type and name of formal parameters.
* Avoid using global variables.
If they are absolutely necessary, restrict their use to a single source file using the `static` keyword.
* Do not use using `goto` unless absolutely necessary - you must have a *really* good reason for using a `goto`, in very exceptional cases.
* Avoid preprocessor macros; `#define` macros tend to be a source of difficult bugs.
Instead, use `const` for constants and use real functions (or inline functions if you must).
* Don't use "magic" numbers in your code.
Use `const` to create a named constant, e.g., `const float pi = 3.1416;`
* Use `const` wherever you can, to indicate a value that will not change.
* Use the `bool` type whenever a function should return a boolean value, or a variable should hold a boolean flag.
Avoid old C conventions that use 0 for false and non-zero for true.
* Wrap calls to `malloc()` in type-specific helper functions; see below.
* Choose either `camelCase` or `snake_case`, and be consistent.
* Break up large programs into multiple files.
Every file (except for that containing `main`) should have a corresponding `.h` file that declares all functions, constants, and global variables meant to be visible outside the file.
* Break up large functions, aiming for *strong cohesion* and *weak coupling*.


***Always remember: You are writing for clarity and communication, not to show how clever you are or how short and dense you can make your code.***


### Commenting:

Comment your code as you write it: it is much easier to write comments while your intentions are fresh in your mind than to go back later and do it.

Keep comments short, simple and to the point.
Comment wherever the code is not self-describing (see the reading assignments).
Use the `//` style of commenting for one-line comments, and the `/* ... */` style for multi-line block comments.

Use four types of comments:

 * Start-of-file comments.
 * Start-of-function comments.
 * Paragraph comments
 * End-of-line comments

Use them in the following fashion:

***Start-of-file-comments.***
You should place a block comment at the start of each file.
This comment should include the names of programmers, the date the file was written, and a high-level description of the file's contents, e.g.,

```c
/*
* stack.c     Bill Stubblefield     November 20, 1994
*
* This file contains the definitions of a stack class.  It includes functions:
*
*     ... list functions, with brief descriptions (if needed)
*
*/
```

***Start-of-function comments.***
Write a header for each function.
This comment should describe the *contract* between the caller and the function: describe what the function does, the meaning of its parameters, the meaning of its return value (if any), and assumptions about the responsibilities of the caller and the function.
For example, if a function

```c
       float sqrt(float number);
```

requires its argument to be positive, document it.
Similarly, specify any constraints on the output.
List all error conditions and what the function does with them.
List any side effects.
Be explicit about memory allocation: if the function returns a pointer to space from `malloc`, who is responsible for calling `free`?

If the function algorithm is not obvious, describe it (often a good idea).
Also, if you borrow the algorithm from another source, credit the source and author.

***Paragraph comments.***
Often procedures can be divided into a series of steps, such as initialization, reading data, writing output.
Place a small comment before each such section describing what it does.

***End-of-line comments.***
Place a brief comment at the end of those lines where needed to clarify the code.
Don't overdo it, but use them to call the reader's attention to subtleties in the code.
Align the comments so that all the comments for a function begin in the same column, although this column can vary for different functions.

### Spacing:

Place a space after keywords like `if`, `else`, `for`, `while`, `do`, `switch`, etc., after commas in function calls, after semicolons in a for loop, between a right parenthesis and a left bracket, and around binary operators (except `.` and `,` and `->`).
Remember that assignment is a binary operator.
I usually do not put spaces between a function name and its parameter list, or an array name and its subscripts.
For example,

```c
   for (i = 0; i < N; i++) {
       x = x + f(A[i], i);
   }
```

### Indenting:

Let your text editor help you auto-indent your code.
Often, trouble with auto-indentation is a clue to your own syntax mistake (such as forgetting brackets).

When you create or open a file, emacs will recognize C by the filename extension `.c` or `.h` and switch to "C mode"; you'll see this mode on the emacs status line.
In C mode, hitting the TAB key while the cursor is on a given line indents it to the correct level, *assuming that the preceding non blank line has been indented correctly*.
Ending a line with a left bracket and hitting return will automatically indent the next line appropriately.
Also, a line beginning with a right bracket will indent to the correct level.
Finally, typing `//` on a new line will create a comment and indent it to the line of code.

Dynamic memory allocation
-------------------------

Avoid sprinking calls to `malloc()` and `free()` throughout your code.
Instead, think about the kinds of things you need to create and destroy, and write type-specific wrapper for each such type.
For example, if your program manipulates things of type `struct listnode`, you would write two functions:

```c
    struct listnode *listnode_new(...);
    void listnode_delete(struct listnode *node);
```

The first function calls `malloc(sizeof(struct listnode)` and initializes all of its contents, perhaps using parameters passed by the caller.
The second calls `free(node)`.
Both involve careful error-checking code.
See example [names6.c]({{site.examples}}/names6.c).

There are many advantages to this approach:

* The mainline code is more readable, because it's clear what `listnode_new()` is doing.
* Code involving `malloc` can sometimes be tricky, and you isolate that trickiness in one spot and focus on getting it right once.
* Some new types might need multiple `malloc` calls, as in our linked-list example [names6.c]({{site.examples}}/names6.c).
All those `malloc` calls (and corresponding `free` calls) can be in the `new`/`free` functions.
* The `new` function acts like a 'constructor' in object-oriented languages and can ensure the newly returned memory is initialized, or at least, not random bytes.
* You can insert debugging output or reference-counting logic, or set debugger breakpoints, in these `new`/`free` functions and immediately have that feature apply to *all* occurrences of your program's work with this type.

Program structure
-----------------

Although C allows us to be very flexible with where we put declarations, a standard layout makes it easier to read the code.
A good convention is:

```c
/*
 *  Start-of-file-comments
 */

#include <stdio.h>
#include <stdlib.h>
. . .

// global type and constant definitions
const float PI = 3.1416;
. . .

// function prototypes
void push(int item);

/* ***************************
 *  Start-of-function-comments
 */
int main(const int argc, char *argv[])
{
	// local const, type and variable declarations
	// body of code
}

/* ***************************
 *  Start-of-function-comments
 */
void push(int item) {
	// local const, type and variable declarations
	// function body
}
```
Although you can declare variables at anytime before they are used, it is sometimes best to place all declarations at the beginning of the function.
That way a reader can easily find them.
There are times when it is convenient or prudent to do otherwise; we'll come back to this issue.

It is also a good idea to break large programs up into multiple files.
For example, a 'stack' module may be declared in 'stack.h', defined in 'stack.c', and used in 'main.c'.

Simplicity
-----------

This single most important thing you can do to write good code is to keep it simple.
As William of Occam said in the 14th century: "Do not multiply entities without necessity." Simplicity has many aspects; a few of these include:

**Make all functions small, coherent and specific.**
Every function should do exactly one thing.
A good rule of thumb is that you should be able to describe what a function does in a single sentence.
Generally, C functions occupy less than a page, with most functions occupying 10-30 lines.

**Use small parameter lists.**
Avoid extremely long parameter lists.
If you find the parameters to a function growing, ask yourself if the function is trying to do too much, or if the function is too vague in its intent.

**Avoid deeply nested blocks.**
Structures such as `if`, `for` and `while` define blocks of code; blocks can contain other blocks.
Try not to nest blocks too deeply.
Any function with more than a couple levels of nesting can be confusing.
If you find yourself with deeply nested structures, consider either simplifying the structure or defining functions to handle some of the nested parts.

**Use the simplest algorithm that meets your needs.**
Einstein once said: "Things should be as simple as possible, but no simpler." This is good advice for selecting an algorithm.
There are a great many extremely clever, complex algorithms in computer science.
Make an effort to know them and use the algorithm that meets your needs for efficiency.
Do not shun complex algorithms, but do not choose them without reason.

**Be consistent.**
Consistency can come in many forms.
A few of these include:

 * Try to be consistent in numbers and types of function parameters.
If two functions have a similar function, try to give them similar sets of parameters.
 * Try to be consistent in your use of loops and other program constructs.
 * Use consistent naming and commenting styles.

**Don't be clever.**
Samuel Johnson once said (I may not be quoting him exactly) "When you find something particularly clever in your writing, strike it out." C offers many constructs, such as conditional expressions, unary operators, etc.
that make it possible to write extremely compact, dense unreadable code.
Use these features, but also ask yourself: "Will another programmer understand what I mean here?"

Practice defensive programming!
-------------------------------

It is important you write C programs defensively.
That is, you need to check the input the program receives, make sure it is as expected (in range, correct datatype, length of strings, etc.), and, if it is not acceptable, provide appropriate message(s) back to the user in terms of the program usage.
The user should **never** be able to cause your program to adversely impact any aspect of the system it's running on, including system files, other users' files or processes, or network access.

 * Make sure command-line arguments and function parameters have legal values.
 * Check the results of all calls to standard libraries or the operating system.
For example, check all memory allocations (`malloc`) to detect out-of-memory conditions.
 * Check all data obtained from users or other programs.
 * Check limit conditions on loops and arrays.
For example, what happens if you try to access a value that is out of bounds?

When you detect an error condition, first consider ways to modify the
code to prevent the error from happening in the first place.  If that
is not possible, ask if there is a way the code can recover from the
error.  If there is no reasonable way of recovering, print an error
message and exit the program.

In short, if someone can crash your program, you lose points, whether
in this class or in a future job.


Required compiler options
-------------------------

For **all** C programming assignments in this class, you must use (at
a minimum) the following `gcc` compile options:

```bash
    gcc -std=c11 -Wall -pedantic ... program.c ...
```

All programs **must** compile without errors or warnings.

These instruct the compiler to compile for the C11 language standard,
display all possible warnings, and to issue warnings if any non-ISO
standard C features proided by `gcc` are used, respectively.  You will
likely need to add other options to these; for example, if you use
mathematics functions, you need to `#include <math.h>` in your C
program and add `-lm` to the command line.

