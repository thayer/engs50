---
layout: page
title: Bugs & Testing
---

### Goals

In this lecture we talk about bugs and introduce the art of testing.

* types of bugs
* the difference between *debugging* and *testing*
* when and why to test
* various approaches to testing

But first, let's talk about bugs.

## Bugs

> From *[Fighting Bugs: Remove, Retry, Replicate, and Rejuvenate](http://www5.in.tum.de/~huckle/FightingBugs.pdf)*, by Grottke and Trivedi.

***Bohr bugs***.
Most bugs are reproducible.
They always occur under the same set(s) of circumstances.
These have been described as *Bohr bugs*, in reference to the simple atomic model of Niels Bohr that brought consistency and predictability to the study of physics at the atomic level.

***Mandelbugs***.
However, bugs don't always cooperate.
It's a common experience to have bugs "disappear" every time you try to show it to someone else, only to return later after the other person has left.

There could be many explanations.
G&T mentioned several: (1) varying error-propagation delay and (2) variations in systems outside your software, such as variations in the compiler (and its configuration), user account configuration, operating system (and its configuration), network connection (or unreliability of said connection), to analog or sensor hardware (which sometime has non-deterministic behavior), or variations in the physical environment (for software that senses or interacts with the real world).

Bugs that don't appear to be the result of a logical chain of events are sometimes called *Mandelbugs* (after Benoit Mandelbrot, a leading mathematician known for his work on Fractals).

***Heisenbugs***.
A subset of Mandelbugs are the *Heisenbugs*, named after Werner Heisenberg's Uncertainty Principle.
These also result in chaotic or unpredictable behavior, but they are a little tougher to figure out because their behavior can change when you try to examine them.
Prime examples of Heisenbugs are some timing problems and others where the very act of probing the bug can introduce side effects.

***Bit rot***.
Finally, there are aging-related bugs, also referred to as *bit rot*.
Systems that run for a long time can eventually suffer a failure due to these slow-effect bugs.
They are usually BohrBugs, since they are repeatable, but they are seldom found in testing due to the long duration before they cause trouble.
(Example: Slow memory leaks.) These are the bugs that are most often handled by establishing policies for a schedule on which applications or computers are periodically restarted even when all seems well.
This practice doesn't come without a cost, especially if you think of the personnel time required to do it and the inconvenience to system users/customers.

Another form of bit rot occurs to software that needs to live for years, spanning many generations of the underlying software and hardware.
A program that compiles today may not compile next year, because of changes in the include files or libraries, and even the compiler.
Even if it compiles, it may not run properly, because of changes in the underlying operating system or its configuration, changes in the hardware if the system has migrated to a new server, or changes in the surrounding environment (such as remote servers to which the software needs to connect).

### Three motivational anecdotes

#### Proven program found to have a bug 20 years later

> adapted from Joshua Bloch's [blog](http://bit.ly/FMKax).

Jon Bentley (Author of *Programming Pearls* and other books) observed that a relatively simple piece of code for a binary sort that he had proven to be correct during a lecture at CMU had a bug in it that wasn't discovered until 20 years later.
Here's the code:

```c
    1:     int binarySearch(int[] a, int length, int key) {
    2:         int low = 0, mid, midVal;
    3:         int high = length - 1;
    4:
    5:         while (low <= high) {
    6:             mid = (low + high) / 2;
    7:             midVal = a[mid];
    8:
    9:             if (midVal < key)
    10:                 low = mid + 1
    11:             else if (midVal > key)
    12:                 high = mid - 1;
    13:             else
    14:                 return mid; // key found
    15:         }
    16:         return -(low + 1);  // key not found.
    17:     }
```

The bug was found to be in line 6:

```c
    6:             mid = (low + high) / 2;
```

This looks correct, since it's purpose is to find the average of `low` and `high`, rounded down to the nearest integer.
However, if the sum of `low` and `high` exceed the maximum signed int value (`2^31-1` on some architectures), the sum goes negative and the resulting value for `mid` is also.

So how would you fix it?
The following would work:

```c
    6:             mid = low + ((high-low) / 2);
```

#### Missile system looking in the wrong place

From the February 1992 GAO report to the House of Representatives' Subcommittee on Investigations and Oversight, Committee on Science, Space, and Technology:

> *On February 25, 1991, a Patriot missile defense system operating at Dhahran, Saudi Arabia, during Operation Desert Storm failed to track and intercept an incoming Scud.
> This Scud subsequently hit an Army barracks, killing 28 Americans. ...
>  The Patriot battery at Dhahran failed to track and intercept the Scud missile because of a software problem in the system's weapons control computer.
> This problem led to an inaccurate tracking calculation that became worse the longer the system operated.
> At the time of the incident, the battery had been operating continuously for over 100 hours.
> By then, the inaccuracy was serious enough to cause the system to look in the wrong place for the incoming Scud. ...
>  The Patriot had never before been used to defend against Scud missiles nor was it expected to operate continuously for long periods of time.
> Two weeks before the incident, Army officials received Israeli data indicating some loss in accuracy after the system had been running for 8 consecutive hours.
> Consequently, Army officials modified the software to improve the system's accuracy.
> However, the modified software did not reach Dhahran until February 26, 1991--the day after the Scud incident.*

The problem was that in order to predict where an incoming missile *would be*, the system needed its velocity and the time expressed as real numbers to do the calculations.
Unfortunately, the time was maintained as an integer representing the number of tenths of a second since the system began operating.
The problem was that the longer it was running, the larger the error would be when converting the integer time into a real number.
Thus, the Patriot was looking "in the wrong place."

#### Apple SSL Bug example

Sometimes software updates add new bugs that wouldn't be caught without running all the tests again.
Here's an example from February 2014 in Apple MacOS X and iOS where hackers could trick those systems into accepting SSL (TLS) certificates that should be rejected.

```c
    . . .
    hashOut.data = hashes + SSL_MD5_DIGEST_LEN;
    hashOut.length = SSL_SHA1_DIGEST_LEN;
    if ((err = SSLFreeBuffer(&hashCtx)) != 0)
        goto fail;
    if ((err = ReadyHash(&SSLHashSHA1, &hashCtx)) != 0)
        goto fail;
    if ((err = SSLHashSHA1.update(&hashCtx, &clientRandom)) != 0)
        goto fail;
    if ((err = SSLHashSHA1.update(&hashCtx, &serverRandom)) != 0)
        goto fail;
    if ((err = SSLHashSHA1.update(&hashCtx, &signedParams)) != 0)
        goto fail;
        goto fail;  /* MISTAKE! THIS LINE SHOULD NOT BE HERE */
    if ((err = SSLHashSHA1.final(&hashCtx, &hashOut)) != 0)
        goto fail;

    err = sslRawVerify(...);
    . . .
```

Yes, C does have a `goto` statement.
It works as expected, providing an immediate transfer to the specified label.

Here the programmer is verifying the certificate; if any of the checks fail the `err` variable is set non-zero and the code exits to the failure handler.
Unfortunately, the programmer inserted two `goto fail`statements instead of just one.
As a result, even if `err==0` the code transfers to the fail section.
That returned with a return code of `err` which, if `err==0` means success, means the certificate is reported as valid, and ultimately accepted.
This bug could allow website spoofing or the acceptance of a bogus certificate containing a mismatched private key.

This bug was overlooked because the second `goto` is indented - but it is not part of the `if` statement.
Proper use of CS50 style (putting brackets around every code block) would have prevented this bug from manifesting itself!

#### Loss of the Mars Climate Orbiter and Mars Polar Lander

From [Wikipedia](https://en.wikipedia.org/wiki/List_of_software_bugs).

> *NASA Mars Polar Lander was destroyed because its flight software mistook vibrations due to atmospheric turbulence for evidence that the vehicle had landed and shut off the engines 40 meters from the Martian surface.*

> *Its sister spacecraft Mars Climate Orbiter was also destroyed, due to software on the ground generating commands in pound-force (lbf), while the orbiter expected newtons (N).*

#### More examples

 * *[Historical software bugs with extreme consequences](http://royal.pingdom.com/2009/03/19/10-historical-software-bugs-with-extreme-consequences/)*, from a blog
 * *[List of software bugs](https://en.wikipedia.org/wiki/List_of_software_bugs)*, Wikipedia


## Testing

> "Testing can demonstrate the presence of bugs but not their absence."
>  -- Edsger Dijkstra

This quote is a good to keep in mind when you are developing code.
What is the difference between debugging and testing?
You debug when you know or have identified problems in your code.
Testing is the art of systematically trying to break code, which you think (hope?) is bug free.
We test throughout the software life cycle because it is typically much less expensive to fix a bug earlier in the software's life than later.

These CS50 lectures are strongly influenced by *[The Practice of Programming](http://www.amazon.com/Practice-Programming-Addison-Wesley-Professional-Computing/dp/020161586X/ref=pd_bbs_sr_2?ie=UTF8&s=books&qid=1199226460&sr=1-2),* by Brian Kernighan and Rob Pike, an outstanding book that will advance your knowledge on good programming practices.
The notes use a number of programming examples from their Chapter 6 on Testing.

### Kinds of testing

There are many kinds of testing, each with its own purpose:

**Unit testing:**
The goal of unit testing is to verify that each functional unit of the system is working properly.
It's written from the unit developer's perspective, and aims to test the internal workings of the unit.
If this testing isn't done well, *all* of the subsequent testing is more painful, slow, and sometimes meaningless!

**Functional testing:**
The goal of functional testing is to verify that the unit, module, sub-system, or system is doing what its user wants.
For a system, the 'user' is the customer; for a unit, the 'user' may be a developer of other components that depend on this unit.
This testing usually requires "scaffolding" or a "test harness" to exercise the device or unit under test.

> "Unit tests tell a developer that the code is doing things right; functional tests tell a developer that the code is doing the right things." -- Jeff Canna, *[Testing, Fun, Really](http://www.ibm.com/developerworks/library/j-test.html)*.

**Glass-box testing and black-box testing:**
These refer to two types of unit testing (or functional testing).
In *glass-box testing* you can peek inside the thing being tested.
In *black-box testing* you can only access the thing's public API: you can send the box input and see only what comes out of the box.
Both approaches have value, but the former is only useful if you have the source code to the thing being tested.
Unit testing is typically glass-box, whereas functional testing is usually black-box.

**Integration testing:**
After unit testing, the integration test verifies that the units (modules) can communicate properly with each others.
Interfaces defined by the units (modules) are properly implemented and used.
No special channels or connections should be used, even if they make things run faster!

**System testing:**
Also known as "big bang" testing, this is where you put the whole thing together and run tests to ensure that it meets the stated requirements without causing any unexpected side-effects.
  If you skip over the integration tests, you may encounter serious problems in system tests - problems that may be very expensive to fix.
(Consider this example of [unit tests without an integration test](http://giphy.com/gifs/unit-test-integration-3o7rbPDRHIHwbmcOBy)).

**Regression testing:**
Regression testing is an automated means of running (and re-running) unit tests, integration tests, and sometimes system tests, each time you prepare a new release.
(For unit and integration tests, each time you 'git push'!
Indeed, some source-code control systems automatically run unit and integration tests before a commit is accepted, rejecting the commit if any tests fail.)

**Usability testing:**
This is testing with real users.
Not other programmers or engineers, and not friends and neighbors, but the real users.
When this isn't possible, you have to really work hard to find objective testers who will act like the end users.
People who have (or can simulate) the same level of experience, biases, and past experience are the kinds of usability testers you want.

In some products, you must also conduct *accessability testing* to determine whether your software is accessible for people with various disabilities.

**Security testing:**
Security tests verify the security of the system, e.g., to ensure that sensitive data are always encrypted, passwords and credit-card numbers are masked, and sensitive data is securely erased immediately after use.
Sometimes, the team hires outside testers to conduct *penetration tests*, in which the tester tries to break the system or leak sensitive information.
 Unfortunately, one can never prove that a system is 'secure', that is, it has no bugs that lead to the failure of security or privacy properties.
Remember Dijkstra's quote about testing: one can only demonstrate the presence of bugs, not their absence.
This is especially true for security!

**Performance testing:**
Most software needs to perform 'well' according to one or more metrics, whether implicit or explict.
Performance metrics include speed (how long does it take to complete a task), throughput (how many tasks completed per second), memory (code size, stack size, heap usage), network bandwidth, energy (battery drain), or cost (in dollars, such as when using cloud resources billed by usage).
Performance testing subjects the software to various loads, measuring the relevant metrics, to determine whether the system performs within acceptable bounds.

**Acceptance testing:**
The ultimate test: whether the customer accepts your product.
Most of the time these tests are similar to the system tests.
However, you will occasionly encounter new, previously unstated "requirements" during acceptance testing.

Finally, the most important tip of all on testing from The [Pragmatic Programmer](http://pragprog.com/the-pragmatic-programmer/extracts/tips):
> Find bugs once.

Once you or one of your testers (or even a customer) find a bug, that should be the last time a human finds that bug.
Once identified and fixed, your automated tests should be extended to check for that same bug every time they are run.
Finding a bug during regression testing is a lot better than how it was found the first time.

## Tips for Testing

Once again, **the difference between debugging and testing**:

-   **Testing** is a determined, systematic attempt to break a program that you think should be working.
As discussed above, tools and a test harness can automate this process.
-   **Debugging** is what you do when you know that the program crashes (e.g., segfaults), fails (e.g., answers queries incorrecly), underperforms (e.g., runs slowly) or acts inconsistently (e.g., intermittently fails on certain conditions).
These are all bugs that testing can find.
Better to find them and fix them.


### Test Early. Test Often. Test Automatically.

That's a [Pragmatic Programmer Tip](http://pragprog.com/the-pragmatic-programmer/extracts/tips).

We should begin testing as soon as we have something to test (Makefile, parsing arguments, initialization, scaffolding, first units).
The sooner you find your bugs, the cheaper it will be in terms of your time, others' time, and downstream support costs.

[Pragmatic Programmer Tip](http://pragprog.com/the-pragmatic-programmer/extracts/tips):
> The coding ain't done 'til all the tests run.

Furthermore:

-   Code that isn't tested does not work.
-   Code that isn't regression tested eventually stops working.
-   Code that isn't *automatically* regression tested to prove it works, does not work.

Thus, you should build automated testing code (unit tests, Makefile rules, shell scripts, test data) from the very beginning.

### I write bug free code - testing is a waste of time

Many people have the attitude that testing code is a waste of time and boring - why do it?
As Fred Brooks said, "All programmers are optimists"!

Consider the software lifecycle discussed in class: requirements, design, coding, testing, debugging, integration, and delivery.
Professional programmers will tell you that testing and debugging take the largest chunk of time.
Thus, it's smart to *develop tools to automate the testing of code*.

Perhaps the most important tools are for *regression testing*, which systematically retest the code periodically.
Each of those words is important:

 * *retest:* they test older parts of the code even as you develop new parts of the code - just in case your new code broke the old code.
 * *systematic:* they run automatically through a large number of tests, validating the results of each test, so neither carelessness nor laziness causes you to overlook important tests.
 * *periodic:* they run at critical points in the development process; certainly, right before a new release, but in many organizations they run as part of a "nightly build" that compiles and tests the entire system and all of its units.
Woe to the programmer who "breaks the nightly build"!


If all the regression tests pass then you have some confidence that your new code did not introduce additional problems.
A more accurate statement might be "the changes didn't reintroduce any of the bugs that I already knew might exist."

### Write the unit-test code first, and keep it with the object/functions

As Jeff Canna observed, it's best to write the test code *before* you write the real code.
This ensures that you're paying attention to the specifications first, and not just leaping into the code.
When writing these unit tests, try to avoid any testing or dependence on things outside of the unit.
Aim to produce a unit test for *every* function or method that some other code or user will invoke.

### Test as you write code

The earlier you find a problem with your code the better; it will save significant time and your company money.
You will also get respect from other programmers.

I expect most of you sit at the terminal and hack at the code to reveal and fix bugs - you hack in some printfs and run your code again, iterating hundreds of times.
This brute-force method is dumb, slow, and error prone - you'll get no respect in industry for this approach.
Read your code, think like a computer, and write test code as you write the real code.

### Use C idioms and be consistent when you write code

You already know many C idioms even if we haven't always labeled them that way.
In C, there are many ways to write a simple loop:

```c
      // example 1
      i = 0;
      while (i <= n-1)
          array[i++] = 1.0;

      // example 2
      for (i = 0; i < n; )
          array[i++] = 1.0;

      // example 3
      for (i = n; --i >= 0; )
          array[i] = 1.0;
```

As in any human language, C has *idioms*, that is, conventional ways that experienced programmers write common pieces of code.
Idioms aid understanding because they are immediately recognizable and any errors in their use is also quickly discernible.

All of the loops above would work... but they do not follow the C idiom for such loops.
The idiomatic C `for` loop is:

```c
      // Idiomatic form
      for (i = 0; i < n; i++ )
          array[i] = 1.0;
```

Being consistent when programming C will help enormously.
For example, if you are use to writing idiomatic code then when you see a piece of code that is not idiomatic you should stop and take a close look at that code: maybe a boundary problem is more likely?
If code is written the same way each time then when you see code that is not idiomatic it either suggests poor code or some genuine difference exists that the idiom does not cover.
Either way: take a second close look to convince yourself its one or the other.

Here are some more examples of C idioms that you should be familiar with:

```c
      // Infinite loop idioms
      for (;;) {
         ....
      }

      // or

      while (1) {
         ....
      }

      // malloc, string copy idiom
      char *newp = malloc(strlen(buf)+1);
      if (newp != NULL)
      		strcpy(newp, buf);
      else 
      		// handle the malloc error

      // copying characters from stdin to stdout until end of file
      while ((c = getchar()) != EOF)
           putchar(c);

      // traversal of a null-terminated string
      for (char *p=string; *p != '\0'; p++)
          // do something with *p  

```

Write in idioms as much as possible; it makes it easier to spot bugs - and harder to create them.

### Test code at its boundaries

In what follows, we use a series of code snippets from [KP, 1999] to illustrate how to code to remove *boundary bugs*, i.e., those that appear at the 'boundary cases' of a loop or function (sometimes called 'edge cases').
Boundary testing assumes you test a small snippet of code at a time - sort of micro testing of code sequences.
The examples (below) do not use idioms and are poorly written to cater for boundary bugs.
Every time *you* write a loop, verify the boundary cases to ensure the execution goes through the loop the correct number of times.

For example, in the code below we probe the following boundaries:

1. empty input
2. a single input character
3. an exactly full array - but could be a `malloc`'ed buffer.

Consider the following code snippet from [KP, 1999]:

### BOUNDARY TEST: empty line (input with only newline)

```c
      // read characters from stdin into a string
      int i;
      char s[MAX];

      for (i = 0; (s[i] = getchar()) != '\n' && i < MAX-1; ++i)
          ;
      s[--i] = '\0';
```

Looking at this code the first thing that should strike us is that it's not a C idiom.
That should make us look very closely at the loop logic; particularly, the loop's conditional logic.
Maybe, after studying the code and thinking about characters being input we convince ourselves that the code is non idiomatic but works.
Now start to test boundaries.
Consider the case where the user simply types 'return'.
The resulting code would terminate immediately on the first iteration with `i` still set to zero.
Outside the loop, the assignment statement will write to s[i-1], which is *before the start of the array*.
Not a good idea!

### BOUNDARY TEST: empty line (input with only EOF character)

OK. The smart thing to do is rewrite this convoluted loop as an idiom and solve the problem; for example:

```c
      for (i = 0; i < MAX-1; i++) // note we switch ++i => i++, the idiom
           if ((s[i] = getchar()) == '\n')
              break;
      s[i] = '\0';
```

Inspecting the code above we can easily see that the previous boundary problem is solved with the new idiomatic code.
It handles the case when the input is solely a newline beautifully.
If we mentally compute through reading 1, 2 or 3 characters we see it also works; for example `a b c \n` works.

```c
	s[0] is a    s[1] is b    s[2] is c    s[3] is \0
```

Looks good.

But what if we get an empty line and the first character is an `EOF`?
It breaks.
Another pesky bug in our code.
Someone typing control-D (`EOF`) would not be an unlikely occurrence.

OK. Let's fix this boundary bug.

```c
      for (i = 0; i < MAX-1; i++)
           if ((s[i] = getchar()) == '\n' || s[i] == EOF)
              break;
      s[i] = '\0';
```

That works!
Nice piece of code now.
Looks like we are done.

Em... are you sure?
There are other boundary problems that could lurk here.
What happens if the array is nearly full - does it work?
What happens if the array is exactly full?
Or over full?
What happens if the array is full and then followed by a newline?
Are these boundary conditions catered for?
We will leave you to determine the answer to that question.

You get the idea.
Bugs lurk at boundaries.
Conversely, if code works at boundaries it is likely to work elsewhere.

### Break building blocks on purpose

Consider one of your important 'building block' functions.
Now break it!
Have it still operate, but just produce goofy results.
For example, in our TSE programs, suppose the hash function always returned the same hash value?
What would your program do?
Would it run, perhaps more slowly, or would it crash?

Many of you use the`count_malloc()` function to help track the balance of `malloc` and `free` calls.
If you use them for every memory allocation and free, they are a great place to insert debugging code and breakpoints.
They are also a great place for testing!

For example, you could cause it to cause an out-of-memory situation after some number of calls (as suggested by Kernighan and Pike):

```c
// Usage example: gcc -DMEMORYTESTLIMIT=50 ...
void *
count_malloc(size_t size)
{
#ifdef MEMORYTESTLIMIT
  if (nmalloc >= MEMORYTESTLIMIT)
    return NULL; // fake an out-of-memory condition
#endif

  void *ptr = malloc(size);
  if (ptr != NULL)
    nmalloc++;
  return ptr;
}
```

### Test pre- and post-conditions

It is always a good idea to test for pre- and post-conditions: *pre-conditions* are those you expect to be true before some block of code; *post-conditions* are those you expect to be true after some block of code executes.
For example, we have already used defensive program to check input values are with in range - an example of pre-condition testing.
Let's look at another simple example out of [KP, 1999] that computes the average of n elements in an array `a[]`.
Closer inspection of the code reveals that there is a problem if `n` is less than or equal to `0`.

```c
float avg(float a[], int n)
{
  float sum = 0.0;
  for (int i = 0; i < n; i++)
    sum += a[i];
  return sum / n;
}
```

A natural question is what to do if someone calls `avg()` with `n=0`?
An array of zero elements does not make much sense but an average of `0` does.
Should our code catch the division by zero, perhaps with an assert or abort, or complain, or be silent?
One reasonable approach is to just return `0` as the average if `n` is less than or equal to zero.
While the code is idiomatic in style we need to tweak it to test pre-condition, as shown below - note: `return n<=0 ? 0.0 : sum/n;`

```c
double avg(double a[], int n)
{
  if (n <= 0)
    return 0;

  float sum = 0.0;
  for (int i = 0; i < n; i++)
    sum += a[i];
  return sum/n;
}
```

### Use 'assert'

C provides an assertion facility in `assert.h` useful for pre- and post-condition testing.
Asserts are usually used for unexpected failure where there is no clean way to recover the logic control.
For example our above `avg()` function could include a different solution using the assert function:

```c
float avg(float a[], int n)
{
  assert(n > 0);
  float sum = 0.0;
  for (int i = 0; i < n; i++)
    sum += a[i];

  return sum/n;
}
```

If the assertion is in fact violated it will cause an abort and standard message to be printed out:

```
Assertion failed: n > 0, file avgtest.c, line 7 
Abort(crash)
```

Assertions should be used only for testing "this should never happen" kinds of conditions...
other errors, especially those caused by the user, should be handled more gracefully.

We wrote an own `assert` function for use in most of my TSE code;

```c
void *
assertp(void *p, char *message)
{
  if (p == NULL) {
    fprintf(stderr, "MALLOC FAILED: %s\n", message);
    exit (99);
  }
  return p;
}
```

Notice that it acts like a pass-through function, when all is well.
The pointer coming from `malloc` is returned by `assertp` and is saved in the variable.
At that point it is assured to be non-NULL.
When `assertp` receives a NULL pointer, it prints a message to `stderr` and exits.

I use it at the top of most functions to verify that all inbound pointers are not NULL (where NULL is not valid or expected):

```c
  assertp(page, "page_save gets NULL page");
  assertp(page->url, "page_save gets NULL page->url");
  assertp(page->html, "page_save gets NULL page->html");
  assertp(pageDirectory, "page_save gets NULL pageDirectory");
```

### Test for the unexpected: aka, defensive programming

Your crawler and indexer uses defensive programming for checking that the input arguments are logically correct: e.g., that a path actually existed.
But a useful technique when coding is to "expect the unexpected", or code for the unexpected.
Adding checks for `n  < 0` in `avg()` is an example.
Another is below:

```c
  if (grade < 0 || grade > 100)  // can't happen at Dartmouth
    letter = '?';
  else if (grade >= 90)
    letter = 'A';
  else
    ....
```

Other examples include:

1. Out of range subscripts
2. NULL pointers
3. Divide by zero

This is especially important for physical systems.
The controlling software must be aware of the limitations of the physical system.
Otherwise, seeming valid, if perhaps unusual, software interactions could lead to disaster: See [this video](http://www.youtube.com/watch?v=fJyWngDco3g) of the effect of some process control software hacking.


### Plan for automate-able and repeatable tests

K&P recommend that the test output should always contain all of the input parameter settings so that the results can be matched to the parameter settings.
Furthermore, you need to be able to precisely recreate the conditions of that test as accurately as possible.
Some situations complicate this goal.
If your program uses random numbers, you will need some way to set and print the starting seed so that you can ensure the same sequence of random numbers for each test run.
Alternatively, you can have a file of "random" numbers for use during test - the random number function just reads the next one from the file.

Another situation which poses a challenge here is testing in the presence of asynchronous processes.
These could be as simple as a collection of independent and variable length timers or as complicated as a distributed real-time process control system managing the flow of product through a refinery process.


### Always check error returns from functions

A really good programmer will always check the return status from functions, system calls, and libraries.
If you neglect to look at the return status ... how do you know that the function really worked?
If your code assumes it did not fail but it did, then the resulting segfault or error will be hard to debug.
Better to always check the error status returned by functions.

Another example from Kernighan and Pike:

```c
  fp = fopen(outfile, "w");
  if (fp == NULL) {
    // file could not be opened
  }
  while (some expression) {
    fprintf(fp, ...);  // but... what if there is an error?
  }
  if (fclose(fp) == EOF) {
    // some output error occurred
  }
```

The error status of `fprintf` is not checked; what if it fails?
The data written  may have been lost.

### Summary

1. Test incrementally and build confidence in your code.
2. Write unit tests that can be re-run once fixes or changes have been made.
3. Write self-contained unit tests
  * Test inputs and outputs.
  * Test the dataflow through the program.
  * Test all the execution paths through the program.
4. Stress-test the code; start simple and advance (test crawler at depths 1 .. 5 for example).
5. Don't implement new features if there are known bugs in the system.
6. The target runtime environment is as important a design and implementation point as the purpose of the code.
Design *and* test with that environment in mind.
7. Test for portability: run code and tests on multiple machines/OSs.
8. Before shipping code make sure that the any debug/test modes are turned off.

If you follow at least 50% of the tips in these notes you will write better code and it will have considerably fewer bugs.


## Tips from Google


[Google's C++ Testing Frameworks](http://code.google.com/p/googletest/wiki/V1_6_Primer) puts the goals of testing this way (and it's clearly applicable to C programming and unit testing as well as functional and system testing):

-   Tests should be independent and repeatable
-   Tests should be portable and reusable
-   When tests fail, they should provide as much information as possible about the failure
-   The testing framework should handle all the tracking of successful and unsuccessful tests for you
-   Tests should be as fast as possible


## Activity

In today's [activity](activity.html) we will review the feedback from the mid-term survey.
