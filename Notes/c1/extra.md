---
layout: page
title: Extra - Introduction to C
---

This "lecture extra" is meant to complement today's [lecture notes](index.html).

***Warning: the examples in (or cited by) this "lecture extra" may not follow CS50 programming style."***

We cover

-   Operators
-   Precedence
-   Base data types
-   Storage modifiers
-   Scope rules of global and local variables
-   Flow of control in C programs


## Let's C !

### Basic Operators

Nearly all operators in C are identical to those of Java.
However, the role of C in system programming exposes us to much more use of the shift and bit-wise operators than in Java.
Here are the basic operators:

- Assignment
    `=`
- Arithmetic
    `+, -, *, /, %, unary`
- Priorities may be overridden with `( )`'s.

- Relational (all of these have the same precedence)
    `>, >=, <, <=`
- Equality
    `==` , `!=`
- Logical
    `&&` (and), `||` (or), `!` (not)

### Pre- and post- decrement and increment operators

Any (integer, character or pointer) variable may be either incremented or decremented before or after its value is used in an expression.

For example :
`--fred`  will decrement `fred` before its value is used

`++fred`  will increment `fred` before its value is used

`fred--`  will get (old) value and then decrement `fred`

`fred++`  will get (old) value and then increment `fred`

Let's write some C code to look at pre and post increment and decrement.

C code: [increment.c]({{site.examples}}/increment.c)

```c
/*
  file: increment.c

  Description: Illustrate pre and post increment and decrement.
*/

#include <stdio.h>

int main() {

     int fred = 3, a=3;

     printf("Start; fred = %d and a = %d\n", fred, a);
     a = --fred;
     printf("a = --fred; fred = %d and a = %d\n", fred, a);
     a = ++fred;
     printf("a = ++fred; fred = %d and a = %d\n", fred, a);
     a = fred--;
     printf("a = fred--; fred = %d and a = %d\n", fred, a);
     a = fred++;
     printf("a = fred++; fred = %d and a = %d\n", fred, a);

     return 0;

}
```

Once we have the C code we have to compile it with `gcc` with the various compiler switches we discussed in Lecture 1.
To see ALL of the options, try

```bash
gcc --help -v
# or
man gcc
```

We'll use `mygcc -o filename filename.c `as our compilation command for now.
Later, we'll use the more powerful `make` utility.
In `.bashrc` we already defined `mygcc` as an alias:

```bash
$ alias mygcc
alias mygcc='gcc -Wall -pedantic -std=c11 -ggdb'

$ mygcc -o increment increment.c
$ ls -l increment
-rwxr-xr-x   1 atc  admin  13344 Jan 14 21:51 increment
$ ./increment
Start; fred = 3 and a = 3
a = --fred; fred = 2 and a = 2
a = ++fred; fred = 3 and a = 3
a = fred--; fred = 2 and a = 3
a = fred++; fred = 3 and a = 2
```

The compiler produces an executable file named `increment`.

You do not have to use `chmod` to make it an executable.
The compiler takes care of that when it creates an executable with the correct permission for the file `increment `.

Try it yourself.
Save the file in your directory (e.g., `cs50/code/`), and compile and run the code.
Verify that the output matches the above.

### More about gcc and mygcc

A word of warning: Whether using `gcc -o hello hello.c` or `mygcc -o hello hello.c` you must take care to avoid getting the order of the files wrong with the `-o` switch which tells the complier that the name of the file following the `-o` switch will be the name of the executable.
One student compiled the correct way `mygcc -o hello hello.c` (producing a executable `hello` correctly) and then recompiled but got the order wrong: `mygcc -o hello.c hello`.
What the `gcc` compiler did wasn't pleasant.
It took the executable `hello` as the source file and and `hello.c` as the name of the executable to be created.
The result was the real source file `hello.c` disappeared!
Well, it didn't actually disappear, it was just erased by the compiler as it got ready to produce a new output file of that same name.
So please be careful: the `-o` tells the compiler that the executable it creates should be given the name that follows the `-o`.
You can always use the default `a.out` and not use the `-o` option if concerned.

