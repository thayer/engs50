---
layout: page
title: Lab 2 - C and Bash
---

This second lab is focused on three small C programs, and a regression-testing bash script.
They start easy and get progressively more difficult.

* TOC
{:toc}

## Reminder

Grading will focus on [CS50 coding style]({{site.resources}}/CodingStyle.html) - including consistent formatting, selection of identifier names, and use of meaningful comments - in addition to correctness and testing.

***Your C code must compile without producing any compiler warnings.***  You will lose points if the compiler produces warnings when using our CS50-standard compiler flags.

***If your submitted code fails to compile, or triggers a segmentation fault,*** we'll notify you and give you an opportunity to repair and resubmit.
(See *[programs that crash]({{site.logistics}}/index.html#crashes).*)

## Preparation

Set up four directories for this lab:

```bash
$ cd
$ mkdir -p cs50/labs/lab2
$ cd cs50/labs/lab2
$ mkdir regress chill histo words
```

## Assignment

Please follow the [CS50 coding style]({{site.resources}}/CodingStyle.html).

Design, write, document, and **fully test** the following three separate C programs and one bash script.


***Point breakdown:***

  * (25 points) regress.sh
  * (25 points) chill.c
  * (25 points) words.c
  * (25 points) histo.c


## regress.sh

*Regression testing* is important to any quality software-development
process.  As a software project evolves, each new revision is tested
against a thorough suite of test cases to ensure that the new revision
still performs correctly where it had before.  As new functionality is
added, new tests are added to the suite.

Write a bash script `regress.sh` to perform regression testing.  Its
command line looks like

```
./regress.sh dirname testfilename...
```
* where `dirname` is the name of a directory containing test results, and
* where each `testfilename` is the name of a file containing bash command(s) for one test case.

The script verifies the validity of its arguments (exit with non-zero status on any error):

* there must be at least two arguments;
* if something by the name `dirname` exists, it must be a directory;
* each `testfilename` must be a regular file and be readable.

After checking its arguments, the script creates new directory whose name has the form YYYYMMDD.HHMMSS, representing the current date and time, in the current directory.
(For example, `20170402.143702`.) If any error, exit with non-zero status.

The script then runs each test case with bash, redirecting stdin from `/dev/null`, producing four files for each case:

* `YYYYMMDD.HHMMSS/testfilename.test` - a copy of `testfilename`
* `YYYYMMDD.HHMMSS/testfilename.status` - the exit status of `bash testfilename`
* `YYYYMMDD.HHMMSS/testfilename.stdout` - the stdout from `bash testfilename`
* `YYYYMMDD.HHMMSS/testfilename.stderr` - the stderr from `bash testfilename`


If the directory `dirname` *does not exist,* YYYYMMDD.HHMMSS is renamed `dirname`.
Exit 0 if success, non-zero if any error.

If the directory `dirname` *already exists,* YYYYMMDD.HHMMSS is compared with `dirname` to provide a brief listing of any differences - or the simple statement "no differences".
Exit 0 if no differences, non-zero if differences.

In typical usage, the first time the developer runs `regress.sh`, the script creates a directory by name `dirname`; in subsequent runs, it compares the new test results with those from the prior run.
Over time, directories YYYYMMDD.HHMMSS accumulate, providing a historical record of test results.

#### exit
{:.no_toc}

Non-zero if any error, or any differences from the earlier `dirname` directory.

Zero if `dirname` created successfully, or there were no differences from an existing `dirname`.

#### Example
{:.no_toc}

Suppose we used `regress.sh` to support development of the `shake.sh` solution.
The directory contains the script and four test files, each with a one-line command.
(Here `regress.sh` is elsewhere in the PATH.) We start out by listing the four test cases, then run `regress.sh` twice, then add a test case, then change a test case.
Finally, we test some erroneous cases.

```
[lab2]$ ls
shake.sh*	test0		test1		test2		test3
[lab2]$ cat test?
cat shake.sh
./shake.sh
./shake.sh love
./shake.sh computer
[lab2]$ regress.sh base test?
20170402.143657
saved test results in base
[lab2]$ regress.sh base test?
20170402.143702
comparing 20170402.143702 with base...
no differences.
[lab2]$ echo ./shake.sh two words > test4
[lab2]$ regress.sh base test?
20170402.143721
comparing 20170402.143721 with base...
Only in 20170402.143721: test4.status
Only in 20170402.143721: test4.stderr
Only in 20170402.143721: test4.stdout
Only in 20170402.143721: test4.test
[lab2]$ echo ./shake.sh rose > test2
[lab2]$ cat test?
cat shake.sh
./shake.sh
./shake.sh rose
./shake.sh computer
./shake.sh two words
[lab2]$ regress.sh base test?
20170402.143806
comparing 20170402.143806 with base...
Files base/test2.stdout and 20170402.143806/test2.stdout differ
Files base/test2.test and 20170402.143806/test2.test differ
Only in 20170402.143806: test4.status
Only in 20170402.143806: test4.stderr
Only in 20170402.143806: test4.stdout
Only in 20170402.143806: test4.test
[lab2]$ ls
20170402.143702/        shake.sh*               test3
20170402.143721/        test0                   test4
20170402.143806/        test1
base/                   test2
[lab2]$
######## now some error cases
[lab2]$ regress.sh
usage: regress.sh dirname testfilename...
[lab2]$ regress.sh base
usage: regress.sh dirname testfilename...
[lab2]$ regress.sh test?
first argument ('test0') is not a directory
[lab2]$ regress.sh /base test?
20170402.144605
mv: rename 20170402.144605 to /base: Permission denied
failed to save test results in /base; they remain in 20170402.144605
[lab2]$ regress.sh base testing
test case 'testing' is not a file (or not readable)
[lab2]$ regress.sh base base
test case 'base' is not a file (or not readable)
[lab2]$ chmod -r test?
[lab2]$ regress.sh base test?
test case 'test0' is not a file (or not readable)
[lab2]$
```

Note above how we use the bash globbing syntax `?` to indicate a wildcard that matches any single character; thus, `test?` expands to
```
test0 test1 test2 test3 test4
```

Note how `test0` simply prints the current copy of `shake.sh`, which adds nicely to the historic record.

>The name of test files is not important to `regress.sh`, but a development team may want to agree on a naming convention.
For example, suppose you chose to name them all with extension `.test`.
If you had saved the first run of `regress.sh` in a directory named `base`, you could then run future tests as
>
>```
./regress.sh base *.test
>```

Just to be clear, each testfile contains bash command(s), and your
`regress.sh` script should execute those commands by running bash and
providing `testfilename` as an argument.  (Recall how we did the test
cases for `shake.sh`.)  But you should run each test only *once*
within any given run of `regress.sh` – not only is that more
efficient, it's possible that the commands within some test files
might actually not be amenable to being run multiple times (e.g., if
they have side effects like creating or removing files).

It's easily possible to redirect the stdin, stdout, and stderr, all in
one run of a test - and to catch the exit status of that run.

#### Assumptions
{:.no_toc}

Please expect that dirname names a directory that could be anywhere -
not necessarily a subdirectory of the current working directory.
(This assumption should not complicate your work.)

Please assume that the testfilenames name files that *are* in the
current directory.  (In principle, we should support testfiles from
anywhere, but it's a bit trickier; this assumption simplifies your
work.  Your script need not validate the assumption - just assume it.)

Please *do not assume* that the script itself, regress.sh, is in the
current working directory.  (This assumption should not complicate
your work.)

#### Hints
{:.no_toc}

> Check out the `date` command and its `+` option.
>
> Check out the `diff --brief` command form.
>
> Check out the `shift` built-in bash command and this [example SHIFTING file]({{site.examples}}/shifter.sh).

## chill.c

Write a program to calculate "wind chill" based on the current
temperature and wind speed.  The standard formula for this calculation
is:

```Matlab
    Wind Chill = 35.74 + 0.6215T - 35.75(V^0.16) + 0.4275T(V^0.16)
```

where `T` is the temperature in degrees Fahrenheit (when less than 50)
and `V` is the wind velocity in miles per hour.  The `^` character
denotes exponentiation.  Note that the above formula is *not* in C
programming language syntax.

#### input
{:.no_toc}

No input files; stdin is ignored.

The user may run your program with no arguments, one argument, or two arguments as explained below.

#### output: no arguments
{:.no_toc}

If the user provides no arguments to your program, it should print out
a table of temperatures (from -10 to +40 by 10's) and and wind speeds
(from 5 to 15 by 5's).  Your output should look similar to the
following, with nice columns and titles:

```bash
    $ ./chill
    Temp    Wind    Chill
    ----    ----    -----
     -10       5    -22.3
     -10      10    -28.3
     -10      15    -32.2

       0       5    -10.5
       0      10    -15.9
       0      15    -19.4

      10       5     1.2
      10      10    -3.5
      10      15    -6.6

      20       5     13.0
      20      10     8.9
      20      15     6.2

      30       5     24.7
      30      10     21.2
      30      15     19.0

      40       5     36.5
      40      10     33.6
      40      15     31.8
```

#### output: one argument
{:.no_toc}

If the user provides one argument, it will assumed to be a temperature (expressed as a floating-point number).
If that temperature is less than 50, it is acceptable; `chill` then prints a table of wind speeds (from 5 to 15 by 5's) and the calculated wind chills *for that temperature only*.
Your program's output for one argument should look like this:

```bash
    $ ./chill 32
     Temp   Wind   Chill
    -----   ----   -----
      32      5     27.1
      32     10     23.7
      32     15     21.6
```

#### output: two arguments
{:.no_toc}

If the user provides two arguments, they will be temperature and
velocity, respectively (expressed as floating-point numbers).  The
temperature must be less than 50 and the velocity must be greater than
or equal to 0.5.

If the arguments are acceptable, then your program should calculate
and print the wind chill for *that temperature and velocity only*.

Your program's output for two arguments should look like this:

```bash
    $ ./chill 5 20
     Temp    Wind   Chill
     -----   ----   -----
        5     20    -15.4
```

If either argument is out of range, your program should issue a
message and exit.  Here's an example:

```bash
    $ ./chill 55
    Temperature must be less than 50 degrees Fahrenheit

    $ ./chill -150 
    Temperature must be greater than -139 Fahrenheit 
    (coldest recorded earth temperature, see https://en.wikipedia.org/wiki/Lowest_temperature_recorded_on_Earth)

    $ ./chill 10 0
    Wind velocity must be greater than or equal to 0.5 MPH
```

> In the preceding examples some values were printed as integers and some as decimal fractions.
You may print everything in the format "x.y", if you wish, but do not print more than one decimal place.
Indeed, it may be wise to use this format when the user specifies temperature or windspeed, because the user may specify a non-integral value and it may be misleading to print it as an integer.

#### output: more than two arguments
{:.no_toc}

print a "usage" line and exit with error status.

#### exit
{:.no_toc}

If the program terminates normally, it exits with a return code  of `0`.
Otherwise, it terminates with a documented, non-zero return code.

#### Compiling
{:.no_toc}

You will likely need the math library.
To use it, add
`#include <math.h>`
to your `chill.c` file, and add
`-lm` to your `mygcc` command.
(That is "dash ell emm", which is short for "library math".)

```bash
mygcc chill.c -lm -o chill
```

## words.c

Write a C program reminiscent of one of the pipelines we explored in Lab 1; specifically, a program called `words` that breaks its input into a series of words, one per line.
It may take input from stdin, or from files whose names are listed as arguments.

#### usage
{:.no_toc}
```
words [filename]...
```

#### input
{:.no_toc}

When no filenames are given on the command line, `words` reads from stdin.

When one or more filenames are given on the command line, `words` reads from each file in sequence.

If the special filename `-` is given as one of the filenames, the stdin is read at that point in the sequence.

#### output
{:.no_toc}

In any case, the stdout should consist of a sequence of lines, with
exactly one word on each output line (i.e., each output line contains
exactly one word and no other characters).  A "word" is a sequence of
letters.

> Although you may be tempted to think of the input as a sequence of lines, it may be helpful to think of it as a sequence of characters.

> Note it is possible for the output to be empty, if there are no words in any of the input files.

Any error messages are written to stderr.

#### exit
{:.no_toc}

If the program terminates normally, it exits with a return code  of `0`.
Otherwise, it terminates with a documented, non-zero return code.

#### hints
{:.no_toc}

> Check out `man ctype` on a mac, or `man ctype.h` on a Linux system.
>
> Consider a function that processes a file, given a `FILE*` as parameter.
> 
> Would it be easier to process the file(s) one character at a time?

## histo.c

Write a program that reads a series of positive integers from stdin, and prints out a histogram.
There should be 16 bins in your histogram.
The catch?
You don't know in advance the *range* of input values; assume the integers range from 0 to some unknown positive maximum.
Thus, you will need to dynamically scale the bin size for your histogram.
An example is below.

#### Usage:
{:.no_toc}

There are no command-line arguments.

#### Requirements:
{:.no_toc}

You must begin with bin size 1, and double it as needed so all
positive integers observed on input fit within the histogram.

You must have 16 bins.
The number '16' should appear only *once* in your code.

#### input:
{:.no_toc}

Input is read from stdin, whether from the keyboard, redirected from a
file, or piped in from another command.  You can use a simple
`scanf()` for this.  Assume the input contains only integers,
separated by white space (space, tab, newline).  Assume the smallest
integer is zero; ignore any negative integers.  If there is
non-integer non-space content in the file, it is ok for the program to
treat that as the end of input; the program should not crash, or enter
an infinite loop -- it should just silently behave as if there are no
more integers.  (These assumptions make it easy to use `scanf` for
your input.)

As always, any other assumptions you make should be documented in your `README` file and your testing procedure should be documented in your `TESTING` file.

#### output:
{:.no_toc}

See examples below.

#### exit
{:.no_toc}

This program has no arguments and does not check its input for errors, so it should always exit with zero status.

#### Examples:
{:.no_toc}

Here we compile and run the program, and type a set of numbers (spread
over three lines, but it doesn't matter as long as we put space or
newline between numbers), ending with `ctrl-D` on the beginning of a
line.  (That sends EOF to the program.)  It then printed a histogram,
nicely labeling each line with the range of values assigned to that
bin, and printing a row of `*` to represent the count of values that
fell into that bin.

```
$ mygcc histo.c -o histo
$ ./histo
16 bins of size 1 for range [0,16)
3 -4 5 1 7 0
8 0 15 12 3 5
3 3 3 3 3
^D
[ 0: 0] **
[ 1: 1] *
[ 2: 2]
[ 3: 3] *******
[ 4: 4]
[ 5: 5] **
[ 6: 6]
[ 7: 7] *
[ 8: 8] *
[ 9: 9]
[10:10]
[11:11]
[12:12] *
[13:13]
[14:14]
[15:15] *
$
```

The notation [a,b) includes all values *x* such that *a <= x < b*,
that is, the range includes *a* but does not include *b*.  For
example, [0,4) = {0, 1, 2, 3}.

Now watch what happens if we input a number outside the original range
of [0,16).

```
$ ./histo
16 bins of size 1 for range [0,16)
3 -4 5 1 7 0
8 0 15 12 3 5
18
16 bins of size 2 for range [0,32)
19 20 30 7 12
50
16 bins of size 4 for range [0,64)
34
32
19
44
^D
[ 0: 3] *****
[ 4: 7] ****
[ 8:11] *
[12:15] ***
[16:19] ***
[20:23] *
[24:27]
[28:31] *
[32:35] **
[36:39]
[40:43]
[44:47] *
[48:51] *
[52:55]
[56:59]
[60:63]
$
```

Each time it sees a number outside the current range, it doubles the
range and doubles the size of each bin.  (Notice also the [low:high]
labels in the histogram; this notation includes both *low* and *high*
and everything in between.) It might have to repeat the doubling if we
put in a number well past the current bin size:

```
$ ./histo
16 bins of size 1 for range [0,16)
150
16 bins of size 2 for range [0,32)
16 bins of size 4 for range [0,64)
16 bins of size 8 for range [0,128)
16 bins of size 16 for range [0,256)
^D
[  0: 15]
[ 16: 31]
[ 32: 47]
[ 48: 63]
[ 64: 79]
[ 80: 95]
[ 96:111]
[112:127]
[128:143]
[144:159] *
[160:175]
[176:191]
[192:207]
[208:223]
[224:239]
[240:255]
$
```

Here's an example using bash syntax to generate a list of numbers, and
piping the output to `histo`:

```
$ echo {1..16} 150 | ./histo
16 bins of size 1 for range [0,16)
16 bins of size 2 for range [0,32)
16 bins of size 4 for range [0,64)
16 bins of size 8 for range [0,128)
16 bins of size 16 for range [0,256)
[  0: 15] ***************
[ 16: 31] *
[ 32: 47]
[ 48: 63]
[ 64: 79]
[ 80: 95]
[ 96:111]
[112:127]
[128:143]
[144:159] *
[160:175]
[176:191]
[192:207]
[208:223]
[224:239]
[240:255]
$
```

Although we scale the bin size (x axis), I'm not asking you to scale
the bin count (y axis) for printing, which can lead to some really
wide output:

```
$ echo {1..100} 1500 | ./histo
16 bins of size 1 for range [0,16)
16 bins of size 2 for range [0,32)
16 bins of size 4 for range [0,64)
16 bins of size 8 for range [0,128)
16 bins of size 16 for range [0,256)
16 bins of size 32 for range [0,512)
16 bins of size 64 for range [0,1024)
16 bins of size 128 for range [0,2048)
[   0: 127] ****************************************************************************************************
[ 128: 255]
[ 256: 383]
[ 384: 511]
[ 512: 639]
[ 640: 767]
[ 768: 895]
[ 896:1023]
[1024:1151]
[1152:1279]
[1280:1407]
[1408:1535] *
[1536:1663]
[1664:1791]
[1792:1919]
[1920:2047]
$
```

We took some pains to format the [low:high] range indicators for each
row, using a fixed-width field just wide enough to hold the biggest
number.  It's a nice touch (read `man printf` for some clues) but it's
ok if you make a simpler assumption (e.g., always use 6-digit field
width).

#### Representing a histogram

You will need an array of 16 bins to represent the number of integers
observed in each bin.  You'll need to keep track of the bin size and
the range of the histogram.  If you observe a value outside the range,
you should double the bin size and range - but first you need to
compress the current 16 bins into the first 8 bins.  You'll likely
need one loop to compute the new values for the lower half of the bins
(each bin receiving the sum of two bins' counts), and then another to
assign the new value (0) to the upper half of the bins.

(Again: the number '16' may only occur *once* in your code; scattering
hard-coded numbers around your code is bad style.)

Notice that the number of bins, bin size, and histogram range are all
powers of 2.


## What to hand in, and how

Make sure to compile and test your solutions on one of the machines in
M210.  If you choose to develop your solutions on some other system,
you are responsible to ensure that the work you submit runs correctly
on a machine in M210 --- which is where where we will test it!

 *  In addition to your code, each of the four subdirectories of
    `lab2` must include two simple text files:

    a.  `README`,
         which describes how your program should be compiled and executed, along with an explanation of any assumptions you made about the assignment.
See the [example README file]({{site.examples}}/subtemplate-README.txt).

    b.  `TESTING`,
         which describes how you tested the program, including test inputs and test scripts; these test inputs and test scripts should be included as files in the same directory.

> See the [example TESTING file]({{site.examples}}/subtemplate-TESTING.txt); in that case we would not need to include testing inputs because they were CS50-provided files, or generated within the testing file itself.
(We created this file in MacOS Terminal by choosing "Export Text As..." from the Shell menu when we had finished all the testing commands, we edited it with emacs to add the comments.



When finished, you should have the following files:

```
lab2
├── chill
│   ├── README
│   ├── TESTING
│   └── chill.c
├── histo
│   ├── README
│   ├── TESTING
│   ├── histo.c
├── regress
│   ├── README
│   ├── TESTING
│   └── regress.sh
└── words
    ├── README
    ├── TESTING
    └── words.c
```

> This listing was produced by the `tree` command.  Neat, huh?

