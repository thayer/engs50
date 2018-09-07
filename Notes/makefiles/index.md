---
layout: page
title: Modules and Makefiles
---

### Goals

 * how to create a re-usable "module" by separating its code into a pair of `.c` and `.h` files.
 * the Make command and its Makefiles - never run `mygcc` again!

For a deeper dive into `make`, see the [lecture extra](extra/).

For a look at the C preprocessor, see another [lecture extra](preprocessor.html).

For more about C header files, see another [lecture extra](headerfiles.html).

<!--You can view today's Terminal [script](script.txt), although a lot of the action was in emacs and thus not shown. -->

## Extracting bag from names

Recall our [names9]({{site.examples}}/names9.c) program from the prior lecture, in which we converted the *linked list* data structure, specific to that particular application's needs, into a generic *bag* data structure.
Our next step is to extract that *bag* into a separate set of files, with a clearly defined interface, so it can be used by this program and easily re-used by other programs.
Given its design, it's also easy to create multiple bags, unlike the original design ([names5.c]({{site.examples}}/names5.c)) that was constrained to a single application-specific linked list.

Today we divide the code [names9]({{site.examples}}/names9.c) into three files:

* `namesA.c` - a new version of the application;
* `bag.h` - declarations that form the interface to he *bag* module
* `bag.c` - functions that define the implementation of the *bag* module.

Since we also use the `readlinep` module, we must now compile the program with a command like

```
mygcc names.c bag.c readlinep.c -o names
```

## Make and Makefiles

As our programs become more complex, it's increasingly tedious (and error-prone) to type the commands to compile the code into an executable.
Indeed, for a large codebase, it can take minutes or hours to compile all the code.
Fortunately, there is a good tool to make an executable from a collection of source files, incrementally recompiling only those files that have been updated.

The `make` command reads a configuration file called `Makefile` -- written in its own little language -- and executes shell commands as needed to compile all the source files and link them into an executable.
Before we look at a specific example, let's first take a closer look at the compilation process.

From now on we will compile all our programs with Make.

### Compiling and linking

The *compiler* reads "source code" (from a file like `bag.c` containing C code) and outputs "assembly code" (in a file `bag.s` containing assembly language).
Assembly language is still a human-readable text file, but now lists machine-level instructions instead of C statements.
In other words, the compiler translates source code into assembly code.
The Unix command for the C compiler is `cc`, though we use one from Gnu called `gcc`.

The *assembler* reads assembly code and outputs "object code", translating the textual machine instructions into binary machine instructions.
It's still not a complete program, not yet "executable" by the operating system.
The Unix command for the assembler is `as`.

The *linker* reads object code (from files like `names.o`, `bag.o`, and `readlinep.o`, and from libraries) and links them all together into an "executable" file, ready for the OS to run (execute) when we ask bash to run it.
It does not translate the code further -- both input and output in machine instructions in a binary format -- it "links" the pieces together, resolving references in one file to functions and variables in other files.
For example, `names.o` may reference a function `bag_new()`, which the linker finds in `bag.o`.
The linker assigns memory addresses for all the code and global variables, ready for loading into memory when the program is executed.
The Unix command for the linker is `ld` (short for "load", not to be confused with `ln`, which links files together).