The other `gcc` switches are important to use because make sure we write good clean code.
Let`s discuss what these `gcc` options are (`-Wall -pedantic -std=c11`):

-   `-Wall` turns on all optional warnings which are desirable for normal code.
-   `-pedantic` checks programs for strict ISO C conformance and issues all the warnings demanded by strict ISO C.
-   `-std=c11` indicates the language standard we want.
By using these options the compiler forces us to resolve various warning that you would not see if you just used `gcc` without any switches.

Always use these options (`-Wall -pedantic -std=c11`) from now on in this course.
You can do a `man gcc` and look at the option meanings for the nitty gritty details on these settings.


### Bitwise operators and masking

`&` (bitwise and), `|` (bitwise or), `~` (bitwise negation).

You can use these to check if certain bits are on, as in `(nextchar & 0x30)`.
Do you see how this works?

Shift operators `<<` (shift left), `>>` (shift right)

Shifting bits to the left or right.
Note: results may vary based upon whether the type of the variable being shifted is "signed" or "unsigned".
See H&S pp.231-233.

### Combined operators and assignment

**Example [combined.c]({{site.examples}}/combined.c)**

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
        int a,b,c,d;

        a=10; b=20; c=30; d=4;

        // these lines ...
        a=a+2;
        b=b-12;
        c=c*(d-2);
        printf( "a=%d, b=%d, c=%d\n", a, b, c);

        a=10; b=20; c=30; d=4;

        // could have been written this way
        a += 2;
        b -= 12;
        c *= d-2;
        printf( "a=%d, b=%d, c=%d\n", a, b, c);

        exit (0);
}

```

### Type coercion

C permits assignments and parameter passing between variables of different types using type casts or coercion.
Casts in C are not implicit, and are used where some languages require a 'transfer function'.
We will see examples of C's cast operator later in the course.

### Precedence of operators

Expressions are all evaluated from left-to-right, and the default precedence may be overridden with brackets.

| Operator  |
| Precedence|
| :--------:|
| *highest* |
| `( )`     |
| `++ -- !` |
| `* / % |` |
| `+ - `    |
| `==  !=`  |
| `&`       |
| `|`       |
| `&&`      |
| `||`      |
| `?:`      |
| `=`       |
| `,`       |
| *lowest*  |

### Variable names

Variable names (and type and function names as we shall see later) must commence with an alphabetic or the underscore character `A-Z a-z _` and be followed by zero or more alphabetic, underscore or digit characters `A-Z a-z 0-9`.
Most C compilers, such as `gcc`, accept and support variable, type, and function names to be up to 256 characters in length.
(Some older C compilers only supported variable names with up to 8 unique leading characters and keeping to this limit may be preferred to maintain portable code.) It is also preferred that you do not use variable names consisting entirely of uppercase characters.
All-uppercase variable names are typically reserved for constants (such as `MAXBUFSIZE`, `AVAGADROS_NUMBER`, `MAXUSERS`).

Importantly, C variable names are case sensitive, so `MYLIMIT`, `mylimit`, `Mylimit` and `MyLimit` are four different variable names.

There are some specific variable/function naming styles that you may encounter.
The major ones are

* **camelCase**: writing compound words with the first letter of each word capitalized, except for the first word's first letter, which is not capitalized.

* **PascalCase**: writing compound words just as in camelCase* with the first letter of the first word also capitalized.
(In Java it is common to use this case for class names, but Camel case for member names.)

* **snake\_case**: writing compound words with an underscore between each word with little, if any, capitalization.

For a short history of how these came about and some discussion, see Brad Abrams' [blog post](http://blogs.msdn.com/b/brada/archive/2004/02/03/67024.aspx).

Any programming project, including all of your assignments, should pick a variable/function naming style and **stick with it**.

### Base types

Variables are declared to be of a certain type.
This type may be either a base type supported by the C language itself, or a user-defined type consisting of elements drawn from C's set of base types.
C's base types and their representation on our lab's systems are:

| type  | description |
| :---- | :---------- |
| `char`  | the character type, 8 bits long |
| `short` | the short integer type, 16 bits long |
| `int`   | the standard integer type, 32 bits long |
| `long`  | the longer integer type, 64 bits long |
| `float` | the standard floating point (real) type, 32 bits long (about 10 decimal digits of precision) |
| `double` | the extra precision floating point type, 64 bits long (about 17 decimal digits of precision) |

