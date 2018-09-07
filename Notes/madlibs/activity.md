---
layout: page
title: Activity - Mad Libs
---

Extend [madlibs.c]({{site.examples}}/madlib.c) to print out the resulting story when translation is finished (and successful).
It might be nice to print a blank line and a row of dashes so the story is nicely set off from the prompts & answers in the first phase of the program.

You should write a new function `printFile(FILE *fp)` that simply copies characters from the input file (already open for reading as `fp`) to stdout.
`main` can thus open the file and call this function.

I anticipate this function will be only 2-3 lines long!

Remember how you can get a copy into your own directory:

```
cd
cd cs50
cp ~cs50/examples/madlib.c .
cp ~cs50/examples/readline.[ch] .
cp ~cs50/examples/madlib*.txt .
```