> However, *[The linker is not a magical program](http://programmer.97things.oreilly.com/wiki/index.php/The_Linker_Is_not_a_Magical_Program)*.

The `gcc` command is actually pretty sophisticated, and in a form like

```
mygcc names.c bag.c readlinep.c -o names
```

will actually run four commands, something like this:

```
gcc -c names.c
gcc -c bag.c
gcc -c readlinep.c
ld names.o bag.o readlinep.o libraries... -o names
rm names.o bag.o readlinep.o
```

Each of the first three ask to "compile" (`-c`) the listed C source file; by default, the compiler creates an object-code file in a file of the same name with the extension `.o`.
(Under the hood, it's actually running both the compiler and then the assembler, briefly creating the intermediate `.s` file.)  The fourth line links those three object files together with a collection of common libraries, to produce the executable program; the original `-o names` commandline argument is placed here.
Finally, it cleans up by removing the intermediate object files.

Again, for a large code base, it is a waste of effort to recompile every C source file every time, even if only one of them has changed since the last compilation.

### Dependencies

To optimize this process it helps to know which files depend on each other.
Clearly, each object file depends on its source file:

```
names.o: names.c
bag.o: bag.c
readlinep.o: readlinep.c
```

and the program depends on all the object files that will linked together:

```
names: names.o bag.o readlinep.o
```

(It also depends on the standard libraries, but we assume they never change and we won't worry about them.)

Actually, if we look deeper, the object files also depend on the include files, because those files are virtually included in the C source files -- the compiler reads the include file `bag.h` when it sees `#include "bag.h"` at some point while reading the C source code.
Thus we also have dependencies

```
names.o: bag.h readlinep.h
bag.o: bag.h
readlinep.o: readlinep.h
```

(They also include `.h` files for standard libraries, but again, we assume those never change and thus we don't worry about them as dependencies.)

The above dependencies are actually written in `make` language.
The name to the left of each colon is the *target*, and the name(s) to the right of the colon are the *dependencies*.
The target depends on the dependencies, and should be rebuilt if any of the dependencies change.
Notice that dependencies are transitive: `names` depends on `bag.o` which depends on `bag.c` and `bag.h`, and so forth.
Make builds the *dependency tree* and rebuilds files as needed.

But how does it know how to rebuild one file from another?
We add a command (or list of commands), indented with a tab, on the line(s) that immediately follow the target.
We put all this together in a file called `Makefile`:

```make
# executable depends on object files
names: names.o bag.o readlinep.o
        gcc names.o bag.o readlinep.o -o names

# object files depend on source files
names.o: names.c
bag.o: bag.c
readlinep.o: readlinep.c

# object files also depend on include files
names.o: bag.h readlinep.h
bag.o: bag.h
readlinep.o: readlinep.h

# how to compile source into object files
names.o:
        gcc -c names.c
bag.o:
        gcc -c bag.c
readlinep.o:
        gcc -c readlinep.c
```

> Important: commands must be indented with a *tab* character, not spaces, or Make will not recognize them as commands.
Some editors are savvy and insert a tab when you type a tab, and some try to be clever and change the tab to spaces.
Make requires a tab.

Now, all we have to do is type `make`, and let it do all the work!

```bash
$ ls
Makefile	bag.h		names.txt	readlinep.h
bag.c		names.c		readlinep.c
$ make
gcc -c names.c
gcc -c bag.c
gcc -c readlinep.c
gcc names.o bag.o readlinep.o -o names
$ make
make: `names' is up to date.
$ touch bag.h
$ make
gcc -c names.c
gcc -c bag.c
gcc names.o bag.o readlinep.o -o names
$ ls
Makefile	bag.o		names.o		readlinep.h
bag.c		names*		names.txt	readlinep.o
bag.h		names.c		readlinep.c
$
```
Notice that, the first time I ran `make` it compiled each source file into an object file, and then compiled them all together.
(We use `gcc` to link object files, because it's very complicated to set up a proper `ld` commandline, and `gcc` is smart enough to realize it need only run the linker when it's only given object files.)

On my second run of `make`, it checked the dependency tree and decided there was nothing to be rebuilt.
Time saved!

I pretended to edit `bag.h` by "touching" it - the `touch` command just updates the modification date of the file(s) named on its command line, creating files if needed but making no changes to the content of existing files.

On my third run of `make`, it checked the dependency tree and saw that both `bag.o` and `names.o` depend on `bag.h`, so it recompiled both.
Because those two object files changed, it had to rebuild `names`.
In the end, notice that the `.o` files stick around - which is why `make` does not need to rebuild them every time.

Make actually knows about C and the relationship between `.c` and `.o` files, so several of the dependencies we listed were not necessary to list.
Indeed, some of the commands we listed are also unnecessary: they are *implicit rules* already known to make.
We thus streamline our `Makefile`:

```make
# executable depends on object files
names: names.o bag.o readlinep.o
	gcc names.o bag.o readlinep.o -o names

# object files also depend on include files
names.o: bag.h readlinep.h
bag.o: bag.h
readlinep.o: readlinep.h
```
Compare with the prior `Makefile` and you'll see two whole sections gone.
This new makefile works just the same:

```bash
$ ls
Makefile	bag.c		names.c		readlinep.c
Makefile~	bag.h		names.txt	readlinep.h
$ make
cc    -c -o names.o names.c
cc    -c -o bag.o bag.c
cc    -c -o readlinep.o readlinep.c
gcc names.o bag.o readlinep.o -o names
$ ls
Makefile	bag.h		names.c		readlinep.c
Makefile~	bag.o		names.o		readlinep.h
bag.c		names*		names.txt	readlinep.o
$
```

There are two important details, however.
First, you'll note that its implicit rules run `cc` instead of `gcc`.
Second, note that neither our explicit rules nor Make's implicit rules pass the CS50-standard command-line arguments to the C compiler.
We need to tell Make about those.
We can assign to some Make variables to inform Make about our preferred compiler and command-line options.
(Actually, Make calls them "macros" because their value cannot actually vary.)

```make
CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb

# executable depends on object files
names: names.o bag.o readlinep.o
	$(CC) $(CFLAGS) names.o bag.o readlinep.o -o names

# object files also depend on include files
names.o: bag.h readlinep.h
bag.o: bag.h
readlinep.o: readlinep.h
```

The first two lines assign values to the macros `CC` and `CFLAGS`.
These two particular macros are known to Make; it will use them in its implicit rules.
To use them in our explicit rules, too, we have to refer to them explicitly - see the commands to rebuild `names`.
Notice that the macro-substitution syntax in Make uses a dollar sign - like bash - but requires parentheses around the macro name - unlike bash.

```bash
$ make
gcc -Wall -pedantic -std=c11 -ggdb   -c -o names.o names.c
gcc -Wall -pedantic -std=c11 -ggdb   -c -o bag.o bag.c
gcc -Wall -pedantic -std=c11 -ggdb   -c -o readlinep.o readlinep.c
gcc -Wall -pedantic -std=c11 -ggdb names.o bag.o readlinep.o -o names
```
This time, Make used the `gcc` compiler and all our flags.

## Which target?

So far, we've just typed `make` at the command line.
We can actually tell Make to build a particular target by naming it:

```bash
$ make readlinep.o
gcc -Wall -pedantic -std=c11 -ggdb   -c -o readlinep.o readlinep.c
```

When given no target(s) on the command line, Make chooses the first target that has commands.
In our `Makefile`, that was `names` - which is why we put it first.
In a complex `Makefile`, it is common to place a target named `all` first, with a dependency (list) that indicates which target (list) is actually desired when one types `make all` or just `make`.

>  This is a *phony target*, because the result of `make all` is never to produce a file called `all`.
That's ok - its purpose is to direct Make toward the target(s) we want it to build.

## Cleaning up

We've taught Make how to build our program - now let's teach it how to clean up.
By convention, every good `Makefile` has a target called `clean`.
Let's extend the above `Makefile` (by convention, the `clean` rule goes at the bottom of the file):

```make
clean:
	rm -f names
	rm -f *~ *.o
	rm -rf *.dSYM
```
The `-f` flag ("force") asks `rm` to exit with success even if it fails - e.g., if there are no files by those names to be removed.
The `-r` flag ("recursive") removes a directory and its contents.
These commands remove the `names` executable, and the object files `*.o`, and the emacs backup files `~`, and the dSYM directory `gcc` creates in support of `gdb`.

Look how well it cleans up!

```bash
$ ls
Makefile	bag.h		names.c		readlinep.c
Makefile~	bag.o		names.o		readlinep.h
bag.c		names*		names.txt	readlinep.o
$ make clean
rm -f names
rm -f *~ *.o
rm -rf *.dSYM
$ ls
Makefile	bag.h		names.txt	readlinep.h
bag.c		names.c		readlinep.c
```

In some Makefiles, you'll see the author explicitly tell Make that this rule is "phony":

```make
.PHONY: clean
```

## More on macros

Any symbol that is defined in a Makefile like this

    NAME = VALUE

is called a macro.
Once defined, you can expand them using

    ... $(NAME) ...

It is also common to define macros for the name of the program being built, and the list of object files that go into it.
Below, our final `Makefile` declares `PROG` and `OBJS` for this purpose, and uses them in the build command.
I also included a list of library files needed by this program as `LIBS`; although `names` does not need the math library, it's harmless to ask `gcc` to link with the math library and it serves as a good example here.
(Certain libraries, like stdio and stdlib, are linked without you asking.)

```make
PROG = names
OBJS = names.o bag.o readlinep.o
LIBS = -lm

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)
```
Notice how we were able to rewrite the build rule to be fully generic - it names no specific files.
Indeed, you could use this rule in all your Makefiles!


## Complete Makefile

With the addition of the phony targets and a nice header comment, we're done:

```
# Makefile for the "names" program that uses the "bag" module.
#
# David Kotz - April 2017

CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb
PROG = names
OBJS = names.o bag.o readlinep.o
LIBS = -lm

.PHONY: all clean

all: names

# executable depends on object files
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)

# object files depend on include files
names.o: bag.h readlinep.h
bag.o: bag.h
readlinep.o: readlinep.h

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
```

The macro definitions at the top make it easy for a reader to quickly see what program will be built and from what files.
The gnarly compilation rule is the same for every Makefile!
Written once, and not likely needing to be changed.
The dependencies at bottom are the only other part that varies with the specific program.

I saved this Makefile as [names-Makefile]({{site.examples}}/names-Makefile) in our examples directory.

## Tips

Some other things to know about Make.

### Errors

If Make encounters an error while compiling, it stops and does not proceed with the rest of the build.
If, for example, a C compilation step fails and prints its error messages, Make notices this, prints a message, and exits with error status 1.
It will not proceed to compile other files, or build the overall program.
If you want to ask Make to proceed even after encountering errors, run `make -k`.

### Make command line

Make supports many command-line arguments.
See `man make`.

`-f file` use `file` instead of default `Makefile`

`-n` Determine which commands need to be run, but don't actually execute any of them, just print them.

`-k` while a particular target and the things that depend on it might have failed, continue trying to make the other dependencies of these targets anyway.
(My emacs command uses this flag.)

`-C dir` or `--directory=dir` tells Make to change its working directory (as if it internally runs `cd dir`) and then look for a Makefile (i.e., it will read from `dir/Makefile`).
This option is useful for running Make in a subdirectory.

### Automatic variables

The make utility also provides some useful [automatic variables](http://www.gnu.org/software/make/manual/make.html#Automatic-Variables):

`$@`   name of the current target

`$?`   the list of dependencies that are newer than the target

`$^`	the list of dependencies for this target

For example, we could rewrite our `names` target as follows

```make
names: names.o bag.o readlinep.o
	$(CC) $(CFLAGS) $^ -o $@
```

Although useful, I find the style we used in our complete example to be more readable.

### Documentation

You can view the [GNU documentation](http://www.gnu.org/software/make/manual/make.html), the manual pages for `make`, Steve Talbot's "oldie but goodie" book "*Managing projects with make*" [updated](http://shop.oreilly.com/product/9780596006105.do) in 2004 by Robert Mecklenburg for GNU `make`, or any of the variety of online tutorials for `make`.

### for emacs users

If you use emacs, and you installed our CS50 customation:

```bash
  cp ~cs50/.emacs ~
```

Whenever you start emacs, it loads this file.
This file defines a new keystroke `^X-c` (ctrl-X c), which tells emacs to run `make -k` in a separate subwindow.
If you get any compiler errors, type the keystroke ``^X-` `` (ctrl-X backquote) and emacs jumps to the right file and right line.
It's handy!

> If `cp` warns you about over-writing an existing `.emacs` you might want to reconsider - perhaps you've customized `emacs` before and you should edit your `~/.emacs` to include commands from `~cs50/.emacs` rather than simply overwriting it!
Best to `diff ~/cs50/.emacs ~/.emacs` to see what's different, rather than simply overwriting yours.


## Non-compilation makefiles

You can use makefiles to solve many of your daily challenges involving a sequences of dependent actions:

-   running test shell scripts during development and regression testing
-   creating documents with LaTeX
-   maintaining webpages (staging and live directories)
-   automated documentation generation
-   source code management

Here, for example, is the Makefile I use on my MacBook to compile and push the CS50 website to the webserver:

```make
# Makefile for deploying Jekyll site.
# David Kotz, Spring 2017, borrowing from Charles Palmer and Ira Jenkins

DEST    =  cs50@green.cs.dartmouth.edu:public_html
DESTURL =  http://www.cs.dartmouth.edu/~cs50/
LOCALURL = http://127.0.0.1:4000

# files *not* to push to the destination site
EXCLUDES = --exclude=/Makefile     \
	--exclude=/Comics/future   \
	--exclude=/Comics/unused   \
	--exclude=/examples/future \
	--exclude=/examples/unused \
	--exclude=/Labs/future     \
	--exclude=/Labs/unused     \
	--exclude=/Sections/future \
	--exclude=/Sections/unused \
	--exclude=/Reading/future  \
	--exclude=/Reading/unused  \
	--exclude=/Lectures/future \
	--exclude=/Lectures/unused \
	--exclude=\*-draft\*       \
	--exclude=\*~              \
	--exclude=\*.o             \
	--exclude=a.out            \
	--exclude=\*.dSYM          \
	--delete-excluded

.PHONY: build deploy local clean

# just for testing the build
build:
	@echo "\nBuilding..."
	cat _config-{base,cs} > _config.yml
	jekyll build

# build and push to CS server
deploy:
	cat _config-{base,cs} > _config.yml
	@echo "\nBuilding for CS..."
	jekyll build --destination _site
	-rm _config.yml

	@echo "\nFixing permissions..."
	chmod -R go-w _site/*
	chmod -R go+rX _site/*

	@echo "\nAdding data..."
	ln -s ../data _site/data

	@echo "\nDeploying..."
	rsync -e ssh -alcvz $(EXCLUDES) --delete  _site/ $(DEST)
	open $(DESTURL)

# build and open in a local server (jekyll serve runs jekyll build first)
local:
	@echo "\nBuilding for local viewing..."
	cat _config-{base,local} > _config.yml
	(sleep 5; open $(LOCALURL)) &
	jekyll serve --incremental
	-rm _config.yml

clean:
	jekyll clean
	-rm -f _config.yml
```


The leading `@` on some command lines tells `make` not to print that command out for the user to see - just to execute the command.
Here I use it for `echo` commands because, of course, those print their arguments for the user to see.

The leading `-` on some command lines tells `make` to ignore the exit status of that command - so even a non-zero exit status will allow `make` to continue and not exit with an error message.

## Activity

In today's [activity](activity.html) we extend the `Makefile` for `names` to add a phony *test* target.
