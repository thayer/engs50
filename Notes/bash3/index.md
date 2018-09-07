---
layout: page
title: Introduction to Bash Programming
---

Take time for this week's [reading]({{site.baseurl}}/Reading/#week-1); it's short, important, and useful.

We are now familiar with the shell and a few commands.

In this lecture, we discuss shell programming using bash.
The main goal is to write your own scripts.
But what are *scripts?*
And what are they useful for?

### Goals

We learn the following today:

- Understanding shell script syntax and constructs
- Writing simple interactive scripts
- Writing and executing your first shell script
- Understanding more advanced constructs through examples

### Class scripts

I recorded my Terminal windows today on [Mac](script-mac.txt) and [flume](script-flume.txt).

## Interactive mode and shell scripts

The shell can be used in two different ways:

-   *interactive mode*, which allows you to enter more than one command interactively to the shell.
We have been doing this already.
However, interactive mode allows you to enter a series of commands; and
-   *shell scripts*, in which the shell reads commands a series of commands (or complex programs) from a text file.

The interactive mode is fine for entering a handful of commands but it becomes cumbersome for the user to keep re-entering these commands interactively.
It is better to store the commands in a text file called a shell script, or *script* for short, and execute the script when needed.
In this way, the script is preserved so you and other users can use it again.

In addition to calling Unix commands (e.g., `grep`, `cd`, `rm`) shell scripts can also invoke compiled programs (e.g., C programs) and other shell scripts.
Shell programming also includes control-flow commands to test conditions (`if...then`) or to do a task repeatedly (`for...do`).
These control structure commands found in many other languages (such as C, or other scripting languages like python) allow the programmer to quickly write fairly sophisticated shell programs to do a number of different tasks.

Like python, and unlike C or Java, shell scripts are not *compiled*; rather, they are *interpreted* and executed by the shell itself.

Shell scripts are used for many reasons - building and configuring systems or environments, prototyping code, or an array of repetitive tasks that programmers do.
Shell programming is mainly built on the Unix shell commands and utilities; reuse of these existing programs enables programmers to simply build new programs to tackle fairly complex jobs.


## Separating groups of commands using ';'

Let's start to build up our knowledge of how scripts work by first looking at some basic operations of the shell.
The Unix shell allows for the unconditional execution of commands and allows for related commands to be kept adjacent as a command sequence using the semicolon character as shown below:

```bash
[cs50@flume ~]$ echo Directory listing; date; ls
Directory listing
Fri Apr  1 08:58:08 EDT 2016
Archive/  primes  private/  public_html/  resources/  students	web@  ziplab1.sh*
[cs50@flume ~]$
```

## Exit status - who cares?

When using the shell interactively it is often clear when we have made a mistake - the shell warns about incorrect syntax, and complains about invalid switches or missing files.
These warnings and complaints can come from the shell's parser and from the program being run (for example, from `ls`).

Error messages provide visual clues that something is wrong, allowing us to adjust the command to get it right.

Commands also inform the shell explicitly whether the command has terminated successfully or unsuccessfully due to some error.
Commands do this by returning an *exit status*, which is represented as an integer value made available to the shell and other commands, programs, and scripts.

The shell understands an exit status of `0` to indicate successful execution, and any other value (always positive) to indicate failure of some sort.

The shell environment value `$?` is updated each time a command exits.

What do we mean by that?

```bash
[cs50@flume ~]$ echo April Fool
April Fool
[cs50@flume ~]$ echo $?
0
[cs50@flume ~]$ ls April Fool
ls: cannot access April: No such file or directory
ls: cannot access Fool: No such file or directory
[cs50@flume ~]$ echo $?
2
[cs50@flume ~]$ 
```


## Conditional sequences - basic constructs

Why do we need to use the exit status?

Often we want to execute a command based on the success or failure of an earlier command.
For example, we may only wish to remove files if we are in the correct directory, or perhaps we want to be careful to only append info to a file if we know it already exists.

The shell provides both conjunction (and) and disjunction (or) based on previous commands.
These are useful constructs for writing decision-making scripts.
Take a look at the example below in which we make three directories, then try to remove the first:

