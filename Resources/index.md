---
layout: page
title: Resources
---

## Textbooks and Resources

**There is no required textbook for this course**.
However, we do highly recommend *C: A Reference Manual* by Harbison and Steele.
I have found it to be invaluable and always near my desk.
There is a copy [on reserve](http://libcat.dartmouth.edu/search/r?SEARCH=cosc+050) at Baker Library.
There may be copies available in local bookstores, or you can order it from [Amazon](http://www.amazon.com/Reference-Manual-Samuel-P-Harbison/dp/013089592X/) or [Barnes & Noble](http://www.barnesandnoble.com/w/c-samuel-p-harbison/1002260874?ean=9780130895929).
Look for the most recent (fifth) edition.

When we need a more traditional C text, we refer to *[The C Book](http://publications.gbdirect.co.uk/c_book)*, second edition, by Mike Banahan, Declan Brady and Mark Doran, originally published by Addison Wesley in 1991.
This book is available online [here](http://publications.gbdirect.co.uk/c_book).

The UNIX operating system and the C programming language have both been around for quite some time.
UNIX was originally developed in the late 1960's in assembly language and was mostly reimplemented in the new C programming language by the early 1970's.
The first book on C, Kernighan and Ritchie's *[C Programming Language](http://www.amazon.com/Programming-Language-2nd-Brian-Kernighan/dp/0131103628/ref=sr_1_1?ie=UTF8&qid=1321068335&sr=8-1),* is still in print, and is owned by most UNIX geeks -- not because it's such a great reference, but, well, just because.
There are a large number of number of books on UNIX and all of its variants, including Linux (see below).

UNIX systems contain lots of documentation in the form of what are called   `man pages`, which is short for "manual pages".
Thus, a hardcopy book on UNIX may not be really necessary -- I didn't own a UNIX book until many years after I began using UNIX.

Documentation for many of the tools we will be using will either be found in   `man pages` or will be supplied as URL's on this page.
Of course, you're welcome to employ your favorite search engine, but beware that there are subtle variations in UNIX tools across its many flavors and distributions.
For CS50, the `man pages` on CS department servers are the definitive reference.

Other resources, papers, and references will appear on in this page as they are identified.
If you find others that you like, please let me know and we'll share them with everyone.

### General

[CS Department User's FAQ](https://wiki.cs.dartmouth.edu/faq/doku.php/users_faq:first); you'll need to log in using your CS UNIX username and password.

### Bash

Here are some good links to bash scripting information.

-   [Short bash tutorial](http://www.panix.com/~elflord/unix/bash-tute.html)
-   [GNU bash manual](http://www.gnu.org/software/bash/)
-   [BASH Programming - Introduction HOW-TO](http://tldp.org/HOWTO/Bash-Prog-Intro-HOWTO.html)
-   [Advanced bash scripting guide](http://tldp.org/LDP/abs/html/)
-   *[Bash Pocket Reference: Help for Power Users and Sys Admins](http://www.amazon.com/Bash-Pocket-Reference-Power-Admins/dp/1491941596),* 2nd Edition, by Arnold Robbins; a short and useful book for less than ten bucks.
-   [explainshell](http://explainshell.com), a *very cool* website that lets you type a bash command and get feedback on what it's supposed to do.  (It's drawing on the man pages.)


### Editors

Editor software (a very personal choice - I have used `emacs` for many years, as it is extensible (via Lisp) and customizable.
Others prefer the increasingly popular `sublime text` editor ($70) - I'm told it is fast, highly extensible using python & JSON.
They are both excellent for longer sessions.
Others prefer `vim`.
For quick fixes and slow ssh connections the `vi` editor is a workable alternative.

-   [Getting started with Sublime Text](StartingSublime.pdf) and [a great tutorial](http://code.tutsplus.com/articles/perfect-workflow-in-sublime-text-free-course--net-27293)
-   [Emacs tutorial](http://www2.lib.uchicago.edu/keith/tcl-course/emacs-tutorial.html)
-   [Emacs quick reference guide](http://marc-abramowitz.com/download/emacs_22_reference_card.ps2pdf14.pdf)
-   [An Extremely Quick and Simple Introduction to the Vi Text Editor](http://heather.cs.ucdavis.edu/~matloff/UnixAndC/Editors/ViIntro.html)
-   [vim tutorial](http://blog.interlinked.org/tutorials/vim_tutorial.html)

### Markdown {#markdown}

A file with extension `.md` is assumed to be a text file in 'Markdown' syntax, which provides very simple (and readable) markup for headings, lists, italics, bold, hyperlinks, code snippets, and embedded images.
(This course website is written in Markdown and rendered with Jekyll.) Many source-code web portals (like our Gitlab and the popular Github) allow you to browse the files in your repository - automatically rendering any that are in Markdown format, making such files much nicer to look at than plain-text files.
You can edit Markdown files in any text editor, but there are some specialized editors available.
Markdown is easy to learn and there are many useful resources online:

 * a quick [tutorial](http://www.markdown-tutorial.com/#/overview).
 * Gitlab's [Markdown guide](https://gitlab.cs.dartmouth.edu/help/user/markdown.md) (after all, CS50 uses Gitlab!)
 * Github's *[Mastering Markdown](https://guides.github.com/features/mastering-markdown/)* tutorial.
 * Github's *[Markdown cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet).*
 * Brett Terpstra's *[Write better Markdown](http://brettterpstra.com/2015/08/24/write-better-markdown/)*, which recognizes that many flavors of Markdown exist.
 * [Markoff](https://robots.thoughtbot.com/markoff-free-markdown-previewer), a MacOS application for previewing Markdown files.
 * [Macdown](http://macdown.uranusjr.com), a MacOS application for editing Markdown files.

### Git

Great references for the `git` distributed version control system that we use

 -   Instructions for setting up [Gitlab with SSH](gitlab-ssh.html).
 -   Free ["Pro Git" book](http://git-scm.com/book) by Scott Chacon, plus the website has LOTS of additional git references, including videos!
 -   Some interactive tutorials
    -   [try.github](http://try.github.io/levels/1/challenges/1)
    -   [explain git](https://onlywei.github.io/explain-git-with-d3/)
-   Some other non-interactive video tutorials
  -   [learn version control with git](http://www.git-tower.com/learn/videos)
  -   [git tutorial (requires Ruby)](http://gitimmersion.com/index.html)
  -   [resolving conflicts](https://help.github.com/articles/resolving-a-merge-conflict-using-the-command-line/)
-   A very slick (and free) GUI for `git` called [SourceTree](https://www.atlassian.com/software/sourcetree) is very popular, as is the excellent licensed (not free) application [Tower<sup>2</sup>.](http://www.git-tower.com/)
-   Reference for [common `.gitignore` files](https://github.com/github/gitignore)

### Tools

Software tools we may be using

  -   [valgrind](http://valgrind.org/): a family of tools for dynamic analysis of programs.
  -   [quick guide to valgrind](https://web.stanford.edu/class/cs107/guide_valgrind.html)

  -   [GNU make](http://www.gnu.org/software/make/manual/make.html) is a utility for determining what needs to be done (e.g., compile, link, copy, etc.) to build a program or other target, and then issues the commands to do it.

  -   [pandoc](http://johnmacfarlane.net/pandoc/): A universal document converter.

  -   [gtk](http://www.gtk.org/documentation.php): A popular toolkit for creating graphical user interfaces.
Follow the X11 instructions below to learn how to compile and use `gtk`.

  -   [X11 and XQuartz](XQuartz/): to run window-based (or graphical) applications on the CS50 Unix servers, but allow them to pop open windows on your Mac, you'll need to install XQuartz.
Installation is simple; this link has instructions for installing and using XQuartz, and for compiling `gtk` applications.

### Unix books

Unix & Linux books / links

 -   *[A Practical Guide to Linux Commands, Editors, and Shell Programming](http://www.amazon.com/Practical-Commands-Editors-Programming-Edition/dp/013308504X/ref=sr_1_1?ie=UTF8&qid=1394757793&sr=8-1&keywords=Linux+Commands,+Editors,+and+Shell+Programming+Mark+G.+Sobell),* by Mark G. Sobell; an excellent, comprehensive, hands-on book on Linux and shell programming as well as Python, Perl, and MySQL.
 -   *[Beginning Linux Programming, 4th Edition](http://www.amazon.com/Beginning-Linux-Programming-Neil-Matthew-ebook/dp/B004YK0KO8/ref=sr_1_1?s=books&ie=UTF8&qid=1393966477&sr=1-1&keywords=beginning+linux+programming),* by Neil Matthew, Richard Stones; A really good book covering, debugging, processes, threads, and socket programming in clear and easy manner
 -   *[The Practice of Programming](http://www.amazon.com/Practice-Programming-Addison-Wesley-Professional-Computing/dp/020161586X/ref=pd_bbs_sr_2?ie=UTF8&s=books&qid=1199226460&sr=1-2),* by Brian W. Kernighan, Rob Pike; a great classic book on design and programming for Unix and C.
 -   *[Professional Linux Programming](http://www.amazon.com/Professional-Linux-Programming-Jon-Masters/dp/0471776130/ref=sr_1_cc_2?s=aps&ie=UTF8&qid=1399424116&sr=1-2-catcorr&keywords=masters+and+blum+linux),* by Jon Masters and Richard Blum; an oldie (2007) but a goodie.
 -   *[UNIX Network Programming](http://www.amazon.com/Unix-Network-Programming-Sockets-Networking/dp/0131411551/ref=sr_1_2?ie=UTF8&qid=1329757685&sr=8-2),* by W. Richard Stevens, 2003; Prentice-Hall.
 -   *[Linux in a Nutshell](http://www.amazon.com/Linux-Nutshell-Ellen-Siever/dp/0596154488)*
 -   *[Linux System Programming](http://www.amazon.com/Linux-System-Programming-Talking-Directly/dp/1449339530)*
 -   *[What Is the X Window System](http://www.linuxdevcenter.com/lpt/a/6109),* from O'Reilly's linux devcenter.com
 -   *[Unix, Linux, and variants](http://www.computerhope.com/unix.htm#04)*, free website listing common Unix commands
 -   *[Bash command line editing](http://www.math.utah.edu/docs/info/features_7.html)*
 -   *[Unix for MacOS X users](https://www.lynda.com/Mac-OS-X-10-6-tutorials/Unix-for-Mac-OS-X-Users/78546-2.html),* a video tutorial from 2011 version of MacOS X. From Lynda.com, which is free to Dartmouth users.
 -   [Homebrew](Homebrew.html), a tool for installing Unix tools on MacOS. Highly recommended for CS50!


### Programming

  -   [C programming tutorials](https://www.lynda.com/Programming-Languages-training-tutorials/1467-0.html?category=c_1249) -- video tutorials from Lynda.com, which are free to Dartmouth users.

  -   *[The Pragmatic Programmer](http://pragprog.com/book/tpp/the-pragmatic-programmer)*[, by Andrew Hunt and David Thomas. 2000, Addison Wesley.](http://pragprog.com/book/tpp/the-pragmatic-programmer)
  -   [97 things every programmer should know, by Kevlin Henney. O'Reilly 2010.](http://www.amazon.com/Things-Every-Programmer-Should-Know/dp/0596809484/ref=sr_1_2?ie=UTF8&qid=1363813033&sr=8-2&keywords=97+things+every+programmer+should+know)
  -   *[A First Book of ANSI C, Fourth Edition,](http://www.amazon.com/First-Book-Fourth-Introduction-Programming/dp/1418835560/ref=sr_1_1?s=books&ie=UTF8&qid=1363813105&sr=1-1&keywords=bronson+ansi+c)* [by Gary J. Bronson](http://www.amazon.com/First-Book-Fourth-Introduction-Programming/dp/1418835560/ref=sr_1_1?s=books&ie=UTF8&qid=1363813105&sr=1-1&keywords=bronson+ansi+c); a very good book for learning C
  -   [The Wikipedia entry for the C programming language](http://en.wikipedia.org/wiki/C_programming_language)
  -   [The USENET discussion Why is C good?](http://groups.google.com/group/comp.lang.c/browse_frm/thread/1ce1b07f3725e0c7?q=%22Why+is+C+good%3F%3F%3F%22&hl=en&pli=1)
  -   *[An Introduction to the C programming language](RC13972-C-Programming.pdf),* by Charles Palmer (1988). Easy read with lots of simple examples. Skip to page 20 to start, and remember some of the comments are dated (e.g., "*variables in all lower case*").
  -   Quick reference cards for [C](http://users.ece.utexas.edu/~adnan/c-refcard.pdf) and [gdb](http://users.ece.utexas.edu/~adnan/gdb-refcard.pdf).

Remember that we're not suggesting you buy all these books.
The text by Harbison and Steele is highly recommended for this course and may be in local bookstores.
