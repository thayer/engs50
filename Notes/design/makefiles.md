---
layout: page
title: More about Makefiles
---

### Goals

* Another look at Makefiles
* Producing and using library archives

For a deeper dive into `make`, recall the [lecture extra]({{site.lectures}}/makefiles/extra/).

<!-- See today's terminal [script](script.txt). -->

## Makefiles

Recall the Makefile we wrote in [Lecture]({{site.lectures}}/makefiles/) -- available as [names-Makefile]({{site.examples}}/names-Makefile) in our examples directory.

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

Let's modify the Makefile to leverage our new `libcs50` library from the [Lab4 starter kit](https://gitlab.cs.dartmouth.edu/CS50/tse).

I adapted the `names9.c` for use with a library-provided *bag*, resulting in file `names.c` one directory, and dropped in the `libcs50` directory as a peer.
(This program is now available as [namesB.c]({{site.examples}}/namesB.c).

```
[cs50@flume ~/demo]$ tree lecture libcs50/
lecture
├── Makefile
└── names.c
libcs50/
├── bag.c
├── bag.h
├── counters.c
├── counters.h
├── file.c
├── file.h
├── file.md
├── hashtable.c
├── hashtable.h
├── jhash.c
├── jhash.h
├── Makefile
├── memory.c
├── memory.h
├── memory.md
├── README.md
├── set.c
├── set.h
├── webpage.c
├── webpage_fetch.c
├── webpage.h
├── webpage_internal.h
└── webpage.md
```

The new Makefile for *names* follows.
Notice several important features:

* definition of macro `L` as a shorthand for the directory name (not the library name) where the library lives.
Make allows us to substitute the value of single-letter macro names without using parens; thus, I can use `$L` to substitute this directory name.

* addition of `-I$L` to the `CFLAGS`, which tells the compiler to look for `include` files in the directory `$L`

* the existing `LIBS` macro, meaning "libraries", used to tell the linker to link with the *math library*; `-lm`

* the new `LLIBS` macro, by which I mean "local libraries", used to tell the linker to link with the libcs50 library; I keep this separate from `LIBS` because I want to inform Make that the program depends on this library in _my_ directories.

* the default `all` rule, just to be clear

* the updated `$(PROG)` general rule, which indicates dependence on `$(LLIBS)` and also provides them to the linker command (the next line).

* the `names.o` rule, which uses `$L` to refer to the include files needed by this program.

* the lack of any rule to build the library `libcs50.a`; it is not the job of this Makefile to build that library.

```make
# Makefile for the "names" program that uses the "bag" module.
#
# David Kotz - April 2017

L = ../libcs50

CC=gcc
CFLAGS=-Wall -pedantic -std=c11 -ggdb -I$L
PROG = names
OBJS = names.o
LIBS = -lm
LLIBS = $L/libcs50.a

.PHONY: all clean

all: $(PROG)

# executable depends on object files
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LLIBS) $(LIBS) -o $(PROG)

# object files depend on include files
names.o: $L/bag.h $L/file.h

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
```

## Producing library archives

What is a "library" file and how do you make one?

A *library file* is simply an *archive of object files.*
An *archive* is a single file that contains a collection of other files; you've probably downloaded `.zip`, `.tgz`, or `.dmg` files before; those are various forms of archive.
Inside those files is some metadata describing the enclosed files, as well as the (often compressed) data of the original files.

In Unix, there is a specific type of archive used for coalescing object `.o` files into a single `.a` file, for convenience.
The linker `ld` knows how to read `.a` files.
It links in any `.o` files that contain symbols that are as-yet unresolved when it reaches that point in its argument list of files; when it pulls in a `.o` file it pulls in that whole `.o` file.
That file may, in turn, reference other symbols - if those are in another `.o` file in the same archive, the linker loads them too.
Any symbols still unresolved after the current `.a` file is exhausted better be in another `.o` or `.a` file later in the argument list.
*Thus, the order of arguments to the linker is important.*

Anyway, a peek inside `libcs50/Makefile` shows how to build an archive:

```make
# object files, and the target library
OBJS = bag.o counters.o file.o hashtable.o jhash.o memory.o \
       set.o webpage.o webpage_fetch.o
LIB = libcs50.a
...
# Build the library by archiving object files
$(LIB): $(OBJS)
        ar cr $(LIB) $(OBJS)

```

The `ar` command manipulates an archive `.a` file; specifically, `ar cr` creates the `.a` file (if needed) and replaces the enclosed `.o` files with those on its command line.
Thus, `libcs50.a` holds all those `.o` files, which we can show with `ar t`:

```
[cs50@flume ~/demo/libcs50]$ ar t libcs50.a
bag.o
counters.o
file.o
hashtable.o
jhash.o
memory.o
set.o
webpage.o
webpage_fetch.o
[cs50@flume ~/demo/libcs50]$
```

## Building it all

To build the whole program, we need to build the library and then the program.
We could do so, from the directory above, with two calls to Make:

```bash
[cs50@flume ~/demo]$ make -C libcs50
make: Entering directory '/net/class/cs50/demo/libcs50'
gcc -Wall -pedantic -std=c11 -ggdb    -c -o bag.o bag.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o counters.o counters.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o file.o file.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o hashtable.o hashtable.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o jhash.o jhash.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o memory.o memory.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o set.o set.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o webpage.o webpage.c
gcc -Wall -pedantic -std=c11 -ggdb    -c -o webpage_fetch.o webpage_fetch.c
ar cr libcs50.a bag.o counters.o file.o hashtable.o jhash.o memory.o set.o webpage.o webpage_fetch.o
make: Leaving directory '/net/class/cs50/demo/libcs50'
[cs50@flume ~/demo]$ make -C lecture
make: Entering directory '/net/class/cs50/demo/lecture'
gcc -Wall -pedantic -std=c11 -ggdb -I../libcs50   -c -o names.o names.c
gcc -Wall -pedantic -std=c11 -ggdb -I../libcs50 names.o  ../libcs50/libcs50.a -lm -o names
make: Leaving directory '/net/class/cs50/demo/lecture'
[cs50@flume ~/demo]$ 
```

Notice that *all but one* of the `gcc` commands are executed by Make's implicit rule for producing a `.o` file from a `.c` file; the final `gcc` command is actually running the linker and not the C compiler; its arguments include `names.o`, `libcs50.a` and the math library `-lm`.
(In this final command most of the CFLAGS are irrelevant, including the `-I` directive - that's only for include files - but we include $(CFLAGS) on the command line just for completeness.)

Indeed, we could write a top-level Makefile that makes those calls to Make, as shown in the the [Lab4 starter kit](https://gitlab.cs.dartmouth.edu/CS50/tse).

You may want to use similar techniques in building `common.a` in Lab4; just arrange your files in an appropriate directory structure and think carefully about the include path (specified with `-I`) and the way you list dependencies.