```bash
[cs50@flume ~]$ mkdir labs && mkdir labs/lab1 labs/labs2
[cs50@flume ~]$ rmdir labs || echo whoops!
rmdir: failed to remove `labs': Directory not empty
whoops!
[cs50@flume ~]$     
```

In the first example, `&&` (without any spaces) specifies that the second command should be only executed if the first command succeeds (with an exit status of `0`) - i.e., we only make the subdirectories if we can make the top directory.

In the second example, (`||`) (without any spaces) requests that the second command is only executed if the first command failed (with an exit status other than `0`).

## Conditional execution using if, then, else

There are many situations when we need to execute commands based on the outcome of an earlier command.

```bash
if command0; then
	command1
	command2
fi
```

Here `command1` and `command2` (and any other commands that might be input) will be executed if and only if `command0` returns a successful or true value (i.e., its exit status is `0`).

> The fact that `0` means true is confusing for many people!
> (In many high-level languages - like C - zero means false and non-zero means true; technology isn't always consistent.)
> The reason Unix uses `0` for success is that there is only one `0`, but there are many non-zero numbers; thus, `0` implies 'all is well' whereas non-zero implies 'something went wrong', and the specific non-zero value can convey information about *what* went wrong.

Similarly, we may have commands to execute if the conditional fails.

```bash
if command0; then
	command1
	command2
else
	command3
	command4
fi
```

Here `command3` and `command4` will be executed if and only if `command0` fails.

### First Interactive Shell Program

Entering interactive scripts - that is, a tiny sequence of commands, typed at the keyboard in an interactive shell - is an easy way to get the sense of a new scripting language or to try out a set of commands.
During an interactive session the shell simply allows you to enter an 'one-command' interactive program at the command line and then executes it.

```bash
[cs50@flume ~]$ if cp students students.bak
> then
> echo $? copy succeeded!
> else
> echo $? copy failed!
> fi
0 copy succeeded!
[cs50@flume ~]$
```

The `>` character is the *secondary prompt*, issued by the shell indicating that more input is expected.

The exit status of the `cp` command is used by the shell to decide whether to execute the `then` clause or the `else` clause.
Just for yucks, I had `echo` show us the exit status `$?`; the above example confirms that `0` status means 'true' and triggered the `then` clause.

We can invert the conditional test by preceding it with `!`, as in many programming languages:

```bash
[cs50@flume ~]$ if ! cp students students.bak
> then
> echo copy failed!
> fi
[cs50@flume ~]$ 
```
> Astute readers might note that I did not quote or escape the `!` in the echo commands.
I've noticed that the `!` is not special if it comes last, which is handy for writing interjections!

The `command0` can actually be a sequence or pipeline.
The exit status of the last command is used to determine the conditional outcome.

```bash
[cs50@flume ~]$ if mkdir backup && cp students backup/students
> then
> echo backup success
> else
> echo backup failed
> fi
backup success
[cs50@flume ~]$ 
```

In the above example, `then` was on the next line instead of at the end of the `if` line.
That's a stylistic choice; if you want it on the `if` line you simply need to put a semicolon (`;`) after the `if` condition and before the word `then`, as seen in the earlier examples.

### The test, aka [ ] command

The `command0` providing the exit status need not be an external command.
We can test for several conditions using the built-in `test` or (interchangeably) the `[ ]` command.
We use both below but we recommend you use the `[ ]` version of the test command because (a) it is more readable and (b) it's more commonly used.
Suppose I want to backup `students` only if it exists; the `-f` switch tests whether the following filename names an existing file.

```bash
[cs50@flume ~]$ if test -f students
> then
> mkdir backup && cp students backup/students || echo backup failed
> fi
[cs50@flume ~]$ 
```

Rewritten with `[ ]`,

```bash
[cs50@flume ~]$ if [ -f students ]
> then
> mkdir backup && cp students backup/students || echo backup failed
> fi
[cs50@flume ~]$ 
```

More commonly, the `if` and `then` are written on the same line, using semicolon:

```bash
[cs50@flume ~]$ if [ -f students ] ; then
> mkdir backup && cp students backup/students || echo backup failed
> fi
[cs50@flume ~]$ 
```

Note, it's important that you leave spaces around the brackets or you will get syntax errors.
There are other options that can be used with the `[ ]` command.

```bash
   Option       Meaning
     -e         does the file exist?
     -d         does the directory exist?
     -f         does the file exist and is it an ordinary file (not a directory)?
     -r         does the file exist and is it readable?
     -s         does the file exist and have a size greater than 0 bytes
     -w         does the file exist and is it writeable?
     -x         does the file exist and is it executable?