We can determine the number of bytes required for datatypes (and other things, as we will see later) with the `sizeof` operator.
In contrast, Java defines how long each datatype may be.
In C, the sizes vary from machine to machine, with the details managed by the compiler.
C's only guarantee is that:

    sizeof(char) <= sizeof(short) <= sizeof(int) <= sizeof(long)

Let's write some C code to look at these base data types.
We will use the `sizeof` operator and the `printf` function.
We will also define variables of each of the base types and print the initialized values as part of the `data-types.c` code.

**Example [data-types.c]({{site.examples}}/data-types.c)**

The contents of data-types.c looks like this:

```c
/*
  file: data-types.c

  Description: Sets up variables for different base data types, intialises them
  and print the data and the size of the base data types in number of bytes.

  Revised version of code pg. 96 (Program 2.10) (Bronson) "First Book on ANSI C"
*/

#include <stdio.h>

int main() {

  char ch = 'a';
  int in = 2;
  short sh = 3;
  long lo = 4;
  long long llo = 1234567890;
  float fl = 1000.256734;
  double db = 11e+23;
  long double ld = 10e+30;

  printf("-------contents ------- sizeof()------\n\n");

  printf("contents of char is %c --- sizeof %ld bytes\n\n", ch, sizeof(char));

  printf("contents int is  %d --- sizeof  %ld bytes\n\n", in, sizeof(int));

  printf("contents short is  %d --- sizeof %ld bytes\n\n", sh, sizeof(short));

  printf("contents long is %ld --- sizeof %ld bytes\n\n", lo, sizeof(long));

  printf("contents long long is %lld --- sizeof %ld bytes\n\n", llo, sizeof(long long));

  printf("contents float is %f --- sizeof %ld bytes\n\n",fl, sizeof(float));
  printf("contents double is  %e --- sizeof %ld bytes\n\n",db, sizeof(double));
  printf("contents long double is  %LG --- sizeof %ld bytes\n",ld, sizeof(long double));

  return 0;

}
```

Let's compile and run the code.

```bash
$ mygcc -o data-types data-types.c
$ ./data-types
-------contents ------- sizeof()------

contents of char is a --- sizeof 1 bytes

contents int is  2 --- sizeof  4 bytes

contents short is  3 --- sizeof 2 bytes

contents long is 4 --- sizeof 8 bytes

contents long long is 1234567890 --- sizeof 8 bytes

contents float is 1000.256714 --- sizeof 4 bytes

contents double is  1.100000e+24 --- sizeof 8 bytes

contents long double is  1E+31 --- sizeof 16 bytes
```

Check it out: Save the file in your directory; compile and run the code.
Check the output.


### Storage modifiers of variables

Base types may be preceded with one or more storage modifier:

| storage | meaning |
| modifier | |
| :------ | :------ |
| `auto`  | the variable is placed on the stack (default, deprecated) |
| `const`  | the variable is a constant, and can/will never change value |
| `extern` | the variable is defined outside of the current file |
| `register` | request that the variable be placed in a register (mostly ignored) |
| `static` | the variable is placed in global storage with limited visibility |
| `typedef` | introduces a user-defined type |
| `unsigned` | stored and used only as positive integers|

### Initialization of variables

All scalar `auto` and `static` variables may be initialized immediately after their definition, typically with constants or simple expressions that the compiler can evaluate at compile time.
The C99 language defines that all uninitialized global variables, and all uninitialized static local variables will have the starting values resulting from their memory locations being filled with zeroes - conveniently the value of `0` for an integer, and `0.0` for a floating point number.

### Scope rules of global variables

*Scope* is defined as the section (e.g., function, block) of the program where the variable is valid and known.

In Java, a variable is simply used as a name by which we refer to an object.
A newly created object is given a name for later reference, and that name may be re-used to refer to another object later in the program.
In C, a variable more strictly refers to a memory address (or contiguous memory address starting from the indicated point) and the type of the variable declares how that memory's contents should be interpreted and modified.

C only has two true lexical levels, `global` and `function`, though sub-blocks of variables and statements may be introduced in sub-blocks in many places, seemingly creating new lexical levels.
As such, variables are typically defined globally (at lexical level 0), or at the start of a statement block, where a function's body is understood to be a statement block.

