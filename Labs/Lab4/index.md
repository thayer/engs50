---
layout: page
title: Lab 4 - Crawler
---

**Due Friday, April 27, 2018, at 10pm**

In this lab you'll begin the Tiny Search Engine (TSE) by coding the Crawler according to the [Crawler Requirements Spec](REQUIREMENTS.html) and the  [Crawler Design Spec](DESIGN.html).

* TOC
{:toc}

## Preparation

 1. *Fork* a copy of our [TSE starter kit](https://gitlab.cs.dartmouth.edu/CS50/tse) to make a new project in your Gitlab account; see instructions in the README there.
Ensure the repo is *Private*.
Give "Master" access to Professor Palmer (ccpalmer) and to head grader Haider Syed ( he may have two ids in Gitlab, use the one with "@h").

 2. *Clone* the new project to a Git repository on your CS Unix account; again, see instructions in your fork's README.

 3. Edit the `README.md` file to remove the git instructions; a suggested template is at the bottom of the file. Include your name!

 4. In the terminal, **copy** your [Lab 3](Lab3/) sources (just `counters.[ch] set.[ch] hashtable.[ch]`) to the `libcs50` subdirectory in your brand-new repository; try `make` in that directory to ensure everything works.

 5.  `git add libcs50/*.[ch]; git commit -a; git push`.

 6. Visit your repo on [Gitlab](gitlab.cs.dartmouth.edu) and you should see the updated README and your new source files.
Double-check the [visibility](https://gitlab.cs.dartmouth.edu/help/public_access/public_access) of your repo to ensure it is ***Private***.

## Assignment

Write the *crawler*, first sub-system of the Tiny Search Engine.
Please follow the [CS50 coding style guidelines]({{site.resources}}/CodingStyle.html), the [Crawler Requirements Spec](REQUIREMENTS.html), and the  [Crawler Design Spec](DESIGN.html).

 1. Create a subdirectory `crawler`.

 4. In that directory, write a program `crawler` that implements the Requirements Spec, leveraging your data structures.
Please take special care that your crawler does not explore URLs that are not 'internal' according to `IsInternalURL()`.

 5. In that directory, write a `Makefile` so you can build everything from the top-level directory by simply typing `make`, and clean up everything by typing `make clean`.
To build `crawler` you will need to add `-lcurl` to include the `libcurl` library.

 7. In that directory, write a `README.md` file to provide any special information about how to compile or use your crawler.
This file is likely to be short.
*You must use Markdown; see below.*

 7. In that directory, write a `IMPLEMENTATION.md` file to describe the implementation of your crawler.
*You must use Markdown; see below.*

 8. Add a `TESTING.md` file in the `crawler` directory, telling the grader how you tested your crawler.
(You may find it helpful to write a `bash` script to execute your crawler, and/or a `make test` target.) Read [about testing](#testing-crawler) below.

 6. As you create files and directories, add them to your git repository.
**Important:** do not add any compiled files to git.
In short: your repo should not contain any data files, core dumps, or files built with `make` and removed by `make clean`.
Commit and push at least once a day.


## Submission - what {#whatsubmit}

In this lab you shall add/edit these files in your repo:

* `README.md` (edited)
* `Makefile` (possibly edited)
* `crawler/`
	* `Makefile`
	* `crawler.c`
	* `README.md`
	* `IMPLEMENTATION.md`
	* `TESTING.md`
	* *optional other files related to testing*
* `common/` *if you follow our tip/suggestion below*
	* `pagedir.c`
	* `pagedir.h`
* `libcs50/`  *if you wish to use your Lab3 solution*
	* `set.c`
	* `counters.c`
	* `hashtable.c`

*You shall NOT modify any of the code we provide in `libcs50`*.

*You shall NOT include any data files produced by the crawler, any binary/object files produced by the compiler, backup files, core dumps etc.*

## Submission - how {#howsubmit}

When you are ready for final submission,

* **Add** all required files using an appropriate `git add` commandline.
* **Commit** all changes using an appropriate `git commit` commandline.
* **Tag**: `git tag lab4submit`
* **Push**: `git push --tags` to ensure the tags are pushed to the remote.
See [more about tags]({{site.lectures}}/git/tags.html).

Use your web browser to view your remote on Gitlab and make sure there is a tag `lab4submit` and the files associated with that tagged commit include everything we'll need to grade your lab.

We grade the version tagged `lab4submit` so it is safe for you to continue work (e.g., so you can start work on Lab 5), even if you commit or push.

We will clone your repo at 0h, 24h, 48h, and 72h after the original deadline.
We will start grading when we first see one with tag `lab4submit`, and judge it late if that tag was added after the deadline.
To avoid confusion, *please blitz `cs50 AT cs.dartmouth.edu` if you want a late submission to be graded instead of your on-time submission.*

***Your entire codebase must compile with `make` from the top-level directory and produce no compiler warnings.***  If we find that your code will not compile, or has **segmentation faults**, we will send it back to you as soon as we can for repair; recall the [grading policy]({{site.logistics}}/#crashes).

We will run your crawler on our own set of test data.

We will run `valgrind` on your program to look for memory leaks; you will lose points for memory leaks or memory errors.
**Important**: the `libcurl` library is known to leave some "still reachable" memory; these are not your fault and will not count against you.


### Extensions

If you want to claim your 24h extension, create a file `EXTENSION` at the top-level directory of your repository.
Don't forget to `git push` *(before the deadline!)* so we will see the file.
For example,

```bash
$ touch EXTENSION
$ git add EXTENSION
$ git commit -m "extension request"
$ git tag lab4submit     # add tag, as above
$ git push --tags        # push to gitlab, including tags
```

Use your web browser to view your remote on Gitlab and make sure there is a tag `lab4submit` and that its files include `EXTENSION`.

When you are ready to submit your code, remove `EXTENSION` as follows, *update your submission tag*, and push to Gitlab:

```bash
$ git rm EXTENSION
$ git commit -m "ready for grading"
$ git push --delete origin lab4submit # remove the tag from remote
$ git tag -f lab4submit  # move the local tag forward to this commit
$ git push --tags        # push to gitlab remote, including tags
```

Use your web browser to view your remote on Gitlab and make sure there is a tag `lab4submit`, that its files do *not* include `EXTENSION`, and its files include everything we'll need to grade your lab.


# Hints and tips

### libcs50

We provide several modules in the `libcs50` directory, which compiles to a library `libcs50.a` you can link with your crawler.
*You should not change any of our code.*
You may drop in your `set.[ch]`, `counters.[ch]`, `hashtable.[ch]` files from Lab 3.
If you'd prefer to use our version of *set*, *counters*, and *hashtable*, that's totally fine; the starter kit includes a pre-compiled library you can use instead; see `libcs50/README.md`.

Most of the modules in this directory are documented with a corresponding Markdown file.

### Markdown

In this and subsequent labs, you must provide documentation files in Markdown format, that is, you should supply `README.md`, `IMPLEMENTATION.md`, and `TESTING.md`.
The Markdown syntax provides very simple (and readable) markup for headings, lists, italics, bold, and code snippets.
(This course website is written in Markdown.) See [Markdown resources]({{site.resources}}/#markdown).

### Testing Crawler {#testing-crawler}

It is your responsibility to test your crawler and write about your approach in `TESTING.md`.
Consider following some of the testing plan discussed in [Lecture]({{site.lectures}}/crawler/).

Some safe seeds you might test include

 * http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters
 * http://old-www.cs.dartmouth.edu/~cs50/index.html
 * http://old-www.cs.dartmouth.edu/~cs50/data/tse/wikipedia

> The first two are good at depths 0 and higher, but the Wikipedia case is likely too slow to run past maxDepth=2.

You may point your crawler at any other CS user's home page - but your seed URL must begin with `http://old-www.cs.dartmouth.edu/`.

For example, you might construct your own test files in your CS Unix account in a directory like `~/public_html/tse` and crawl the URL `http://old-www.cs.dartmouth.edu/~YOURUSERID/tse`


### Use valgrind and gdb

In [Lecture]({{site.lectures}}/debug/) we learned how to use `valgrind` and `gdb`; make use of them.

### Memory allocation

You may find the `memory.c` module useful.
Its use is optional, but it is ready to use as part of library `libcs50.a`.

In our Lab3 we tried to recover gracefully from memory-allocation failures.
In the TSE application programs, we'll be a bit more lazy: on NULL return from malloc/calloc you can print an error and exit with non-zero exit status.
(You may find the `assertp()` function, defined by the  `memory` module, to be useful here.)

### Hashtable of URL

Our design calls for use of a Hashtable to store the URLs already seen.
Our Hashtable implementation stores a `void*item` with each key... but if you're just storing URLs (as keys), what item do you store?
Our hashtable disallows NULL items.
Suggestion: just pass a constant string as the item.

### Pseudocode

Your implementation does not need to follow our pseudocode; this is one reason why you need to write about your implementation choices in `IMPLEMENTATION.md`.

Our pseudocode refers to a `pagefetcher`; note this is effectively `webage_fetch()`.
**Note that `webage_fetch()` inserts a 1-second delay after every fetch attempt**; your Crawler thus gets this behavior for free.

Our pseudocode refers to a `pagescanner`; yours should leverage `webage_getNextURL()`.


### pageDirectory

The Crawler is supposed to determine whether the pathname provided as pageDirectory is indeed a directory, and is writable (meaning, you can create files there).
How?
The simplest method is to create a file there.
If you construct a string `filename` that is the directory name, followed by a slash `'/'`, followed by a file name like `.crawler`, you could call `fopen(filename, "w")`; if it returns NULL (failure), then either the directory does not exist or is not writable.
If it returns non-NULL (success), close the file.
It's fine to leave `.crawler` in the page directory.
(Actually, the presence of this file will later help your indexer  confirm the pageDirectory is indeed a Crawler-produced directory.)

**Tip: think ahead**, and put the code for writing webpages to the pageDirectory in a separate `pagedir` module, in the `common` directory.
Write a `Makefile` that produces library `common/common.a`.
Not required for Lab4 but you'll end up needing to take this step in Lab5 anyway.