```

To learn even more about the `test` command,  `man test`.


## Loops for lists

Many commands accept a list of files on the command line and perform actions on each file in turn.
However, what if we need to perform a sequence of commands on each file in the list of files?
Some commands can only handle one file (or argument) per invocation so we need to invoke the command many times.

The shell supports a simple iteration over lists of values - typically over lists of filenames.
In the following example, we make a 'back up' copy of each of our C files by appending the `.bak` extension.
(Again, this extension is just a naming convention - Unix doesn't care, nor does the shell.)

```bash
[cs50@flume ~/example]$ ls
hash.c	hash.c.date  makefile  output.data  queue.c  README  sort.c
[cs50@flume ~/example]$ for i in *.c
> do
> echo back up $i
> cp $i $i.bak
> done
back up hash.c
back up queue.c
back up sort.c
[cs50@flume ~/example]$ ls
hash.c	    hash.c.date  output.data  queue.c.bak  sort.c
hash.c.bak  makefile	 queue.c      README	   sort.c.bak
[cs50@flume ~/example]$ 
```

Notice that the variable `i` is instantiated, one at a time, with the value of each argument in the list provided after `in`, and that value is substituted wherever `$i` occurs.

We should be more defensive, though, in case one of the filenames has a space inside it;

```bash
[cs50@flume ~/example]$ for i in *.c
> do
> echo back up "$i"
> cp "$i" "$i.bak"
> done
back up hash.c
back up queue.c
back up sort.c
[cs50@flume ~/example]$ 
```

As expected we may place as many commands as we want inside the body of a loop.
We can use any combination of other if/else tests and nested loops, just like in traditional languages such as C.

We are not limited to use names of files (as generated by filename expansion) in our list:

```bash
[cs50@flume ~]$ for house in Allen "East Wheelock" "North Park" School South West LLC
> do
> echo $house is the best house!
> done
Allen is the best house!
East Wheelock is the best house!
North Park is the best house!
School is the best house!
South is the best house!
West is the best house!
LLC is the best house!
[cs50@flume ~]$ 
```

We can use the *contents of a file* to provide the list used by `for`:

```bash
[cs50@flume ~]$ cat LFlist
John.P.Kotz.19@dartmouth.edu
joel.j.katticaran.ug@dartmouth.edu
Kaya.M.Thomas.17@dartmouth.edu
trevor.l.davis.18@dartmouth.edu
Thomas.D.Kim.19@dartmouth.edu
kyle.dotterrer.18@dartmouth.edu
[cs50@flume ~]$ for i in $(<LFlist) ; do echo hello "$i" ; done
hello John.P.Kotz.19@dartmouth.edu
hello joel.j.katticaran.ug@dartmouth.edu
hello Kaya.M.Thomas.17@dartmouth.edu
hello trevor.l.davis.18@dartmouth.edu
hello Thomas.D.Kim.19@dartmouth.edu
hello kyle.dotterrer.18@dartmouth.edu
[cs50@flume ~]$ 
```

Notice the special shell syntax `$(<filename)`, which means to substitute the contents of `filename`.
Any spaces or newlines in the file will cause the shell to delineate *words* that become arguments to `for`.

The example also demonstrates how one can use semicolons to write a simple loop all on one line!

> In fact, if you type a multi-line `if` or `for` statement, then execute it, and later use up-arrow (or ctrl-P) to have the shell retrieve your earlier command, you'll see that it formats it this way.

We can even use the *output of a command* to provide the list used by `for`:

```bash
[cs50@flume ~]$ for i in $(sed 's/\..*/!/' LFlist | sort); do echo hello $i; done
hello John!
hello Kaya!
hello Thomas!
hello joel!
hello kyle!
hello trevor!
[cs50@flume ~]$ 
```

Indeed, in this case, we've used a pipeline of two commands to produce the list of arguments to `for`.

> You may see old scripts (or old people!) using the old-fashioned syntax in which the command is surrounded by back-quotes, ``` `command` ```, instead of `$(command)`; the latter is arguably more readable and, sometimes, nestable.


## First Shell Script

Up until now we have entered scripts interactively into the shell.
It is a pain to have to keep re-entering scripts interactively.
It is better to store the script commands in a text file and then execute the script when we need it.
So how do we do that?

Simple!  Write the commands in a file, and ask `bash` to read commands from the file instead of from the keyboard.

For example, we can put our simple backup script into a file called `backup.sh`:

```bash
[cs50@flume ~/example]$ cat > backup.sh
for i in *.c
do
  echo back up "$i"
  cp "$i" "$i.bak"