Variables defined globally in a file, are visible until the end of that file.
They need not be declared at the top of a file, but typically are.
If a global variable has a storage modifier of `static`, it means that the variable is only available from within that file.
If the `static` modifier is missing, that variable may be accessed from another file if part of a program compiled and linked from multiple source files.

The `extern` modifier is used (within a given file) to declare that the indicated variable is defined in another file.
The variable may be *declared* as `extern` in all files, but must be *defined* (and not as a `static`!) in only a single file.

### Scope rules of local variables

Variables may also be declared at the beginning of a statement block, but may not be declared anywhere other than the top of the block.
Such variables are visible until the end of that block; most variables are declared at the top of a function's block, and are thus visible until the end of the current function.
A variables name may shadow that of a global variable, making that global variable inaccessible.
Blocks do not have names, and so shadowed variables cannot be named.
Local variables are accessible until the end of the block in which they are defined.

Local variables are implicitly preceded by the `auto` modifier as control flow enters the block; memory for the variable is allocated on the run-time stack.
The memory is automatically deallocated (or simply becomes inaccessible) as control flow leaves the block.
The implicit `auto` modifier facilitates recursion in C as each entry into a new block allocates memory for new local variables, and these unique instances are accessible only while in that block.

If a local variable is preceded by the `static` modifier, its memory is not allocated on the run-time stack, but in the same memory as for global variables.
When control flow leaves the block, the memory is not deallocated, and remains for the exclusive use by that local variable.
The result is that a `static`local variable retains its value between entries to its block.
Whereas the starting value of an `auto` local variable (sitting on the stack) cannot be assumed (or more correctly, should be considered to contain a totally random value), the starting value of a static local variable is as it was when the variable was last used.

### Examples of global and local variables

Let's look at some code snippets to reinforce the ideas of local and global variables and the issue of the scope of these variables in a section of code.

**Example [scope.c]({{site.examples}}/scope.c)**

```c
/*

  File: scope.c

  Description: Illustrates the use of global and local variables and
               global function prototypes.


   Revised code taken from pg. 330 (Program 7.1) (Bronson) "First Book on ANSI C"

*/

#include <stdio.h>

/* firstnum is a global variable not defined on the main() stack. It has full scope
   of all functions in the file scope.c. Any code in the file can read and write to it.
   Once main() teriminates the variable is dellocated and no longer exists
*/

int firstnum; /* create a global variable named firstnum */

void valfun(); /* global function prototype */


int main()
{
  int secnum; /* create a local variable named secnum */
  firstnum = 10; /* store a value into the global variable */
  secnum = 20; /* store a value into the local variable */

  printf("\nFrom main(): firstnum = %d",firstnum);
  printf("\nFrom main(): secnum = %d\n",secnum);

  valfun(); /* call the function valfun */

  printf("\nFrom main() again: firstnum = %d",firstnum);
  printf("\nFrom main() again: secnum = %d\n",secnum);

  return 0;
}


void valfun() /* no values are passed to this function */
{

  /* secum is a local variable created on the stack when valfun() executes.
     When valfun() exits the stack is deallocated and the variable no
     longer exists. It is local and its scope is valfun() */

  int secnum; /* create a second local variable named secnum */
  secnum = 30; /* this only affects this local variable's value */


  printf("\nFrom valfun(): firstnum = %d",firstnum);
  printf("\nFrom valfun(): secnum = %d\n",secnum);
  firstnum = 40; /* this changes firstnum for both functions */

}
```

If we run the code the output is as follows:

```bash
$ mygcc -o scope scope.c
$ ./scope

From main(): firstnum = 10
From main(): secnum = 20

From valfun(): firstnum = 10
From valfun(): secnum = 30

From main() again: firstnum = 40
From main() again: secnum = 20
```

Study the output.
Is it what you expected?

The first thing to note about the source code is that it defines a global variable `firstnum` that's scope is the complete file and therefore is accessible from `main()` and the `valfun()`.

