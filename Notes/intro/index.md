---
layout: page
title: Welcome to CS50!
---

In this lecture, we discuss the aim and schedule of the course, and take a brief look at Unix, C programming, and computer architecture.

## The course

The aim of this course is to develop the necessary systems programming skills in C and Unix as a foundation to tackle the design, implementation, and integration of a large software project working in small teams.
The challenge of the course is to quickly get people up to speed so there is sufficient time to get into the details of a complex software design project.
The first part of the course serves to develop design, programming and other systems skills such as source-code management, testing, and debugging.
The second part of the course is all about the project and team work.
Good team work will lead to success.
That's the message.

A note about Unix/Linux: Unix came first.
All of the others, including BSD, MacOS, and all the variants of Linux, are derivations of that original effort.
While we use Linux on the Sudikoff servers, you may elect to use your own copy of Linux or the Unix that Mac OSX is based on.
Except when it *really* matters, I use the term Unix to refer to them all.


The syllabus in a nutshell:

-   Unix: shell, commands, shell programming;
-   C: structure, arrays, pointers, dynamic memory, files;
-   Programming tools: gcc (GNU compiler), make (maintain groups of programs), gdb (GNU debugger), git (source code management), valgrind (profiling and memory leak checker).
-   Software development methodology: design, implement, unit test/debug, integration, demo, maintenance.
-   Programming: building a search engine (crawler, indexer, query engine).
-   Team project: it's a surprise!

The course includes five Unix shell and C programming assignments for the first part of the course; these assignments are to be done individually.
The last part (about 3 weeks) is devoted to the team project.
There are fewer lectures in the last part of the course but the projects are run with design reviews and progress meetings where the team can brainstorm problems and come up with solutions.

Please take note of the [reading assigned]({{site.baseurl}}/Reading) each week.
I will list the reading week by week, rather than lecture by lecture, to give you some flexibility -- but please do the reading, you'll find it to be interesting and valuable!


## Logistics

Read the [Logistics]({{site.logistics}}) information.

**About communication:** be sure to track {{site.piazza}} for announcements and updates.

**About engagement:** you will learn more from this course if you are actively engaged, where *engagement = preparation + participation.*
Read the lecture notes and weekly reading, practice at home, and participate in classroom and Section activities.
The Learning Fellows are here to help with classroom activities, and the Section Leaders are here to help outside class.

**About the programming:** *There is a significant amount of programming in this course, requiring a considerable time commitment on the part of the student.*
You will need to be well organized to complete all the programming assignments and project.
Start each lab early.
It will be challenging, but we hope it will be fun!

**About the project**:
You will be assigned to a team of four students and given about three weeks to complete a large project requiring strong collaboration and a problem-solving mindset.
Each member is responsible for contributing to the overall system design, implementation, testing, integration, and documentation.
The goal of this activity is to help you develop the confidence, skills, and habits necessary to write large computer programs while part of a multi-person team.
You will become conversant in software engineering paradigms, such as source code control with `git` and other open source tools that ease the software development process.
In addition, you will develop vital skills in self-directed learning, problem solving, and communication.
The project concludes with a demo and a review of your design and implementation.
All members of the team get the same base grade, plus a team-contribution grade determined in part by a short evaluation form completed by all members of each project team.


## Goals for today's lecture

We plan to cover the following in today's lecture:

-   The concept of a command line;
-   Logging on to a Unix machine;
-   Looking at the home directory and its files;
-   Editing and compiling our first program in C;
-   Taking a look at the compilation process, from C to machine code;
-   Logging out; and
-   Some housekeeping business.

In the first few lectures we cover Unix, the shell, and shell programming.
This is not meant to be a detailed presentation of the Unix OS and its programming tools -- it would require a whole term to cover all that material in detail.
We need to know enough about Unix and its tools to be able to navigate our way around the system, write some basic shell scripts, and use its programming tools.

It is important that you use these notes as a starting point, but like any budding hacker you need to do some experimenting and read up on the details.
You need to go on the web and find information if there are gaps in your knowledge, and then come see the instructor or TAs for help if you're still stuck.
There are many references on the [Resources]({{site.resources}}) page.