done
[cs50@flume ~/example]$ bash backup.sh
back up hash.c
back up queue.c
back up sort.c
[cs50@flume ~/example]$ 
```

Here I've typed it at the keyboard, but for more complex scripts, you would of course want to use a text editor.


Indeed, we can go further, and make the file into a command executable at the shell prompt; to do so, you should

1. add a special string `#!/bin/bash` to the first line,
2. make it executable (with `chmod`), and
3. either
 - add it to a directory on our `PATH`, or
 - type its pathname at the commandline.

So, for `backup.sh`, it looks like this:

```bash
[cs50@flume ~/example]$ emacs backup.sh
[cs50@flume ~/example]$ cat backup.sh
#!/bin/bash
for i in *.c
do
  echo back up "$i"
  cp "$i" "$i.bak"
done
[cs50@flume ~/example]$ chmod +x backup.sh
[cs50@flume ~/example]$ ls -l backup.sh
-rwxr-xr-x 1 cs50 cs50 72 Apr  3 15:28 backup.sh*
[cs50@flume ~/example]$ ./backup.sh
back up hash.c
back up queue.c
back up sort.c
[cs50@flume ~/example]$
```

There are a couple of things to note about this example.

First, there is the `#!/bin/bash` line.
What does this mean?
Typically, the `#` in the first column of a file denotes the start of a comment until the end of the line.
Indeed, in this case, this line is treated as a comment by `bash`.
*Unix, however, reads that line when you execute the file and uses it to determine which command should be fed this file;* thus, in effect, Unix will execute ```/bin/bash ./backup.sh```.
Then `bash` reads the file and interprets its commands.
The `#!/bin/bash` must be the first line of the file, exactly like that - no spaces.

Second, there is `chmod +x`,  which sets the 'execute' permission on the file.
(Notice the 'x' characters in the file permissions displayed by `ls`.)  Unix will not execute files that do not have 'execute' permission, and the shell won't even try.

Third, we used the pathname `./backup.sh` when treating our script as a command, because `.` is not on our `PATH`.
If `.` were on our `PATH`, we could have typed just `backup.sh`.

> It is very tempting to have `.` on your `PATH`, but it is a big security risk.
If you `cd` to a directory with an executable file called, say, `ls` and you don't notice, bad things might happen when you type the command `ls`.
If `.` is on your `PATH` before `/bin` you will run the local command `./ls` instead of the official `/bin/ls`... and the local `ls` may be malicious and do something bad!

Fourth, this script has no comments.
We really should improve it; see [backup.sh]({{site.examples}}/backup.sh).

```bash
#!/bin/bash
#
# backup.sh - make a backup copy of all the .c files in current directory
#
# usage: backup.sh
# (no arguments)
#
# input: none
# output: a line of confirmation for each file backed up
#
# David Kotz, April 2016

for i in *.c
do
  echo back up "$i"
  cp "$i" "$i.bak"
done

exit 0
```

It is good practice to identify the program, how its command-line should be used, and a description of what it does (if anything) with stdin and stdout.
And to list the author name(s) and date.

Notice the script returns the exit status `0`, which can be viewed using the `echo $?` command, as discussed earlier.
The return status is typically not checked when scripts are run from the command line.
However, when a script is called by another script the return status is typically checked - so it is important to return a meaningful exit status.

We could continue to improve this script - for example, to catch errors from `cp` and do something intelligent, but let's move on.

## Another shell script

If we go to all that trouble to save a backup copy of our `.c` files, it might be nice to see, later, what changed since we last made a backup.
Let's write a little script to compare the current versions with the backup copies.

See [backup-diff.sh]({{site.examples}}/backup-diff.sh)

```bash
#!/bin/bash
#
# backup-diff.sh - compare all the .c files in current directory with backup
#
# usage: backup-diff.sh
# (no arguments)
#
# input: none
# output: a line of information for each file, and diffs where they differ
# exit status: zero.
#
# David Kotz, March 2017

for i in *.c
do
    if [ ! -r "$i.bak" ]
    then
        echo "$i" - no backup 
    else
        if cmp --quiet "$i.bak" "$i" 
        then
            echo "$i" unchanged
        else
            echo "$i" differences:
            diff "$i.bak" "$i" 
        fi
    fi
    
    echo
done

exit 0
```

