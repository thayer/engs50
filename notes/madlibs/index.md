---
layout: page
title: More C programming
---

In this lecture, we continue our accelerated introduction to the C programming language.

### Goals

Today we learn about

- processing command-line arguments
- opening files for reading and writing
- scanning input files character by character
- CS50 coding style, by example.

<!-- Terminal [script](script.txt) from today's class. -->

## Mad Libs

Many of you may be familiar with the [Mad Libs](http://www.madlibs.com) books; each page is a game in which one player reads through a short story that contains fill-in blanks.
Each blank space is labeled with a part of speech, e.g., "noun", "verb", "adverb", and so forth.
The other players -- who cannot see the story -- respond with words, and the first player writes them in the corresponding blanks.
When all blanks are full, the first player reads the complete story.
The results are often amusing!

Today we look at [madlib.c]({{site.examples}}/madlib.c), which has usage

```
madlibs template.txt output.txt
```

where the file `template.txt` has substitutable codes enclosed in angle brackets, e.g., `<noun>` or `<adjective>`.
The user is prompted for each, in turn, on stdout, and provides answers on stdin.
The translated file is then written to the output file.
Here is a (not very funny) example template:

```
$ cat madlib1.txt
Dear class,

 Welcome to <subject of study> <course number>, taught by Professor
 <professor name>.  In this class you will <verb> and learn about the
 history of <plural noun>.  You will <adverb> enjoy it!  
$
```
and a not-funny run of the program:

```
$ ./madlib madlib1.txt madlib1.out
subject of study: Computer Science
course number: 50
professor name: Kotz
verb: code
plural noun: computers
adverb: thrillingly
done! read your Mad Lib in 'madlib1.out'
$ cat madlib1.out
Dear class,

 Welcome to Computer Science 50, taught by Professor
 Kotz.  In this class you will code and learn about the
 history of computers.  You will thrillingly enjoy it!
$
```

Now you can see why the same player should not write both the template and the words to fill in!  :-)

### madlibs.c

Let's look at the [madlib.c]({{site.examples}}/madlib.c) code.
To compile it,

```
mygcc madlib.c readline.c -o madlib
```

**Things you should notice:**

* The file header comment - giving name and usage of the program, assumptions, exit status, author, date.
* the `include` files for standard libraries and our custom `readline` function.
* the use of global variables - here, constants
* the function prototype for `fillTemplate()`
* the arguments `argc` and `argv` passed to `main()` by Unix
	* these are the command-line arguments, parsed by the shell and passed to Unix when it asks Unix to run the program; Unix passes them to the C runtime, which passes them to `main()`.
	* notice that `argv[]` is an array of character pointers, aka, an array of strings.
	* the argument `argc` tells you how many strings are in the array `argv`, from `argv[0]` through `argv[argc-1]` because C arrays start at zero.
* the declaration of local variables inside `main`
	* because we can always assume `argc >= 1`, we can safely use `argv[0]` -- it is always the name of the command used to run the program. I save a pointer to this string in `progName` for readability.
* we check to see whether the correct number of arguments were provided
	* if not, we print a helpful 'usage' message
	* if so, we save a pointer to the two arguments in variables with descriptive names
* we open the template file for reading ("r")
* we open the output file for writing ("w")
* the use of an assignment statement as a value
	* the statement `x = 5` is actually an expression with value 5.
	* thus, we can use it anywhere a value is needed; it is best to put it inside parentheses for readability, e.g., `y = (x = 5)` assigns 5 to both x and y.
	* here we are saving the results of `fopen` in a variable *and* testing that result in an `if` statement.
	* you'll see this same form in the `while` loops below.
* useful error messages printed to stderr.
* the call to `fillTemplate()` pushes all the program logic outside `main()`, allowing `main` to focus exclusively on parsing arguments, setting up, and cleaning up - and allowing readers of `fillTemplate` to focus on the specifics of how it works without all this initialization/cleanup cruft in the way.
* remembering to close files when done with them; not strictly necessary here, because we're going to exit immediately afterward, but always a good practice.
* a useful concluding message so the user knows they're done and whether it was successful.

**In `fillTemplate()`, notice**

* the header comment that explains what this function does and what it returns
* the variable declarations with a comment about each one.
* the use of `const` to give names to certain constants.
	* this improves readability.
	* if I ever want to change them, I need only change one place.
* two strings, represened as character arrays.
* an outer loop and an inner loop
* the outer loop copies characters from input to output,
* use of `fgetc` to read a character from a file
* use of `fputc` to write a character to a file
* but if `codeStart` character appears, run the inner loop to scan characters into the `codeName` string.
* we take care not to overflow the `codeName` string.
* we sensibly handle the overflow case.
	* which includes scanning off input until we find the end.
* prompting for input, and using `readline()` to read a line as input.
* stripping off the last character of the input string
* using `fputs` to write a string to output file
* using `feof` to test whether we actually reached end of file.
	* the loop ends when `fgetc` returns EOF, but that can happen on error as well as on end of file.

**Stylistically, notice**

* paragraph comments at top of file and of `fillTemplate`
* one-line comments before blocks of code
* end-of-line comments for declarations and some code.
* global constants so key parameters are visible at the top
	* these don't need to be used outside `fillTemplate` so they need not be global variables, but it is (debatably) more readable having critical parameters at the top.
* curly braces around `if` clauses and loop bodies.
* use of camelCase for variable and function names.
* meaningful variable and function names.
* factorization of program into `main` and `fillTemplate`
* error checking (within the limits of our assumptions)
* naming constants rather than sprinkling them throughout.

## Activity

Today's [activity](activity.html) is to add a step to print the resulting story.

#### Bonus example

Another example that translates its input to its output; in this case, it looks for a given target string in the input - wherever it occurs, it substitutes the contents of a given *file* in the output.

 * [subtemplate.c]({{site.examples}}/subtemplate.c)
 * [subtemplate-README.txt]({{site.examples}}/subtemplate-README.txt)
 * [subtemplate-TESTING.txt]({{site.examples}}/subtemplate-TESTING.txt)