**Caveat**: Please take note that lecture notes will not always be detailed.
You will need to augment these notes with your own comments and by using the references and reading assignments so you can dive deeper into the topic.

## The command line

[Today's shell examples.](script.txt)

Unix was originally developed for computers with hardwired 'terminals', each of which was basically an electronic typewriter - a printer with a keyboard.
There were no graphical displays, and the concepts of 'windows' and 'mouse' had not yet been invented.
To interact with the computer, the user types on the keyboard, and the computer echos the keystrokes on the paper.
(See the [historical note](#historical-note) below.
The system is controlled by typing 'commands', most of which print results for the user to see.
The interaction occurs over the 'command line'.

Modern Unix systems support rich graphical user interfaces, but under the hood they all support the command line.
In this class, I will demonstrate everything using the MacOS command line, accessed via the MacOS application called `Terminal`.
If you have a Mac, you can follow along.
If you use Windows, consider installing Linux on your laptop (either 'dual boot' or 'virtual machine').
But all of us can (and will) also use the department's Linux servers.

When I open a new Terminal window on my Mac, I can type Unix commands at the 'prompt'.
This prompt is from the 'shell' -- a program -- that interprets your command line and runs a program representing each command.
Your prompt may look different - the shell allows users to customize prompts and you'll see a few formats in the examples below.

```bash
[MacBook ~]$ ls
Applications/           Movies/                 bin/
Creative Cloud Files/   Music/                  cs50@
Desktop/                Pictures/               lib/
Documents/              Pictures personal/      projects/
Downloads/              Public/                 public_html/
Dropbox/                Scans/                  repositories/
Google Drive/           Shared@                 src/
Library/                Sites/
[MacBook ~]$ echo Hello CS50
Hello CS50
[MacBook ~]$ 
```

The `ls` command is the "list directory contents" command.
The `echo` command is like a print statement - it echos its arguments back.

Most commands quickly produce some output and then exit.
Some will run too long - perhaps printing too much output; you can stop (kill) the command, forcing it to exit, by typing control-C `^C` at the keyboard.
One silly program, `yes`, just prints an infinite sequence of `y` characters until you kill it:

```bash
[DFK:~] yes
y
y
y
^C
[DFK:~]
```

Some commands ask for your input, and continue to read input until they read an "end of file" (EOF); you can cause the program to detect an EOF by typing control-D `^D` at the beginning of an input line.
Below I typed three lines of text, the `^D` at the start of the fourth input line, to the `cat` program:

```bash
[cs50@flume ~]$ mail kotz@cs
Subject: Hello from cs50
This is an email message from me to kotz@cs.
I can end the message by typing ctrl-D.
bye!
EOT
[cs50@flume ~]$ 
```

Here, when we typed ctrl-D the `mail` program detected an end of file (EOF) on its input (i.e., the keyboard), then printed `EOT` and exited.
Moments later, the mail message landed in my inbox.

Notice the difference between `^C` and `^D`; the former kills the program immediately, whereas the latter causes it to detect EOF when it next reads input from the keyboard.

## Logging into a remote machine using `ssh`

The Department of Computer Science operates a set of Linux servers in the basement of Sudikoff, and you should plan to log in to one of those servers for doing the labs.
(See the [list of recommended servers](http://www.cs.dartmouth.edu/~wbc/suditour/011/index.html) - a web page accessible only on campus.)

I'll login in from my Mac using the **s**ecure **sh**ell (`ssh`) Unix command.
The `ssh` command establishes a secure channel and uses public-key cryptography to authenticate the remote computer and the user.

> The `ssh` command replaces the archaic `telnet` (remote communications with another computer) and `rlogin` (remote login) because they lack security.
The `ssh` command is exclusively used, these days, because your session is encrypted when it's transmitted over the network, rather than being sent in clear text.

Below, I remotely log in as user `kotz` to the server named `flume` by giving its full IP name - `flume.cs.dartmouth.edu`.

```bash
[MacBook ~]$ ssh -l kotz flume.cs.dartmouth.edu
Last login: Fri Jan 27 13:25:26 2017 from 10.31.126.2
[kotz@flume ~]$ ls
cs50/  old/  public_html/
[kotz@flume ~]$ ls cs50
labs/
[kotz@flume ~]$ ls cs50/labs
[kotz@flume ~]$ logout
Connection to flume.cs.dartmouth.edu closed.
[MacBook ~]$ 
```


> It is also possible to connect to a remote Linux server using X-windows, an early form of graphical user interface that has the capability to run applications on a remote server but put the windows on your local computer.
I won't be using X in this course, but you may wish to explore the option.

There are hundreds of Unix commands -- but you probably only need a few dozen to get by.
Each Unix command has a short abbreviated command name (e.g., LiSt directory (ls) or Secure SHell (ssh)) and its associated syntax that typically includes various arguments, and options; typically, these options (or *switches* as they are also known) are either a single letter preceded by a hyphen (e.g., `-l`) or one or more words preceded by two hyphens (e.g., `--verbose`).
For example, the format of an `ssh` command line looks like this:

```bash
	ssh [options] [user@] hostname [command]
```

In `ssh -l kotz flume.cs.dartmouth.edu`, the switch `-l` informs the `ssh` command that the username of the user logging in is kotz.
(Alternately, I could have used the form `ssh kotz@flume.cs.dartmouth.edu`).

This is a good time to look at the formatting of these command help texts.
The `[ ]` are used to denote optional things, like

    [command]

while the things outside of the `[ ]` , like `hostname`, must be specified.


## Getting Information using the online manual (man)

If you want the detailed syntax of a Unix command you can use the manual command followed by the command, as in `man ssh` which produced the following:

```man
    SSH(1)                    BSD General Commands Manual                   SSH(1)

    NAME
         ssh -- OpenSSH SSH client (remote login program)

    SYNOPSIS
         ssh [-1246AaCfgKkMNnqsTtVvXxYy] [-b bind_address] [-c cipher_spec]
             [-D [bind_address:]port] [-e escape_char] [-F configfile] [-I pkcs11] 
             [-i identity_file] [-L [bind_address:]port:host:hostport] [-l login_name]
             [-m mac_spec] [-O ctl_cmd] [-o option] [-p port] 
                [-R [bind_address:]port:host:hostport] [-S ctl_path]
             [-W host:port] [-w local_tun[:remote_tun]] [user@]hostname [command]

    DESCRIPTION
         ssh (SSH client) is a program for logging into a remote machine and for executing
         commands on a remote machine.  It is intended to replace rlogin and rsh, and
         provide secure encrypted communications between two untrusted hosts over an 
         insecure network.  X11 connections and arbitrary TCP ports can also be forwarded 
         over the secure channel.

         ssh connects and logs into the specified hostname (with optional user name).  The 
         user must prove his/her identity to the remote machine using one of several methods 
         depending on the protocol version used (see below).

         If command is specified, it is executed on the remote host instead of a login shell.

         The options are as follows:

         -1      Forces ssh to try protocol version 1 only.

         -2      Forces ssh to try protocol version 2 only.

         -4      Forces ssh to use IPv4 addresses only.

         -6      Forces ssh to use IPv6 addresses only.

         -A      Enables forwarding of the authentication agent connection.  This can also
                 be specified on a per-host

    ... and a whole lot more
```

This is just a snippet of the `man ssh` output (`man` is short for manual).
The manual output includes all the nitty gritty details on options and about the command.
For most commands you can use the common option `--help` (two hyphens) to get a brief breakdown of the command and its switches.
This doesn't work for all commands (including `ssh`, interestingly), but in that case the use of `-help` is interpreted as an invalid entry by ssh and it lists of the options anyway.

You can use

    man -k keyword

to search through the manual pages for matches on a keyword.
For example:

```
[kotz@flume ~]$ man -k shell
bash (1)             - GNU Bourne-Again SHell
capsh (1)            - capability shell wrapper
chroot (1)           - run command or interactive shell with special root directory
chsh (1)             - change your login shell
CPAN::Admin (3pm)    - A CPAN Shell for CPAN admins
CPAN::Plugin (3pm)   - Base class for CPAN shell extensions
csh (1)              - C shell with file name completion and command line editing
... and much more
```


## Your home directory and its files

Each user has a 'home directory'.
After you have logged in using `ssh` you are in your home directory - that is, the shell's notion of your 'current working directory' is your home directory.

We can look at our home directory 'path' using the `pwd` (print working directory) command.
You can always use the `man` and  `info`  commands to get more information.

```bash
[kotz@flume ~]$ pwd
/net/nusers/kotz
[kotz@flume ~]$ 
```

The tilde (~) above is shorthand for 'home'.
Let's take a look at the contents of my home directory (using the -l switch which means long format):

```bash
[kotz@flume ~]$ ls
cs50/  old/  public_html/
[kotz@flume ~]$ ls -l
total 12
drwxrwxr-x 5 kotz root 4096 Feb  2 11:24 cs50/
drwxrwxr-x 2 kotz root 4096 Jan 27 20:00 old/
drwxr-xr-x 3 kotz root 4096 Mar 17 12:01 public_html/
[kotz@flume ~]$ cd cs500
-bash: cd: cs500: No such file or directory
[kotz@flume ~]$ cs cs50
-bash: cs: command not found
[kotz@flume ~]$ cd cs50
[kotz@flume ~/cs50]$ ls -l
total 20
drwxr-xr-x 2 kotz root 4096 Jan 28 11:08 lab1/
drwxr-xr-x 2 kotz root 4096 Feb  2 10:36 lab2/
drwxr-xr-x 2 kotz root 4096 Jan 28 10:14 project/
-rw-r--r-- 1 kotz root   74 Feb  2 11:19 testfile
-rwxr-xr-x 1 kotz root  402 Feb  2 11:23 testread.sh*
[kotz@flume ~/cs50]$ 
```

Yes, I mistyped two commands in that example: `cd cs500` and `cs cs50`.
I wanted you to see what the system says when you make a mistake ... just in case you make one yourself sometime. ;-)

The `cd` command changes the current working directory; I finally typed it right and the shell reported that my working directory is `~/cs50`.
The same command, `ls -l`, listed *that* directory the second time.

Files can be plain files, directories, or special files (more later).
We can see that each file has file permissions and other data associated with it; for example, the directory `public_html`:

```bash
drwxr-xr-x 3 kotz root 4096 Mar 17 12:01 public_html/
```

You can traverse directory trees assuming you have the appropriate permission.

Unix supports a number of shells (command line interpreters).
If we use the echo command we can look at the environment variable that tells us which shell is running.
For this course we will use the bash (Born Again SHell) shell.

Again, the shell is the command processor for Unix systems.
One way to find out what shell you're running, try this:

```bash
[kotz@flume ~/cs50]$ echo my shell is $SHELL
my shell is /bin/bash
[kotz@flume ~/cs50]$ 
```

The last parameter to `echo` substitutes the value of the variable `SHELL`.
More on the bash shell later.

Another useful command for copying files between machines is the `scp` - secure copy (remote file copy program) command.
Below I find, then copy, of the schedule for CS50 from the course website.


```bash
[DFK:~] ssh kotz@flume
Last login: Mon Mar 28 10:17:04 2016 from 10.31.123.28
[kotz@flume ~]$ cd ~cs50
[kotz@flume /net/class/cs50]$ ls
Archive/		 master.bashrc	proc-log      src/  web-tse-from-2016W/
download_16S_repos.awk*  private/	public_html/  web@
[kotz@flume /net/class/cs50]$ cd public_html/
[kotz@flume /net/class/cs50/public_html]$ ls
css/	    Labs/      Logistics/  Reading/    Schedule.pdf
index.html  Lectures/  Project/    Resources/  Schedule.xlsx
[kotz@flume /net/class/cs50/public_html]$ logout
Connection to flume closed.
[DFK:~] scp flume.cs.dartmouth.edu:/net/class/cs50/public_html/Schedule.pdf .
Schedule.pdf                                           100%   44KB  44.1KB/s   00:00    
[DFK:~] open Schedule.pdf
[DFK:~] 
```

Recall that `~` is my home directory, so `~cs50` is the home directory for user `cs50`.
I changed my working directory to the cs50 home, then into its `public_html`, and listed the files there.
Now I know the 'path name' for the desired file - the directory name followed by slash followed by the filename.
The `scp` command allows me to specify the host and pathname for the source and destination of the copy; here the destination is `.`, a shorthand for 'current working directory.
Finally, I used the MacOS command `open` to open the file, which launches `Preview` to show me the pdf.


### Logging out

When we are ready to logout from our session on flume.cs.dartmouth.edu, we use `logout` or `exit`:

```bash
[kotz@flume ~]$ logout
Connection to flume.cs.dartmouth.edu closed.
```

Okay, this has been a good start.

## Housekeeping - things you need to do:

1. Do [lab assignment 0]({{site.labs}}/Lab0/) today!

2. Visit {{site.canvas}} and connect to Piazza to make sure your accounts are set up and linked.

3. Review all of the class materials on the website (Tentative Schedule, Lectures, Reading, Logistics, Reading, Resources), accessible via {{site.canvas}}.
Pay special attention to the [CS Department User's FAQ](https://wiki.cs.dartmouth.edu/faq/doku.php/users_faq:first).

3. Before next class, use your CS unix account to go through the above examples: execute all the commands and get a 'feel' for the shell.

4. Choose an editor and become familiar with it.
This is a very important step, as the reading assignment *["Learn to use a real editor"](http://programmer.97things.oreilly.com/wiki/index.php/Learn_to_Use_a_Real_Editor)* says.
Try both emacs and vim, and see which you prefer.
Your first homework assignment will be released at the next class period, so don't delay!

## One more thing: Remotely accessing CS Unix machines

Note the following, depending on your personal computer's operating system.

**Linux**: The systems in the CS department are running GNU/Linux.
Your Linux will likely be sufficiently compatible that you won't have any trouble developing on your machine and delivering your assignments on a CS machine.
You may want to try the X-windows connection.

**Mac**: Mac OSX Unix conforms to the POSIX standard for the C API, shell utilities, and threads and can compile and run your existing code.
The GNU tools we will be using, such as `gcc`, `make`, etc., are either included or freely available.
(You may need to install command-line tools via Xcode; if so, you will be prompted to do so when you first type `gcc` or `make` or related commands.) You can use the `Terminal` application.
You can also use the `ssh` command to remotely log on to computers, as discussed above.
**We recommend you install [Homebrew]({{site.resources}}/Homebrew.html).**

**Windows**: There are Unix-command shells for Windows and even an X-Window system for Windows systems.
However, since this is a Unix course you would be far better off doing your assignments on the departmental server.
(Some Windows tools support sftp or other means to copy files back and forth; it can work, and it can also lead to disaster.)  Windows users been most successful coding on the lab systems via ssh.
As an alternative, visit Sudikoff 003/005 and use the MacOS computers there.
As another alternative, consider installing Linux on your laptop - either dual-boot (so you can choose Linux or Windows at boot time) or using Virtual Machine software to run one OS on top of the other.



## Historical note {#historical-note}

The name "Terminal" is still commonly used in Unix parlance, right down to the MacOS app by that name.
This term refers to the fact that early Unix computers, like other computers of its time, had a small number of interactive 'terminals' connected to it -- each directly connected by a dedicated wire to a card within the computer.
Each terminal was little more than a keyboard and a screen - or in the early days, a keyboard and a printer that would print each character as it was typed, and print the characters sent by the computer.

The first such terminals were "teletypes", adapted from the device used by newsrooms around the country, which printed characters transmitted over the phone line from a distant device.
This [video](https://www.youtube.com/watch?v=E4IztV7M3jI) shows a Teletype model ASR33.
From the sound of this machine, can you tell why television news shows' opening music usually has a stocatto tap-tap-tap-tap-tap background theme?

<!--David-->
<!--
> One of the first interactive computer systems I ever used was a PDP8/e running ETOS and BASIC - far simpler than Unix - with a couple of teletype terminals.
I found a [video of a refurbished PDP8/e driving a teletype](https://www.youtube.com/watch?v=2B-U-5ylvWo).
Fun.
-->