**[Classroom activity](activity.html):** modify this script to exit non-zero when missing backups or differences are found.


## Variables and arrays

Variables are typically not declared before they are used in scripts.

```bash
[cs50@flume ~]$ a=5
[cs50@flume ~]$ message="good morning"
[cs50@flume ~]$ echo $a
5
[cs50@flume ~]$ echo $message
good morning
[cs50@flume ~]$ 
[cs50@flume ~]$ echo ${message}
good morning
```

Above we create two variables (`a` and `message`).
The later commands show the `${varname}` syntax for variable substitution; this is the general form whereas `$varname` is a shorthand that works for simple cases; note that `${message}` is identical to `$message`.

## Repetition: the while Command

The 'for-loop' construct is good for looping through a series of strings but not that useful when you do not know how many times the loop needs to run.
The `while do` command is perfect for this.

The contents of [guessprime.sh]({{site.examples}}/guessprime.sh) use the 'while-do' construct.
The script allows the user to guess a prime between 1-100.

```bash
#!/bin/bash
#
# File: guessprime.sh
# 
# Description: The user tries to guess a prime between 1-100 
# This is not a good program. There is no check on what the
# user enters; it may not be a prime, or might be outside the range.
# Heck - it might not even be a number and might be empty!
# Some defensive programming would check the input.
# 
# Input: The user guess a prime and enters it
#
# Output: Status on the guess

# Program defines a variable called prime and set it to a value.

prime=31

echo -n "Enter a prime between 1-100: "
read guess

while [ $guess != $prime ]; do
    echo "Wrong! try again"
    echo -n "Enter a prime between 1-100: "
    read guess
done
exit 0
```

This script uses user defined variables `prime` and `guess`.
It introduces the `read` command, which pauses and waits for user input, placing that user input into the named variable.
The `-n` switch to `echo` removes the newline usually produced by echo.
Finally, note the semicolon after the `while` command and before the `do` command.
As with the `if` command and its `then` branch, we could have put `do` on the next line if we prefer that style.

```bash
[cs50@flume ~/public_html/examples]$ ./guessprime.sh 
Guess a prime between 1-100: 33
Wrong! try again
Guess a prime between 1-100: 2
Wrong! try again
Guess a prime between 1-100: 9
Wrong! try again
Guess a prime between 1-100: 31
[cs50@flume ~/public_html/examples]$ 
```

## The shell's variables

The shell maintains a number of important variables that are useful in writing scripts.
We have come across some of them already.

```
  Variable            Description
     $USER              username of current user
     $HOME              pathname for the home directory of current user
     $PATH              a list of directories to search for commands
     $#                 number of parameters passed to the script
     $0                 name of the shell script
     $1, $2, .. $#      arguments given to the script
     $*                 A list of all the parameters in a single variable.
     $@                 A list of all the parameters in a single variable; always delimited
     $$                 process ID of the shell script when running
```

The variable `$#` tells you how many arguments were on the command line; if there were three arguments, for example, they would be available as `$1`, `$2`, and `$3`.
In the command line `myscript.sh a b c`, then, `$#=3`, `$0=myscript.sh`, `$1=a`, `$2=b`, and `$3=c`.

The two variables `$*` and `$@` both provide the list of command-line arguments, but with subtle differences; try the following script, [args.sh]({{site.examples}}/args.sh), to see the difference.

```bash
#!/bin/bash

echo $# arguments to $0

# loop through all the arguments, in four different waysf
echo 'for arg in $*'
for arg in $*; do echo "$arg"; done

echo
echo 'for arg in "$*"'
for arg in "$*"; do echo "$arg"; done

echo
echo 'for arg in $@'
for arg in $@; do echo "$arg"; done

echo
echo 'for arg in "$@"'
for arg in "$@"; do echo "$arg"; done

exit 0
```

Let's try it on a command with four arguments; the fourth argument has an embedded space.

```bash
[cs50@flume ~/public_html/examples]$ ./args.sh one two three "and more"
4 arguments to ./args.sh
for arg in $*
one
two
three
and
more

for arg in "$*"
one two three and more

for arg in $@
one
two
three
and
more

for arg in "$@"
one
two
three
and more
[cs50@flume ~/public_html/examples]$ 
```

Study the difference of each case.
You should use `"$@"` to process command-line arguments, nearly always, because it retains the structure of those arguments.

