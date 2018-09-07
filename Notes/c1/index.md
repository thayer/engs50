---
layout: page
title: Introduction to C
---

The first few lectures have been a crash course in the shell and shell programming.
Now we move to the C language.
We will spend the rest of the course developing our C and systems programming skill set by first understanding the basics of the language and then (through examples) study good code and write our own.

This lecture will serve as an introduction to the C language.
You may also want to read the "[lecture extra](extra.html)", which has lots more information about C programming that I will not have time to cover in class.


### Goals

We will learn the following from today's lecture:

- Structure of a C program
- Compiling and running a C program
- Input and output with stdin, stdout
- Random numbers
- Functions

### Reading

We elected not to require a specific textbook on C.
There are many to choose from, including a good text online (see the [Resources page]({{site.resources}})).
The Harbison and Steele book is very highly recommended and is, as I've said in class, an excellent reference and learning resource.
But it is not a tutorial.
When I do reference it, I will use the shorthand "H&S".

If you feel you need more of a C textbook, either use the one online or see the professor for recommendations of good ones.
For example, past incarnations of this course used the text by Bronson, *[A First Book of ANSI C](http://www.amazon.com/First-Book-Fourth-Introduction-Programming/dp/1418835560/ref=sr_1_1?ie=UTF8&qid=1326594741&sr=8-1)*.
It's not bad, and there are lots of others, including some that you can get electronically, like Prinz's *[C in a Nutshell](http://www.amazon.com/C-Nutshell-OReilly-ebook/dp/B0043GXMRK/ref=sr_1_2?ie=UTF8&qid=1326594935&sr=8-2)* (O'Reilly).

### Manuals

C programming depends on a suite of standard libraries for input/output, strings, math, memory allocation, and so forth.
Most or all of these functions are documented in man pages, just like shell commands.
Try `man strcpy`, for example.

> For some C functions there are shell commands with identical names; if you type `man printf`, for example, you'll see the man page for the bash `printf` command and not the C function `printf()`.
You can ask `man` to look only for library functions (section 3 of the manual) with `man 3 printf`.

C
-

C can be correctly described as a successful, general-purpose programming language, a description also given to Java and C++.
C is a *procedural* programming language, not an *object-oriented* language like Java or C++.
Programs written in C can be described as 'good' programs if they are written clearly, make use of high-level programming practices, and are well-documented with sufficient comments and meaningful variable names.
Of course, all of these properties are independent of C and are traits of good programming in any high-level language.

C has the high-level programming features provided by most procedural programming languages - strongly typed variables, constants, structured types, enumerated types, a mechanism for defining your own types, aggregate structures, control structures, recursion and program modularization.

C does not support sets of data, Java's concept of a *class* or objects, nested functions, nor subrange types and their use as array subscripts, and has only recently added a Boolean datatype.

C does have, however, separate compilation, conditional compilation, bitwise operators, pointer arithmetic and language independent input and output.
The decision about whether C, C++, or Java is the best general-purpose programming language (if that question can be decided, or even needs to be decided), is not going to be an easy one.

C is the programming language of choice for most systems-level, engineering, and scientific programming.
The world's popular operating systems - Linux, Windows, and Mac OS X, their interfaces and file systems, are written in C; the infrastructure of the Internet, including most of its networking protocols, web servers, and email systems, are written in C; software libraries providing graphical interfaces and tools, and efficient numerical, statistical, encryption, and compression algorithms, are written in C; and the software for most embedded devices, including those in cars, aircraft, robots, smart appliances, sensors, and game consoles, is written in C.
Recent mobile devices such as the iPhone, iPad, and some Microsoft products use languages derived from C, such as Objective C, C++, and C#.

> The TIOBE Programming Community index is another indicator of the popularity of programming languages.
Updated monthly, it provides a great historical look at this topic.
See the latest results [here](http://www.tiobe.com/index.php/content/paperinfo/tpci/index.html).

C's overall philosophy is "get out of the programmer's way." C is often criticized for allowing the programmer to do pretty much whatever she wants.

Examples
---------
In class we iteratively build a C version of our friend [guessprime.sh]({{site.examples}}/guessprime.sh), and then enhance it.
**Follow my classroom Terminal [script](script.txt).**

 * [guessprime1.c]({{site.examples}}/guessprime1.c): (simple replacement for the bash program)
 * [guessprime2.c]({{site.examples}}/guessprime2.c): (add readGuess() function)
 * [guessprime3.c]({{site.examples}}/guessprime3.c): (move readGuess() function to bottom, declare function prototype)
 * [guessprime4.c]({{site.examples}}/guessprime4.c): (add isPrime() function; check bounds of input; args in prototypes)
 * [guessprime5.c]({{site.examples}}/guessprime5.c):  (pick a random answer)

***We did not have time to cover:***

 * [guessprime6.c]({{site.examples}}/guessprime6.c): (support command-line arguments)
 * [guessprime7.c]({{site.examples}}/guessprime7.c):  (handle non-numeric input from user)
 * [guessprime8.c]({{site.examples}}/guessprime8.c): (smarter 'readline' function, to be introduced tomorrow)
 * [guessprime9.c]({{site.examples}}/guessprime9.c): (interpret words like 'quit' on input; usage of stderr)

***I encourage you to read it on your own.***

You can compare one version with another using `diff` (here, I also use the `[]` filename expansion in bash):

```bash
[cs50@flume ~]$ diff guessprime[45].c 
2,4c2,4
<  * guessprime4.c - a C version of our bash demo program
<  *  (add isPrime() function; check bounds of input; args in prototypes)
<  * David Kotz, April 2016
---
>  * guessprime5.c - a C version of our bash demo program
>  *  (handle non-numeric input from user)
>  * David Kotz, April 2016,2017
36c36,42
<   scanf("%d", &guess);
---
>   if (scanf("%d", &guess) < 1) {
>     printf("Hey! invalid number.\n");
>     while (getchar() != '\n') {
>       ; // discard the rest of characters on input line 
>     }
>     return -1;
>   }
39a46
>     return -1;
43a51
>     return -1;
```

### Activity

Our in-class [activity](activity.html) is to extend [guessprime4.c]({{site.examples}}/guessprime4.c) with an additional function.
