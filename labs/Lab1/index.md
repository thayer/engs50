---
layout: page
title: Lab 1 - Bash
---

**Due Sunday, April 2, at 11:00pm**

This first lab is relatively quick, and should get you up to speed working with the command line, basic shell commands, an editor, and a small shell program.

* TOC
{:toc} 

## Materials

You will need these materials for this assignment.

* *Alice in Wonderland*, which you will find as plaintext in file `alice-gutenberg.txt` on canvas.
> Credit: [Project Gutenberg](http://www.gutenberg.org/ebooks/11)

* Shakespeare's sonnets, which you will find as plaintext files,
are available in the tar file `sonnets.tar` on canvas. This file unpacks into a
subdirectory `sonnets`. 
> Credit: [Project Gutenberg](http://www.gutenberg.org/ebooks/1041)


Curious how the `sonnets` directory from Gutenberg's [`sonnets.html`](sonnets.html) file?
Look at the bottom of this page.

## Preparation

Set up for your work in this course, if you have not already:

```bash
$ cd
$ mkdir -p cs50/labs/lab1
$ chmod go-rwx cs50
$ cd cs50/labs/lab1
```

These commands create a directory `~/cs50/labs/lab1`, prevent others
from peeking at your work, and change the working directory to `lab1`
so you're ready for the work below.


## Assignment

1. Write a single bash command/pipeline that will extract the text of
*Alice in Wonderland* into a file `alice.txt` in your `lab1`
directory.  (Note that the provided file has header and footer
material added by Project Gutenberg.  We want only the stuff Lewis
Carroll wrote.)

1. Write a single bash command/pipeline that will read `alice.txt` and
   print a crude table of contents.

1. Write a single bash command/pipeline that will read `alice.txt` and
print the words, in order, exactly one word per line, into
`alicewords.txt`.  (A *word* is a sequence of letters.)

1. Write a single bash command/pipeline that will read
   `alicewords.txt` and print the number of times the word "Alice"
   appears, regardless of how it is capitalized.

1. Write a single bash command/pipeline that will read
   `alicewords.txt` and print the number of times the word "wonder"
   appears, regardless of how it is capitalized; be careful not to
   count other words!

1. Write a single bash command/pipeline that will read
   `alicewords.txt` and print the top-10 most-common words, regardless
   of capitalization.

1. Write a single bash command/pipeline that will read `alicewords.txt` and print the number of unique words, regardless of capitalization, that are not [stop words](https://en.wikipedia.org/wiki/Stop_words).
Use the sorted list of stop words in `stopwords.txt` (available on canvas).
> We're going to keep things simple, here; the words "account", "accounts", and "accounting" are all unique words for our purposes, though a fancier solution would *stem* them all to "account".
Given our definition of *word*, above, the word "account's" would appear in `alicewords.txt` as "account" and "s", and the latter will be stripped out as a stopword.
>
> You may find `comm` useful here.

1. Write a bash script called `shake.sh` that allows the user to search for a word in all of Shakespeare's sonnets.
 * For each matching sonnet, the script prints one line: the sonnet number, a colon, a space, the first line of the sonnet, then elipses.
 * If the user provides too few or too many arguments, it should print "usage: shake.sh searchword" and exit with status 1.
 * If the script cannot find the `sonnets` directory in the expected location, it should print "cannot find sonnets directory" and exit with status 2.
 * Write three test cases; write each test's command in a separate single-line file `shaketest#`.
Run each test and save its output in a separate file, i.e., `bash shaketest1 > shaketest1.out`.

> For example,
>
> ```
> $ ./shake.sh spring
CII:   My love is strengthen'd, though more weak in seeming;...
CIV:   To me, fair friend, you never can be old,...
I:   From fairest creatures we desire increase,...
LIII:   What is your substance, whereof are you made,...
LXIII:   Against my love shall be as I am now,...
XCVIII:   From you have I been absent in the spring,...
$ ./shake.sh computer
$
> ```
> How many hits will you get if you shake `love`? :-)

## What to hand in, and how

For the command/pipeline questions, write all your answers in a single file `commands.txt`.
*Include each command and its output.*

When finished, you should have the following files:

```bash
$ ls -1
alice.txt
alicewords.txt
commands.txt
shake.sh
shaketest1
shaketest1.out
shaketest2
shaketest2.out
shaketest3
shaketest3.out
```

## Bursting an html file into many sonnets

This section is brought to you by *curiosity*.

How was the files in the `sonnets` directory produced from Gutenberg's
[sonnets.html](sonnets.html) file?  A little `sed` and a little `awk`:

```bash
mkdir sonnets
sed \
 -e '1,/^\*\*\* START/d' \
 -e '/^End of Project Gutenberg/,$d' \
 -e 's/<br \/>//' \
 -e 's/&nbsp;/ /g' \
 -e '/<\/p>/d' \
 -e '/<\/h3>/d' \
 -e '/class="poem"/d' \
 -e '/<pre>/d' \
 -e '/^$/d' sonnets.html \
| awk '\
 /<h3>/ {printing=0; header=1; next;}\
 header {sonnet="sonnets/" $1; print sonnet; printing=1; header=0; next;}\
 printing {print > sonnet}'
```

You don't need to learn `awk` and you will not need it for this
assignment.  But it's a interesting language!