As a shorthand, `for arg` is equivalent to `for arg in "$@"`.

> My choice of the variable name `arg` is immaterial to the shell.

## Printing error messages

You might need to inform the user of an error; in this example, the 2nd argument is supposed to be a directory and the script found that it is not:

```bash
echo 1>&2  Error: "$2" should be a directory
```

Here we see how to push the output of `echo`, normally to stdout (`1`), to the stderr (`2`) instead, by redirecting the stdout to the stderr using the confusing but useful redirect `1>&2`, which means 'make the stdout go to the same place as the stderr'.


## Checking arguments

When writing scripts it is important to write defensive code that checks whether the input arguments are correct.
Below, the program verifies that the command has exactly three arguments, using the 'not equal to' operator.

```bash
if [ $# -ne 3 ]; then
   echo 1>&2 Usage: incorrect argument input
   exit 1
fi
```

Notice also that the script then exits with a non-zero status.


## Finally

From this week's [reading assignments]({{site.baseurl}}/Reading/#week-2):

- Comments should clarify the code, not obscure it.
- They should enlighten, not impress.
- If you used a special algorithm or text, mention it and give a reference!
- Don't just add noise or chitchat.
- Say in comments what the code cannot.

Don't forget there are some good `bash` references on the [Resources]({{site.resources}}/#bash) page.

# Other stuff

There's never enough time to show you all the good stuff in class.

## Simple debugging tips

When you run a script you can use `printf` or `echo` to print debugging information to the screen.
I found it helpful to define a function `debugPrint` so I can turn on and off all my debug statements in one place:

```bash
# print the arguments for debugging; comment-out 'echo' line to turn it off.
function debugPrint() {
#    echo "$@"
    return
}
...
debugPrint starting to process arguments...
for arg; do
	debugPrint processing "$arg"
	...
```

If you get a syntax error; for example:

```bash
[cs50@flume ~]$ ./ziplab1.sh
making a tarball called cs50-lab1.tgz
./ziplab1.sh: line 18: syntax error near unexpected token `else'
./ziplab1.sh: line 18: `else'
[cs50@flume ~]$ 
```

