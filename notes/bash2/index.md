---
layout: page
title: More about Bash
---

Don't forget this week's [reading]({{site.baseurl}}/Reading/#week-1).

In this lecture, we continue our discussion of the Unix shell and its commands.

## Goals

We plan to learn the following today:

- Redirection and pipes
- Special characters and quoting
- Standard input, output, and error

We'll do this activity in today's class:

- Sit with your group, and get to know your group mates.
- Experiment with shell pipelines in this [Activity](activity.html).

### Class scripts

I recorded my Terminal windows from [flume](script-flume.txt) and [Mac](script-mac.txt).


## Redirection and pipes

To date we have seen Unix programs using default input and output -
called *standard input* (stdin) and *standard output* (stdout) - the
keyboard is the standard input and the display the standard output.
The Unix shell is able to redirect both the input and output of
programs.  As an example of output redirection consider the following.

```bash
[engs50@mc ~]$ date > listing
[engs50@mc ~]$ ls -lR public_html/ >> listing
```

The output redirection `>` writes the output of `date` to the file
called `listing`; that is, the 'standard output' of the `date` process
has been directed to the file instead of the default, the display.
Note that the `>` operation created a file that did not exist before
the output redirection command was executed.  Next, we append a
recursive, long-format directory listing to the same file; by using
the `>>` (double `>`) we tell the shell to *append* to the file rather
than overwriting the file.

Note that the `>` or `>>` and their target filenames are *not*
arguments to the command - the command simply writes to stdout, as it
always does, but the shell has arranged for stdout to be directed to a
file instead of the terminal.

The shell also supports input redirection.  This provides input to a
program (rather than the keyboard).  Let's create a file of prime
numbers using output redirection.  The input to the `cat` command can
come from the standard input (i.e., the keyboard).  We can instruct
the shell to redirect the `cat` command's output (stdout) to file
named `primes`.  The numbers are input at the keyboard and `CTRL-D` is
used to signal the end of the file (`EOF`).

```bash
[engs50@mc ~]$ cat > primes
61
53
41
2
3
11
13
18
37
5
19
23
29
31
47
53
59
[engs50@mc ~]$  
```

Input redirection `<` tells the shell to use a file as input to the command rather than the keyboard.
In the input redirection example below `primes` is used as input to `cat` which sends its standard output to the screen.

```bash
[engs50@mc ~]$ cat < primes
61
53
41
2
3
11
13
18
37
5
19
23
29
31
47
53
59
[engs50@mc ~]$ 
```

Many Unix commands (e.g., `cat`, `sort`) allow you to provide input from stdin if you do not specify a file on the command line.
For example, if you type `cat (CR)` (carriage return) then the command expects input from the standard input.

Unix also supports a powerful 'pipe' operator for passing data between commands using the operator `|` (a vertical bar, usually located above the `\` key on your keyboard).
Pipes connect commands that run as separate processes as data becomes available the processes are scheduled.

> Pipes were invented by Doug McIlroy while he was working with Ken Thompson and Dennis Ritchie at AT&T Bell Labs.
(As I mentioned earlier, Doug has been an adjunct professor here at Dartmouth College for several years now.)  In this [two-page interview]({{site.reading}}/DougMcIlroy.pdf), at the middle of the third column, Doug tells how pipes were invented and the `|` character selected as the operator.
Pay special attention to the next paragraph: the Dartmouth Time Sharing System had something similar, even earlier!

Pipes are a clever invention indeed, since the need for separate temporary files for sharing data between processes is not required.
Because commands are implemented as processes, a program reading an empty pipe will be ``suspended'' until there is data or information ready for it to read.
There is no limit to the number of programs or commands in the pipeline.
In our example below there are four programs in the pipeline all running simultaneously waiting on the input:

```bash
[engs50@mc ~]$ sort -n primes | uniq | grep -v 18 | more
2
3
5
11
13
19
23
29
31
37
41
47
53
59
61
[engs50@mc ~]$ 
```

What is the difference between pipes and redirection?
Basically, redirection (`>`,`>>`,`<`) is used to direct the stdout of command to a file, or from a file to the stdin of a command.
Pipes (`|`) are used to redirect the stdout to the stdin of another command.
This operator allows us to 'glue' together programs as 'filters' to process the plain text sent between them (*plain text* between the processes - a nice design decision).
This supports the notion of reuse and allows us to build sophisticated programs quickly and simply.
It's another cool feature of Unix.

Notice three new commands above: `sort`, `uniq`, and `grep`.

* `sort` reads lines from from stdin and outputs the lines in sorted order; here `-n` tells `sort to use numeric order (rather than alphabetical order);
* `uniq` removes duplicates, printing only one of a run of identical lines;
* `grep` prints lines matching a pattern (more generally, a *regular expression*); here, `-v` inverts this behavior: print lines that *do not* match the pattern.
In this case, the pattern is simply `18` and `grep` does not print that number as it comes through.

And, as we saw last time, `more` pauses the output when it would scroll off the screen.

Note that the original file - `primes` - is not changed by executing the command line above.
Rather, the file is read in by the `sort` command and the data is manipulated as it is processed by each stage of the command pipe line.
Because `sort` and `cat` are happy to read its input data from stdin, or from a file given as an argument, the following pipelines all achieve the same result:

```bash
[engs50@mc ~]$ sort -n < primes       | uniq | grep -v 18 | more
[engs50@mc ~]$ cat   primes | sort -n | uniq | grep -v 18 | more
[engs50@mc ~]$ cat < primes | sort -n | uniq | grep -v 18 | more
```

Which do you think would be most efficient?

**Another pipeline**: How did I create that list of existing usernames, for Lab0?

```bash
[engs50@mc ~]$ cut -d : -f 1 /etc/passwd | sort > usernames.txt
```

> See `man cut` to understand what the first command does.

**Another example**: what is the most popular shell?
Try each of these in turn:

```bash
[engs50@mc ~]$ cut -d : -f 7 /etc/passwd
[engs50@mc ~]$ cut -d : -f 7 /etc/passwd | less
[engs50@mc ~]$ cut -d : -f 7 /etc/passwd | sort
[engs50@mc ~]$ cut -d : -f 7 /etc/passwd | sort | uniq -c
[engs50@mc ~]$ cut -d : -f 7 /etc/passwd | sort | uniq -c | sort -n
[engs50@mc ~]$ cut -d : -f 7 /etc/passwd | sort | uniq -c | sort -nr
```

### MacOS tip:

There are three great commands you should know - they are not on Linux, because they interact with MacOS: `open`, `pbpaste`, `pbcopy`.

You've already seen the `open` command, which on MacOS at the Terminal command line, will open a file for viewing in the relevant MacOS application; for example, for a photo file you might type `open photo.jpg` and see Preview launch and open that file; for an html file you might type `open index.html` and see Safari launch and render that page.

The commands `pbpaste` and `pbcopy` are a great fit into many pipelines.
The first command prints the MacOS 'clipboard' to its standard output, and the second copies its standard input into the MacOS clipboard.
For example; select some text in a window somewhere, then *cmd-C* to copy it to the clipboard, then
```
	pbpaste | wc
```
to count the lines, words, and characters in the clipboard.
Or,
```
	ls -l | pbcopy
```
saves the directory listing in the clipboard, where you might paste it into Piazza or an email message or some document.

I'm not certain you can combine `pbpaste` and `pbcopy` on the same command line, however; if you wanted to *replace* the clipboard with its number of lines, you might try
```
	pbpaste | wc -l | pbcopy
```
but be careful mixing those two commands.

## Standard input, output and error

As we learned above, every process (a running program) has a *standard input* (abbreviated
to `stdin`) and a *standard output* (`stdout`). 
The shell sets `stdin` to the keyboard by default, but the command
line can tell the shell to redirect `stdin` using `<` or a pipe.  The
shell sets `stdout` to the display by default, but the command line
can tell the shell to redirect `stdout` using `>` or `>>`, or to a
pipe.

Each process also has a *standard error* (`stderr`), which most
programs use for printing error messages.  The separation of `stdout`
and `stderr` is important when `stdin` is redirected to a file or
pipe, because normal output can flow into the file or pipe while error
messages reach the user on the screen.

Inside the running process these three streams are represented with
numeric *file descriptors*:

1. `stdin`
2. `stdout`
3. `stderr`

You can tell the shell to redirect using these numbers; `>` is
shorthand for `1>` and `<` is shorthand for `0<`.  You can thus
redirect the standard error (file descriptor 2) with the symbol `2>`.
Suppose I was logged in as `dfk` and wanted to make a list of the web
files `index.html` anywhere in the `cs50` account's home directory
tree.

```bash
[engs50@mc ~]$ find ~cs50 -name index.html > pages
find: `/net/class/cs50/Archive/src': Permission denied
find: `/net/class/cs50/.emacs.d': Permission denied
find: `/net/class/cs50/private/': Permission denied
[engs50@mc ~]$ 
```

I redirected the output of `find` to a file called `pages` - and
indeed that file filled with useful information - but `find` printed
its error messages to the screen so I could still see them.  Suppose I
wanted to capture those errors in a file too:

```bash
[engs50@mc ~]$ find ~cs50 -name index.html > pages 2> errors
[engs50@mc ~]$ 
```
The file `errors` contains the error messages we saw earlier.

As another alternative, we could ignore the error output entirely by
sending it to a place where all characters go and never return!

```bash
[engs50@mc ~]$ find ~cs50 -name index.html > pages 2> /dev/null
[engs50@mc ~]$ 
```
The file called `/dev/null` is a special kind of file - it's not a file at all,
actually, it's a 'device' that simply discards anything written to it.
(If you read from it, it appears to be an empty file.)

## Special characters

There are a number of special characters interpreted by the shell -
spaces, tabs, wildcard ('globbing') characters for filename expansion,
redirection symbols, and so forth.  Special characters have special
meaning and cannot be used as regular characters because the shell
interprets them in a special manner.  These special characters
include:

``& ; | * ?  ` " ' [ ] ( ) $ < > { } # / \ ! ~ ``

We have already used several of these special characters.
Don't try to memorize them at this stage.
Through use, they will become second nature.
We will just give some examples of the ones we have not discussed so far.


## Quoting

If you need to use one of these special characters as a regular
character, you can tell the shell not to interpret it by escaping or
quoting it.  To *escape* a single special character, precede it with a
backslash `\`; earlier we saw how to escape the character `*` with
`\*`.  To escape multiple special characters (as in `**`), quote each:
`\*\*`.  You can also *quote* using single quotation marks such as
`'**'` or double quotation marks such as `"**"` - but these have
subtlety different behavior.  You might use this form when quoting a
filename with embedded spaces: `"Homework assignment"`.

You will often need to pass special characters as part of arguments to
commands and other programs - for example, an argument that represents
a pattern to be interpreted by the command; as happens often with
`find` and `grep`.

There is a situation where single quotes work differently than double
quotes.  If you use a pair of single quotes around a shell variable
substitution (like `$USER`), the variable's value will not be
substituted, whereas it would be substituted within double quotes:

```bash
[engs50@mc ~]$ echo "$LOGNAME uses the $SHELL shell and his home directory is $HOME."
cs50 uses the /bin/bash shell and his home directory is /net/class/cs50.
[engs50@mc ~]$ echo '$LOGNAME uses the $SHELL shell and his home directory is $HOME.'
$LOGNAME uses the $SHELL shell and his home directory is $HOME.
[engs50@mc ~]$ 
```

***Example 1.***
Double-quotes are especially important in shell scripts, because the
variables involved might have been user input (a command-line argument
or a keyboard input) or might have be a file name or output of a
command; such variables should *always* be quoted when substituted,
because spaces (and other special characters) embedded in the value of
the variable can cause confusion.  Thus:

```bash
directoryName="Homework three"
...
mkdir "$directoryName"
mkdir $directoryName
```

Try it!

***Example 2.***
Escapes and quoting can pass special characters and patterns passed to
commands.

Suppose I have a list of email addresses, one per line.

```
 Eric Chen <eric.t.chen.17@dartmouth.edu>
 Rui Liu <Rui.Liu.GR@dartmouth.edu>
 Taylor Hardin <Taylor.A.Hardin.GR@dartmouth.edu>
 Elena N. Horton <Elena.N.Horton.18@dartmouth.edu>
 Jinnan Ge <Jinnan.Ge.TH@dartmouth.edu>
 Mauricio Esquivel Rogel <Mauricio.Esquivel.Rogel.18@dartmouth.edu>
 James Edwards <James.G.Edwards.18@dartmouth.edu>
 Emily J. Lin <Emily.J.Lin.18@dartmouth.edu>
 John Cardwell <John.R.Cardwell.18@dartmouth.edu>
 John Kotz <John.P.Kotz.19@dartmouth.edu>
 Joel J. Katticaran <joel.j.katticaran.ug@dartmouth.edu>
 Kaya M. Thomas <Kaya.M.Thomas.17@dartmouth.edu>
 Trevor L. Davis <trevor.l.davis.18@dartmouth.edu>
 Thomas D. Kim <Thomas.D.Kim.19@dartmouth.edu>
 Kyle Dotterrer <kyle.dotterrer.18@dartmouth.edu>
```

Some email programs, or websites, require these to be comma-separated.
If I have the above text in my clipboard, I can change those newline characters to commas:

```bash
$ pbpaste | tr \\n ,
Eric Chen <eric.t.chen.17@dartmouth.edu>, Rui Liu <Rui.Liu.GR@dartmouth.edu>, Taylor Hardin <Taylor.A.Hardin.GR@dartmouth.edu>, Elena N. Horton <Elena.N.Horton.18@dartmouth.edu>, Jinnan Ge <Jinnan.Ge.TH@dartmouth.edu>, Mauricio Esquivel Rogel <Mauricio.Esquivel.Rogel.18@dartmouth.edu>, James Edwards <James.G.Edwards.18@dartmouth.edu>, Emily J. Lin <Emily.J.Lin.18@dartmouth.edu>, John Cardwell <John.R.Cardwell.18@dartmouth.edu>, John Kotz <John.P.Kotz.19@dartmouth.edu>, Joel J. Katticaran <joel.j.katticaran.ug@dartmouth.edu>, Kaya M. Thomas <Kaya.M.Thomas.17@dartmouth.edu>, Trevor L. Davis <trevor.l.davis.18@dartmouth.edu>, Thomas D. Kim <Thomas.D.Kim.19@dartmouth.edu>, Kyle Dotterrer <kyle.dotterrer.18@dartmouth.edu> 
```

> On Unix a single special character called 'newline' is what *defines* the end of one line and the beginning of the next.
A common syntax for the newline character, in programming languages,
is `\n`.  But the `\` is special, in bash, so we need to escape it,
um, with `\`; thus we have `\\n`.

The `tr` command filters `stdin` to `stdout`, translates each instance
of the character given in the first argument (`\\n`) to the character
given in the second argument (`,`).  Here, `tr` spit out the
translated input - on one very long line that does not end with a
newline.  I can then copy-paste that result into the pesky web
browser.

Outlook and Microsoft tools want *semicolons*, not commas; sigh.
But the semicolon is also special to bash; so we must escape it too:

```bash
$ tr \\n \;
```

On MacOS I can connect the MacOS "Clipboard" to this tool as follows:

```bash
$ pbpaste | tr \\n \; | pbcopy
```
great!
copy the list of addresses to the clipboard, type that command in the shell, and now the clipboard contains a semicolon-separated list of addresses.


***Example 3.***
An even more powerful filtering tool - the stream editor called
`sed` - allows you to transform occurrences of one or more patterns in
the input file(s):

```bash
	sed pattern [file]...  
```

For example,

```bash
[engs50@mc ~]$ cat .forward
 David Kotz <kotz@cs>
 Eric Chen <eric.t.chen.17@dartmouth.edu>
 Rui Liu <Rui.Liu.GR@dartmouth.edu>
 Taylor Hardin <Taylor.A.Hardin.GR@dartmouth.edu>
 Elena N. Horton <Elena.N.Horton.18@dartmouth.edu>
 Jinnan Ge <Jinnan.Ge.TH@dartmouth.edu>
 Mauricio Esquivel Rogel <Mauricio.Esquivel.Rogel.18@dartmouth.edu>
 James Edwards <James.G.Edwards.18@dartmouth.edu>
 Emily J. Lin <Emily.J.Lin.18@dartmouth.edu>
 John Cardwell <John.R.Cardwell.18@dartmouth.edu>
 John Kotz <John.P.Kotz.19@dartmouth.edu>
 Joel J. Katticaran <joel.j.katticaran.ug@dartmouth.edu>
 Kaya M. Thomas <Kaya.M.Thomas.17@dartmouth.edu>
 Trevor L. Davis <trevor.l.davis.18@dartmouth.edu>
 Thomas D. Kim <Thomas.D.Kim.19@dartmouth.edu>
 Kyle Dotterrer <kyle.dotterrer.18@dartmouth.edu>
[engs50@mc ~]$ # remove myself, and excess white space
[engs50@mc ~]$ sed -e /kotz@cs/d -e 's/\t/ /g' -e 's/  */ /g'  .forward
 Eric Chen <eric.t.chen.17@dartmouth.edu>
 Rui Liu <Rui.Liu.GR@dartmouth.edu>
 Taylor Hardin <Taylor.A.Hardin.GR@dartmouth.edu>
 Elena Horton <Elena.N.Horton.18@dartmouth.edu>
 Jinnan Ge <Jinnan.Ge.TH@dartmouth.edu>
 Mauricio Esquivel Rogel <Mauricio.Esquivel.Rogel.18@dartmouth.edu>
 James Edwards <James.G.Edwards.18@dartmouth.edu>
 Emily Lin <Emily.J.Lin.18@dartmouth.edu>
 John Cardwell <John.R.Cardwell.18@dartmouth.edu>
 John Kotz <John.P.Kotz.19@dartmouth.edu>
 Joel Katticaran <joel.j.katticaran.ug@dartmouth.edu>
 Kaya Thomas <Kaya.M.Thomas.17@dartmouth.edu>
 Trevor Davis <trevor.l.davis.18@dartmouth.edu>
 Thomas Kim <Thomas.D.Kim.19@dartmouth.edu>
 Kyle Dotterrer <kyle.dotterrer.18@dartmouth.edu>
[engs50@mc ~]$ # remove myself, remove names, make comma-sep list of addresses
[engs50@mc ~]$ sed -e /kotz@cs/d -e 's/.*<//' -e 's/>.*/,/'  .forward
eric.t.chen.17@dartmouth.edu,
Rui.Liu.GR@dartmouth.edu,
Taylor.A.Hardin.GR@dartmouth.edu,
Elena.N.Horton.18@dartmouth.edu,
Jinnan.Ge.TH@dartmouth.edu,
Mauricio.Esquivel.Rogel.18@dartmouth.edu,
James.G.Edwards.18@dartmouth.edu,
Emily.J.Lin.18@dartmouth.edu,
John.R.Cardwell.18@dartmouth.edu,
John.P.Kotz.19@dartmouth.edu,
joel.j.katticaran.ug@dartmouth.edu,
Kaya.M.Thomas.17@dartmouth.edu,
trevor.l.davis.18@dartmouth.edu,
Thomas.D.Kim.19@dartmouth.edu,
kyle.dotterrer.18@dartmouth.edu,
[engs50@mc ~]$ 
```

The above uses the `-e` switch to `sed`, which allows one to list more than one pattern on the same command.

A few quick notes about sed's patterns:

 * `d` deletes lines matching the pattern
 * `p` prints lines matching the pattern (useful with `-n`)
 * `s` substitutes text for matches to the pattern.

Patterns are actually [regular expressions](http://sed.sourceforge.net/sedfaq3.html#s3.1.1); I use some above.

***Example 4.***

I saved a list of students enrolled in CS50 in the file `~cs50/demo/students.txt`.
Each line is of the form `First.M.Last.18@Dartmouth.edu;`.

Let's suppose you all decide to move to Harvard.

```bash
[engs50@mc ~]$ sed s/Dartmouth/Harvard/ demo/students.txt
...
[engs50@mc ~]$ sed -e s/Dartmouth/Harvard/ -e 's/\.[0-9][0-9]//' -e 's/;$//' demo/students.txt
...
```

The second form removes the dot and two-digit class number, and the
trailing semicolon.  Notice how I quoted those patterns from the
shell, and even escaped the dot from sed's normal meaning (dot matches
any character) so sed would look for a literal dot in that position.
The dollar `$` constrains the semicolon match to happen at the end of
the line.

Here's another fun pipe: count the number of students from each class
(leveraging the class numbers in email addresses):

```bash
[engs50@mc ~]$ tr -c -d 0-9\\n < demo/students.txt | sed 's/^$/other/'  | sort  | uniq -c | sort -nr
     27 18
     22 19
      9 17
      5 other
      1 16
[engs50@mc ~]$ 
```

See `man sed` or the [sed FAQ](http://sed.sourceforge.net/sedfaq.html) for more info.
You'll want to learn a bit about *regular expressions*, which are used to describe patterns in sed's commands; 
see [sed regexp info](http://sed.sourceforge.net/sedfaq3.html#s3.1.1).


## Compressing and archiving files

It is often useful to bundle several files into a compressed *archive* file.
You may have encountered files like this on the Internet - such as `files.zip`, `something.tar`, or `somethin-else.tgz`.
Each packs together several files - including directories, creation dates, access permissions, as well as file contents - into one single file.
This is a convenient way to transfer large collections of files.

On Unix it is most common to use the `tar` utility (short for tape archive - from back when we used tapes) to create an archive of all the files and directories listed in the arguments and name it to something appropriate.
We often ask `tar` to compress the resulting archive  too.

Given a directory `stuff`, you can create (`c`) a compressed tar archive (aka, a "tarball"), and then list (`t`) its contents.
The `f` refers to a file and the `z` refers to compression.

```bash
[engs50@mc ~]$ mkdir stuff
[engs50@mc ~]$ echo > stuff/x
[engs50@mc ~]$ tar cfz stuff.tgz stuff
 98.8%
[engs50@mc ~]$ tar tfz stuff.tgz
stuff/
stuff/x
[engs50@mc ~]$ 
```

The command leaves the original directory and files intact.
Notice that `tar` has an unconventional syntax for its switches - there is no dash `-` before them.

To unpack the archive,

```bash
[engs50@mc ~]$ tar xfz stuff.tgz
```

In short, `c` for create, `t` for type (list), `x` for extract.
The `f` implies that the next argument is the tarball file name.
The `z` indicates that the tarball should be compressed.
By convention, a tarball filename ends in `.tar` if not compressed, `.tgz` if compressed.
