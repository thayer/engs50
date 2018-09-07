---
layout: page
title: Memory and pointers - paper exercise
---

In class we worked through the [scores]({{site.examples}}/scores) example.
I handed out [scoresheet.c]({{site.examples}}/scores/scoresheet.c) and asked you to fill in the blanks.

We then looked at the full program, [scores1.c]({{site.examples}}/scores/scores1.c).
This program demonstrates

 * allocating and constructing a linked list, in which the list nodes contain structs.
 * scanning a linked list
 * allocating and filling an array of structs
 * deleting a linked list

We then wondered how we might modify it to use an array of pointers instead of an array of structs, resulting in [scores2.c]({{site.examples}}/scores/scores2.c).
This program demonstrates

 * allocating and constructing list nodes that have *pointers* to structs.
 * allocating and filling an array of struct *pointers*

See the [differences]({{site.examples}}/scores/diffs12.txt) between scores1 and scores2.

See the [output]({{site.examples}}/scores/testing.txt) of both programs.