The error is on or around line 18.
In `emacs` edit the file ./count.sh again and then go to line 18 using the sequence of key strokes `ESC g` -- that is, hit the `ESC` key and hit `g`.
(If you did not install the customized `~cs50/.emacs` file in your own `~/.emacs`, you may need to hit `g` twice.) Then, enter the line number 18 and you will be brought to that line.
Now fix the bug.
(In my particular example, the actual error was on line 13, not 18; on line 13 the `if` statement began, but I forgot the semicolon before `then`...
the shell finally realized a problem when it reached the `else` command at line 18.
So you may need to work backwards through the code, looking carefully to find the syntax problem.

Every time you launch `emacs` to edit a file, it saves a backup copy of that file.
For example, when you edit `foo.sh` and save it, `emacs` saves the pre-editing version in `foo.sh~`.
If you're later wondering what changed,

```bash
[cs50@flume ~]$ diff foo.sh~ foo.sh
```

will print the differences between the two files.

## Arrays

Like variables, arrays are typically not declared before they are used in scripts.

```bash
[cs50@flume ~]$ colors=(red orange yellow green blue indigo violet)
[cs50@flume ~]$ echo $colors
red
[cs50@flume ~]$ echo ${colors[1]}
orange
[cs50@flume ~]$ echo ${colors[6]}
violet
[cs50@flume ~]$ echo ${colors[7]}
[cs50@flume ~]$ 
```

Above we create one array (`colors`).
Notice that `$colors` implicitly substitutes the first element, with index 0 (computer scientists like counting from zero).
The later commands show the `${varname}` syntax for variable substitution; this is the general form whereas `$varname` is a shorthand that works for simple cases; note that `${message}` is identical to `$message` and `$colors` is equivalent to `${colors[0]}`.
When desiring to subscript an array variable, you must use the full syntax, as in `${colors[1]}`.
Finally, note that `${colors[7]}` is empty because it was not defined.

Even cooler, the array can be used in combination with file subsitution `$(<filename)` and command substitution `$(command)`:

```bash
[cs50@flume ~]$ cat LFlist
John.P.Kotz.19@dartmouth.edu
joel.j.katticaran.ug@dartmouth.edu
Kaya.M.Thomas.17@dartmouth.edu
trevor.l.davis.18@dartmouth.edu
Thomas.D.Kim.19@dartmouth.edu
kyle.dotterrer.18@dartmouth.edu
[cs50@flume ~]$ lfs=($(<LFlist))
[cs50@flume ~]$ echo ${lfs[3]}
trevor.l.davis.18@dartmouth.edu
[cs50@flume ~]$ 
[cs50@flume ~]$ juniors=($(grep .18. LFlist))
[cs50@flume ~]$ echo ${juniors[1]}
kyle.dotterrer.18@dartmouth.edu
[cs50@flume ~]$ echo ${lfs[*]}
John.P.Kotz.19@dartmouth.edu joel.j.katticaran.ug@dartmouth.edu Kaya.M.Thomas.17@dartmouth.edu trevor.l.davis.18@dartmouth.edu Thomas.D.Kim.19@dartmouth.edu kyle.dotterrer.18@dartmouth.edu
[cs50@flume ~]$ 

```

The last line demonstrates how you can substitute all values of the array, with the `[*]` index.

## `let` me do arithmetic!

The `let` command carries out arithmetic operations on variables.

```bash
$ let a=1

$ let b=2

$ let c = a + b
-bash: let: =: syntax error: operand expected (error token is "=")

# ... note, the let command is sensitive to spaces.

$ let c=a+b

$ echo $c
3

$ echo "a+b=$c"
a+b=3

$ echo "$a+$b=$c"
1+2=3

$ let a*=10  # equivalent to  let a=a*10
$ echo $a
10

```


## Temporary files

If your script needs to create some temporary files to do its work, it is good practice to create those files in a place *other than the current directory*, and with a filename that is unlikely to be used by another script - even another concurrently running copy of your script.

The directory `/tmp` is writable by everyone - so it's not a great place to put important files - and is the conventional place to put temporary files.
To avoid picking a name that others might pick, scripts include `$$`, their process identifier, as part of the filename.
For example, a script `print` might do the following:

```bash
#!/bin/bash
# build up an output file, then print it
# name of temporary file includes our process id $$
tmpfile=/tmp/print$$
echo > $tmpfile

for arg
do
	# print a nice header then the file
	echo "======================" >> $tmpfile
	echo "$arg" >> $tmpfile
	cat "$arg" >> $tmpfile
	echo >> $tmpfile
done

lpr $tmpfile		# print the result
rm -f $tmpfile	# clean up after ourself
exit 0
```

We use a variable `tmpfile` for clarity and consistency throughout the script.

## Catching interrupts, cleaning up

Many scripts create intermediate or temporary files, and might leave a mess if interrupted part-way through their operation.

The `trap` command can catch such interrupts, such as those caused by the user typing `ctrl-C` at the keyboard while the script works.
It is good form to catch this interrupt and clean up before exiting.
In the above example, we would extend the above example as follows:

```bash
# name of temporary file includes our process id $$
tmpfile=/tmp/print$$
trap "rm -f $tmpfile" EXIT
```

This `trap` command gives the shell a command to run whenever the script exits, for any reason (whether due to an `exit` command or due to an interrupt that kills the process).
Very handy!
Notice that I define the `trap` *immediately* after defining the variable name, so that it will be in effect whenever the temporary file is later created.
The `-f` flag ('force') to `rm` causes it to override some kinds of errors, notably, to not complain if the `$tmpfile` does not yet exist.

Sometimes you need a whole directory for your temporary use:

```bash
tmpdir=/tmp/print$$
trap "rm -rf $tmpdir" EXIT
mkdir -p $tmpdir
cd $tmpdir
```

Here I used `mkdir -p` to make the directory, and `rm -rf` to recursively remove it.



## Functions

Like most procedural languages, shell scripts have structure and function support.
Typically, it is a good idea to use functions to make scripts more readable and structured.
In what follows, we simply add a function to guessprime  to create [guessprimefunction.sh]({{site.examples}}/guessprimefunction.sh):

```bash
#!/bin/bash
#
# File: guessprimefunction.sh (variant of guessprime.sh)
# 
# Description: The user tries to guess a prime between 1-100 
# This is not a good program. There is no check on what the
# user enters; it may not be a prime, or might be outside the range.
# Heck - it might not even be a number and might be empty!
# Some defensive programming would check the input.
# 
# Input: The user guess a prime and enters it
#
# Output: Status on the guess

# Ask the user to guess, and fill global variable $guess with result.
# usage: askguess low high
#   where [low, high] is the range of numbers in which they should guess.
function askguess() {
    echo -n "Enter a prime between $1-$2: "
    read guess
}

# Program defines a variable called prime and set it to a value.

prime=31

# ask them once
askguess 1 100

while [ $guess != $prime ]; do
    # ask again
    askguess 1 100
done
exit 0
```

Notice that defining a function effectively adds a new command to the shell, in this case, `askguess`.
And that command can have arguments!
And those arguments are available within the function as if they were command-line arguments `$1`, `$2`, and so forth.
All other variables are treated as 'global' variables, like `guess` in this example.

Try this script; it's very fragile.
See what happens when you enter nothing - just hit return at the prompt for a guess.
Why does that happen?


## Another example: submitx

To submit your Lab solutions you use a command `~cs50/labs/submit`, which actually just runs a bash script `~cs50/labs/submitx`.
You can learn many things from this example; note the frequent checks for possible problems, the carefully quoted variable instantiations, the command chains with `&&` to ensure that a command sequence stops at the first error, and only reaches `exit 0` if they all succeed without error, and the use of `\` to break long lines into readable sequences.

```bash
#!/bin/bash
#
# Submit a homework assignment in CS50.
# The assignment must in in ~/cs50/labs/labN, where N is [1..9].
# The entire directory is copied to ~cs50/submit/labs/labN/username,
# where username is the $USER of the user that runs this script.
#
# usage: submit N [extension]
# where N is [1..9]
# where the optional second word is literally "extension" and is used
# to indicate that the student wants to claim an extension on this assignment.
# (In that case, all previously submitted files are deleted.)

usage="usage: $0 N [extension]    -- where N is [1..9]"

# Check arguments
if [[ $# -eq 0 || $# -gt 2 ]]
then
    echo "$usage"
    exit 1
fi

if [[ $# -eq 2 ]]
then if [[ "$2" == "extension" ]]
     then
	 extension=1
     else
	 echo "$usage"
	 exit 1
     fi
fi

let "N=$1"
if [[ $N -lt 1 || $N -gt 9 ]]
then
    echo "$usage"
    exit 2
fi

lab=lab$N

# destination of their files
dest=~cs50/labs/submissions/$lab/$USER

if [ $extension ]
then
   echo Requesting extension for $lab.
else
   echo Submitting $lab.

   # check their cs50 directory
   if [[ ! -d ~/cs50 ]]
   then
       echo 'oops! you are missing a ~/cs50 directory.'
       exit 3
   fi
   
   echo Ensuring that your CS50 directory is not visible by any other user...
   if chmod go-rwx ~/cs50
   then
       echo good.
   else
       echo 'Failed: unable to set permissions on your ~/cs50 directory.'
       echo They are:
       ls -ld ~/cs50
       exit 3
   fi

   # Prepare to copy from 'source' to 'dest'
   source=~/cs50/labs/$lab
   
   echo Checking source directory "$source"...
   if [[ ! -d "$source" ]]
   then
       echo "$source does not exist or is not a directory;"
       echo "did you put your lab in the right place?"
       exit 4
   fi
   
   if [[ ! -x "$source" || ! -r "$source" ]]
   then
       echo "$source is not searchable or not readable:"
       ls -ld "$source"
       exit 5
   else
       echo good.
   fi
fi
  
echo Checking destination directory "$dest"...
if  mkdir -p "$dest" && chmod o-rwx "$dest"
then
    echo good.
else
    echo cannot make directory "$dest"
    exit 6
fi

if [ $extension ]
then
   echo Removing previously submitted files, if any...
   rm -rf "$dest/"*
   echo Marking your submission as an extension...
   date > $dest/EXTENSION \
   && chgrp -R cs50 "$dest" \
   && chmod -R g=u "$dest" \
   && chmod g+rwx "$dest" \
   && chmod o-rwx "$dest" \
   && echo success! $lab extension requested. \
   && cat $dest/EXTENSION \
   && exit 0
else
    echo Copying new or changed files...
    rsync -aHv --delete "$source/" "$dest/" \
	&& chgrp -R cs50 "$dest" \
	&& chmod -R g=u "$dest" \
	&& chmod g+rwx "$dest" \
	&& chmod o-rwx "$dest" \
	&& echo success! $lab submitted \
	&& date \
	&& exit 0
fi

echo Failed!
exit 99

```