Note `scope.c` has a `main()` and a `valfun()` function.
The *prototype* for `valfun()` is declared at the top of the file, giving it global scope in the file `scope.c`.
(We will discuss prototypes more later.) Both `main()` and `valfun()` update and print the value of `firstnum`, which represents a variable with a memory address (space is not allocated on the stack as in the case of auto variables such as `secnum`).
Note that `main()` and `valfun()` both have local variables named `secnum`.
This name collision is not a problem and causes no clash because of the scope of these two different local variables (that happen to have the same name) only have local scope inside the `main()` and `valfun()` functions, respectively.
Their instances are private to `main()` and `valfun()`, respectively.
They have no association other than having the same names.
They are auto variables created on the stack and no longer exist when the function exits.
For example, `valfun()` creates a variable for `secnum` of integer type on its local stack when it executes, but when it returns control to `main()` the stack is deallocated and the variable no longer exists.
In contrast, the global variable `firstnum` and its current value are not changed when `valfun()` exits.

### Examples of auto and static local variables

Consider another storage modifier that is impacted by scope: `static`.
Here the variable is placed in global storage with limited visibility depending on where it is defined.
Let's look at two code snippets that illustrate the use of local auto and static variables.
These represent two important cases in C.

First, let's look at the case of auto local variables.

**Example: [auto.c]({{site.examples}}/auto.c)**

```c
/*

  File: auto.c

  Description: Illustrates the auto local variables

  Code taken from pg. 336 (Program 7.2) (Bronson) "First Book on ANSI C"

*/


#include <stdio.h>

void testauto(); /* function prototype */

int main()
{
  int count; /* create the auto variable count */
  for(count = 1; count <= 3; count++)
    testauto();

  return 0;
}

void testauto()
{
  int num = 0; /* create the auto variable num */
               /* and initialize to zero */

  printf("The value of the automatic variable num is %d\n", num);
  num++;
}
```

If we run the code the output is as follows:

```bash
$ ./auto
The value of the automatic variable num is 0
The value of the automatic variable num is 0
The value of the automatic variable num is 0
```

Study the output.
Is it what you expected?

Now let's look at the case when `num` is defined as `static` inside the scope of the function `teststat()`.
Note, that the value of `num` is now persistent across multiple invocations of the function.
This is in direct contrast to the auto local varable of the last code snippet - i.e., `auto.c`.
In essence, the operator `static` allocates memory to the variable of type `int` that is outside the stack just like a global variable in `scope.c` - i.e., `firstnum`.
However, the distinction here is that `static` is not global.
It is only accessible in the function `teststat()`.
We hope that clarifies the issue of scope, local and global variables and the issue of auto variables and static variables.

First, let's look at the case of static local variables.

**Example [static.c]({{site.examples}}/static.c)**

```c
/*

  File: static.c

  Description: Illustrates the use of auto variables, with `static`.


   Revised code taken from pg. 336 (Program 7.2) (Bronson) "First Book on ANSI C"

*/ 


#include <stdio.h>

void teststat(); /* function prototype */

int main()
{
  int count; /* count is a local auto variable */

  for(count = 1; count <= 3; count++)
    teststat();

  return 0;
}

/*  Note, that the varuable num in teststat() is only set to zero once. The value set by 
    the local scope static variable num detains its value when teststat() returns.
*/

void teststat()
{
  static int num=0; /* num is a local static variable */

  printf("The value of the static variable num is now %d\n", num);
  num++;

}
```

If we run the code the output is as follows:

```bash
$ ./static
The value of the static variable num is now 0
The value of the static variable num is now 1
The value of the static variable num is now 2
```

Is this what you expected?

Question: If I have defined `static int num;` at the top of `static.c` how would that change the scope of the static variable?
Is it different to `int num`; as defined as global variable (like `firstnum` in `scope`.c)?

### Flow of control in a C program

Control flow within C programs is almost identical to the equivalent constructs in Java.
However, C provides no exception mechanism, and so C has no `try`, `catch`, and `finally`, constructs.

Conditional execution

```c
      if ( expression )
           statement1;
      if ( expression ) {
           statement1;
           statement2;
           ......
      }

      if ( expression )
           statement;
      else
           statement;
```

Of significance, and a very common cause of errors in C programs, is that C (before C99) has no Boolean datatype.
Instead, any expression that evaluates to the integer value of 0 is considered false, and any nonzero value as true (the opposite of bash!).
A conditional statement's controlling expression is evaluated and if non-zero (i.e., true) the following statement is executed.
Most errors are introduced when programmers (accidentally) use embedded assignment statements in conditional expressions:

```c
      if (loop_index = MAXINDEX )
           statement;

       /* instead of ... */

       if (loop_index == MAXINDEX )
          statement;
```

A good habit to get into is to place constants on the left of (potential) assignments:

```c
      if (0 = value )
           statement;
```

When compiling with `gcc -std=c11 -Wall -pedantic` the compiler will complain about the use of assignment operators inside `if` conditions ... the only way to 'shut up the compiler' is to use extra parentheses:

```c
      if ( ( loop_index = MAXINDEX ) )
           statement;
```

C's other control flow statements are very unsurprising:

```c
      while ( conditional-expression ) {
           statement1;
           statement2;
           ......
      }

      do {
           statement1;
           statement2;
           ......
      } while ( conditional-expression );


      for( initialization ; conditional-expression ; adjustment ) {
           statement1;
           statement2;
           ......
      }
```

Examples of code snippets:

```c
    /* Loops: using the for statement */

    #define ARRAY_LENGTH 100

    long array[ARRAY_LENGTH];
    int i;

    for ( i = 0; i < ARRAY_LENGTH; i++) {

       array[i] = 4 * i;
       printf('Value of i is %d\n", i);

    }
```

Any of the components of the `for` statement's *for-expressions* may be missing, If the conditional-expression is missing, it is always true.
Infinite loops may be requested in C with `for( ; ; )` ... or with `while(1)` ...

### The equivalence of for and while

```c
      for ( expression1 ; expression2 ; expression3 ) {
             statement1;
      }


      expression1;
      while ( expression2 ) {
            statement1;
            expression3;
      }
```

Example of equivalence using the `while` statement

```c
    i = 0;

    while (i < ARRAY_LENGTH) {

       array[i] = 4 * i;
       printf('Value of i is %d\n", i);
       i++;

    }
```

### The switch statement

```c
      switch ( expression ) {
           case const1 : statement1; break;
           case const2 : statement2; break;
           case const3 :
           case const4 : statement4;
           default : statementN; break;
      }
```

One of the few differences here between C and Java is that C permits control to "drop down" to following case constructs, unless there is an explicit `break` statement.

**Example [operator.c]({{site.examples}}/operator.c)**

```c
/*

  File: operator.c

  Description: Implements basic operations (multiplication, division, addition, modulos.


  Revised version of code pg. 191 (Program 4.6) (Bronson) "First Book on ANSI C"

*/ 

#include <stdio.h>

int main() {

  int opselect;
  float fnum, snum;

  printf("Please type in two numbers: ");
  scanf("%f %f", &fnum, &snum);
  printf("Enter a select code:");
  printf("\n 1 for addition");
  printf("\n 2 for multiplication");
  printf("\n 3 for division : ");
  printf("\n 4 for modulus  : ");
 
  scanf("%d", &opselect); 

  // This line below as an intentional bug. It is commented out. 
  // it causes a segmentation fault (segfault for short)

  //scanf("%d", opselect); 

  switch (opselect) {

    case 1:
      printf("The sum of the numbers entered is %6.3f\n", fnum + snum);
      break;
    case 2:
      printf("The product of the numbers entered is %6.3f\n", fnum * snum);
      break;

    case 3:
      if (snum != 0.0)
        printf("The first number divided by the second is %6.3f\n",fnum / snum);
      else
		      printf("Division by zero is not allowed\n");
      break; 

    case 4:
      printf("The modulus of the numbers entered is %d\n", (int)fnum % (int)snum);
      break;

    default:
      printf("Need to enter a number between 1-4\n\n"); 

 }

 return 0;
}
```

### The break statement

```c
      for ( expression1 ; expression2 ; expression3 ) {
           statement1 ;
           if( ... )
              break;
           statementN ;
      }

      while ( expression1 ) {
           statement1 ;
           if( ... )
              break;
           statementN ;
      }

      switch ( expression1 ) {
           case const1:
              statement 1;
              break;

           case const2:
              statement 2;
              break;

           case const3:
              statement 3;
              break;

           default:
              statement n;
              break;

       }
```

### The continue statement

```c
      for ( expression1 ; expression2 ; expression3 ) {
           statement1 ;
           if( ... )
              continue;
           statementN ;
      }

      while ( expression1 ) {
           statement1 ;
           if( ... )
              continue;
           statementN ;
      }
```

