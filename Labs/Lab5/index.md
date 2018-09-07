---
layout: page
title: Lab 5 - Indexer
---

**Due Friday, May 5, at 10pm**

In this lab you'll continue the Tiny Search Engine (TSE) by coding the Indexer and a program for testing a unit that saves and loads index files, according to the [Indexer Requirements Spec](REQUIREMENTS.html).

* TOC
{:toc}

## Preparation

 1. Start with the same Gitlab project you used for Lab 4.
*Before you begin*, make sure you submitted Lab 4 correctly: you tagged the submitted version with `lab4submit`, [as instructed]({{site.labs}}/Lab4/#howsubmit), and pushed that tag to your Gitlab remote.

 2. Check to ensure your local repo is clean with `make clean` and everything has been committed and pushed according to `git status`.
If you have files that need to be committed, or commits that should be pushed, do that now.
(oops - were those supposed to be part of your Lab 4 submission?
See the first step above.)

 3. **Do not proceed** if you have uncommitted changes or unpushed commits.
Seek help if you need to sort out your repo and Gitlab.

 3. Pull the updated and additional files from the upstream master (the TSE starter kit) into your local repository:
`git pull upstream master`
(this works if you earlier followed the [instructions from Section meeting]({{site.sections}}/05/)).
> [Here](https://gitlab.cs.dartmouth.edu/CS50/tse/compare/341328cc0ba0501a0f53eabace60a5cdbbd5b762...HEAD) you can see the changes that will happen when you run this command - all the changes made to the starter kit since it was released.

 4. Commit and push your changes; perhaps tag this commit for easy reference later: `git commit -a; git tag lab5start; git push --tags`.

 5. Check again to be sure your Gitlab repo is ***private*** (not *internal* or *public*).
Visit your repo on Gitlab, click on *Settings*, and scroll down to *Project Visibility*.


## Assignment

Write the *indexer*, second sub-system of the Tiny Search Engine.
Please follow the [CS50 coding style guidelines]({{site.resources}}/CodingStyle.html) and the [Indexer Requirements Spec](REQUIREMENTS.html), and make good use of our abstract data structures.

Now is a good time to read Section 4 in *[Searching the Web]({{site.reading}}/searchingtheweb.pdf)*, the paper about search engines.

 1. In the `indexer` subdirectory, write
	 * a program `indexer`;
	 * a program `indextest`;
	 * a short file `README.md` to provide any special information about compiling or using your indexer or indextest programs;
	 * a file `DESIGN.md` to provide the Design Spec for indexer (not index tester), drawing inspiration from the [lecture notes]({{site.lectures}}/indexer/);
	 * a file `IMPLEMENTATION.md` to provide the implementation spec and testing plan for indexer (not index tester);
	 * a file `TESTING.md`, telling the grader how you tested your indexer (see [about testing](#testing) below);
	 * a `.gitignore` file telling Git to ignore the binary files (libraries, executables) in this directory.

 2.  Both programs shall leverage common code from `common.a` in the `../common` directory:

	 * a module `index.c` that contains all the logic for saving and loading index files (this module is common between the Indexer, Querier, and indextest);
	 * a module `pagedir.c` that contains all the logic for saving pages to a crawler output directory, for loading pages from a crawler output directory (this module is common between the Crawler and Indexer);
	 * (optionally) a module `word.c` that implements `NormalizeWord` (this module is common between the Indexer and Querier);
	 * a `Makefile` that builds `common.a` for use by the programs;
	 * a short `README.md` file explaining how to build `common.a`;
	 * a `.gitignore` file telling Git to ignore the binary files (libraries, executables) in this directory.

 3. Review your top-level `README.md` and `Makefile` to update as needed.


### Submission - what {#whatsubmit}

In this lab you shall edit or add files as described above.
***You must arrange your directory like ours, so we can better navigate and test your code.***  Of course, you may have additional files - test scripts, test output, code you've chosen to break into multiple files.
Here is the solution's [directory structure]({{site.labs}}/Lab5/tse-tree.txt); it includes some of the optional files and some of the testing files, which may not be present in your solution.
The point is that your code must be organized in the same *directory* structure.

*You shall NOT modify any of the code we provide in `libcs50`*.

*You shall NOT include any data files produced by the crawler or indexer, or any binary/object files produced by the compiler, backup files, core dumps, etc.*

### Submission - how {#howsubmit}

When you are ready for final submission,

* **Add** all required files using an appropriate `git add` commandline.
* **Commit** all changes using an appropriate `git commit` commandline.
* **Tag**: `git tag lab5submit`
* **Push**: `git push --tags` to ensure the tags are pushed to the remote.
See [more about tags]({{site.lectures}}/git/tags.html).

Use your web browser to view your remote on Gitlab and make sure there is a tag `lab5submit` and the files associated with that tagged commit include everything we'll need to grade your lab.

We grade the version tagged `lab5submit` so it is safe for you to continue work (e.g., so you can start work on Lab 6), even if you commit or push.

We will clone your repo at 0h, 24h, 48h, and 72h after the original deadline.
We will start grading when we first see one with tag `lab5submit`, and judge it late if that tag was added after the deadline.
To avoid confusion, *please blitz the team `cs50 AT cs.dartmouth.edu` if you want a late submission to be graded instead of your on-time submission.*

***Your entire codebase must compile with `make` from the top-level directory and produce no compiler warnings.***  If we find that your code will not compile, or has **segmentation faults**, we will send it back to you as soon as we can for repair; recall the [grading policy]({{site.logistics}}/#crashes).

We will run your indexer on our own set of test data.

We will run `valgrind` on your program to look for memory leaks; you will lose points for memory leaks or memory errors.

### Extensions

If you want to claim your extension, create a file `EXTENSION` at the top-level directory of your repository.
Don't forget to `git push` *(before the deadline!)* so we will see the file.
For example,

```bash
$ touch EXTENSION
$ git add EXTENSION
$ git commit -m "extension request"
$ git tag lab5submit     # add tag, as above
$ git push --tags        # push to gitlab, including tags
```

Use your web browser to view your remote on Gitlab and make sure there is a tag `lab5submit` and that its files include `EXTENSION`.

When you are ready to submit your code, remove `EXTENSION` as follows, *update your submission tag*, and push to Gitlab:

```bash
$ git rm EXTENSION
$ git commit -m "ready for grading"
$ git push --delete origin lab5submit # remove the tag from remote
$ git tag -f lab5submit  # move the local tag forward to this commit
$ git push --tags        # push to gitlab remote, including tags
```

Use your web browser to view your remote on Gitlab and make sure there is a tag `lab5submit`, that its files do *not* include `EXTENSION`, and its files include everything we'll need to grade your lab.



## Hints and tips

### Review the lecture notes

There are some design tips in the [lecture notes]({{site.lectures}}/indexer/).
This week's [reading]({{site.reading}}/#week-6) is great too!

### libcs50

We provide several modules in the `libcs50` directory, which compiles to a library `libcs50.a` you can link with your indexer.
*You should not change any of our code.*
You may drop in your `set.[ch]`, `counters.[ch]`, `hashtable.[ch]` files from Lab 3.
If you'd prefer to use our version of *set*, *counters*, and *hashtable*, that's totally fine; the starter kit includes a pre-compiled library you can use instead; see `libcs50/README.md`.

Most of the modules in this directory are documented with a corresponding Markdown file.

### Markdown

In this and subsequent labs, you must provide documentation files in Markdown format, that is, you should supply `README.md`, `DESIGN.md`, `IMPLEMENTATION.md`, and `TESTING.md`.
The Markdown syntax provides very simple (and readable) markup for headings, lists, italics, bold, and code snippets.
(This course website is written in Markdown.) See [Markdown resources]({{site.resources}}/#markdown).

### Testing {#testing}

If your crawler never quite worked, never fear!
You do not need a working crawler to write or test your indexer.
Try your indexer on the crawler's output, which is in `~cs50/demo/crawler-output/`.

We recommend that you write a bash script to execute your indexer; you might run that script from a `make test` target.
Your `TESTING.md` file can name the script and describe what it does.

Because some of our data-structure implementations have unspecified ordering -- the order in which data appears when traversing the structure may not be the same as the order items were inserted -- the file saved by the index tester may not be literally identical to the file read by that program.
We provide an [`indexsort.awk`]({{site.labs}}/Lab5/indexsort.awk)  script that sorts the index file into a 'canonical' ordering, making it possible to compare two index files for their content.

Note that `TESTING.md` is different from the 'Testing plan', which is a short high-level description written before you code.
`TESTING.md` contains (or refers to) results from the tests.
It may refer to other files that contain input to or output from your test runs, or scripts to run the tests; they need not be copied into this file.
(Indeed, your file will be much more readable if you don't fill it with long scripts or output!)

### Use valgrind and gdb

In [Lecture]({{site.lectures}}/debug/) we learned how to use `valgrind` and `gdb`; make use of them.

### Memory allocation

You may find the `memory.c` module useful.
Its use is optional, but it is ready to use as part of library `libcs50.a`.

In our Lab3 we tried to recover gracefully from memory-allocation failures.
In the TSE application programs, we'll be a bit more lazy: on NULL return from malloc/calloc you can print an error and exit with non-zero exit status.
(You may find the `assertp()` function, defined by the `memory` module, to be useful here.)

### Hashtable

"How big should the hashtable be?"

In the indexer/querier, we use a hashtable to store an inverted index (words –> documents), and thus the hashtable is keyed by words.
The answer to the above question, then, depends on how many words will be in the index.

When building the inverted index, it's impossible to know in advance how many words you will find in all those pages encountered by the crawler.
Pick a reasonable size, perhaps something in the range of 200..900 slots.

When loading an inverted index from a file, though, you *can* know how many words... because there is one word per line in the index file, and it's easy to count the number of lines (see `file.c`).
Once your code can obtain the number of words, think about how it can compute a good size for your hashtable.

### pageDirectory

Recall that the Crawler fills a directory with saved pages; in Lab 4 we recommended that you also create and leave a file `.crawler` in the page directory.
If you followed that advice, you now have a great opportunity!
You might include a function `isCrawlerDirectory(char *dir)` in your `pagedir` module, which can easily verify whether `dir` is indeed a Crawler-produced directory.
If it can open a file `dir/.crawler` for reading, then `dir` is a Crawler-produced directory; if not, either the `dir` is not a valid pathname, not a directory, not a readable directory, it's not a Crawler produced directory, or some other error - all easily caught by this simple test.

### Index files

To read each line of the index file, it works well to read the word, then loop calling `fscanf` with format `"%d %d "` to pull off one pair at a time, checking the return value of `fscanf`.

To write the index file, use the `_iterate` methods built into your data structures.
(Indeed you may need to have iterators call iterators!) Do *not* use your `_print` methods for this purpose; those are meant for producing pretty human-readable output for debugging purposes.


The functions found in `file.c` should be helpful.

### Makefile

Your `indexer/Makefile` needs to build both `indexer` and `indextest`.
It may be most convenient to add a phony top-most rule:

```make
all: indexer indextest
```

so that `make` or `make all` will build both programs; if you want to build just one, run `make indexer` or `make indextest`.

You may also find it useful to add phony rules so you can `make test` or `make valgrind`.

Good luck!
