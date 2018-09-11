---
layout: page
title: TSE Querier
---

### Goals

There are three mini lectures today.

* to introduce the TSE Querier
* to learn another form of testing: *fuzz testing*
* to learn about expressions and operator precedence

* TOC
{:toc}

## the Querier

The third component of the Tiny Search Engine is the *Querier*, which reads the index produced by the Indexer and the page files produced by the Crawler, to interactively answer written queries entered by the user.

Our Querier loads the index into memory (a data structure we developed for the Indexer) and then prompts the user for queries.
Queries are comprised of words, with optional `and`/`or` operators.
For example,

```
computer science
computer and science
computer or science
baseball or basketball or ultimate frisbee
```

The first two examples are treated identically, matching only documents that have *both* words - not necessarily together (as in the phrase "computer science").
The third picks up documents that have *either* word.
The fourth matches documents that mention baseball, or basketball, or both "ultimate" and the word "frisbee" (not necessarily together).

Here's an example run, with the output truncated a bit:

```
$  querier/querier data/cs50-3 data/cs50-index3
KEY WORDs:> computer and science
Query: computer and science 
Matches 139 documents (ranked):
score 141 doc  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
score 135 doc 349: http://old-www.cs.dartmouth.edu/~dfk/papers/index-t.html
score 135 doc 348: http://old-www.cs.dartmouth.edu/~dfk/papers/index-a.html
score 135 doc 347: http://old-www.cs.dartmouth.edu/~dfk/papers/index-c.html
score  10 doc  11: http://old-www.cs.dartmouth.edu/~dfk/armada/
score   4 doc   9: http://old-www.cs.dartmouth.edu/~dfk/people.html
score   4 doc   7: http://old-www.cs.dartmouth.edu/~dfk/teaching.html
score   3 doc 206: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/deshpande-thesis.html
score   3 doc 167: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/nanda-thesis.html
score   3 doc  18: http://old-www.cs.dartmouth.edu/~dfk/index.html
...
KEY WORDs:> tiny search engine
Query: tiny search engine 
No documents match.
-----------------------------------------------
KEY WORDs:> TSE
Query: tse 
No documents match.
-----------------------------------------------
KEY WORDs:> NOTE we LOWERcase the query first
Query: note we lowercase the query first 
No documents match.
-----------------------------------------------
KEY WORDs:>  spaces      do    not    mattter
Query: spaces do not mattter 
No documents match.
-----------------------------------------------
KEY WORDs:> non-letter characters are disallowed
Error: bad character '-' in query.
KEY WORDs:> even digits as in cs50
Error: bad character '5' in query.
KEY WORDs:> and
Query: and 
Error: 'and' cannot be first
KEY WORDs:> or
Query: or 
Error: 'or' cannot be first
KEY WORDs:> what about and
Query: what about and 
Error: 'and' cannot be last
KEY WORDs:> friend and foe
Query: friend and foe 
No documents match.
-----------------------------------------------
KEY WORDs:> quit
Query: quit 
No documents match.
-----------------------------------------------
KEY WORDs:> exit
Query: exit 
Matches 1 documents (ranked):
score   3 doc   3: http://old-www.cs.dartmouth.edu/~dfk/visit-dartmouth.html
-----------------------------------------------
KEY WORDs:> ^D
```


Let's study the [Requirements Spec]({{site.labs}}/Lab6/REQUIREMENTS.html) for the Querier, and run some demos.

Today's demo scripts are here: [script1](script1.txt) and [script2](script2.txt).

## Fuzz Testing

In a recent lecture we talked about *unit testing*, and the difference between *glass-box testing* and *black-box testing*.
Usually, these tests are based on a carefully constructed series of test cases, devised to test all code sequences and push on the "edge cases".

However, such tests are only as good as the test writer - who must logically study the code (for glass-box testing) or the specs (for black-box testing) to think of the suitable test cases.
It's possible they will miss some important cases.

Another solution, therefore, is ***fuzz testing***, a form of black-box testing in which you fire thousands of random inputs at the program to see how it reacts.
The chances of triggering an unconsidered test case is far greater if you try a lot of cases!

Here is a fuzz-testing program for our *querier*.
It generates a series of random queries on stdout, which it then pipes to the querier on stdin.
Here's the core of the fuzz tester:

```c
/**************** generate_query ****************/
/* generate one random query and print to stdout.
 * pull random words from the wordlist and from the dictionary.
 */
static void
generate_query(const wordlist_t *wordlist, const wordlist_t *dictionary)
{
  // some parameters that affect query generation
  const int max_words = 6;        // generate 1..max_words
  const float or_probability = 0.3;   // P(OR between two words)
  const float and_probability = 0.2;  // P(AND between two words)
  const float dict_probability = 0.2; // P(draw from dict instead of wordlist)

  int qwords = random() % max_words + 1; // number of words in query
  for (int qw = 0; qw < qwords; qw++) {
    // draw a word either dictionary or wordlist
    if ((random() % 100) < (dict_probability * 100)) {
      printf("%s ", dictionary->words[random() % dictionary->nwords]);
    } else {
      printf("%s ", wordlist->words[random() % wordlist->nwords]);
    }

    // last word?
    if (qw < qwords-1) {
      // which operator to print?
      int op = random() % 100;
      if (op < (and_probability * 100)) {
        printf("AND ");
      }
      else if (op < (and_probability * 100 + or_probability * 100)) {
        printf("OR ");
      }
    }
  }
  printf("\n");
}
```

With the following setup,

```bash
$ cd tse
$ mkdir data/cs50-3
$ crawler/crawler http://old-www.cs.dartmouth.edu/~cs50/ data/cs50-3 3
$ indexer/indexer data/cs50-3 data/cs50-index3
```

And here's the output of 10 random queries:

```bash
$ querier/fuzzquery 
usage: querier/fuzzquery indexFile numQueries randomSeed
$ querier/fuzzquery data/cs50-index3 10 0
querier/fuzzquery: generating 10 queries from 5586 words
captured AND despite
pcs OR frontiers activityaware OR relay tour 
unix downloading OR pre 
triactine pieces colgate OR aspects OR wine-wise OR direx 
uncompressed OR early taxonomy austrian AND jewelry OR manages 
once forced odame localization OR marsch 
comparison 
suffer desires OR workflow 
facilitated 
garth OR yang OR cardiac AND ruslan AND synthetic 
```

And here's what happens when we pipe it to our querier (output abbreviated a little):

```
$ querier/fuzzquery data/cs50-index3 10 0 | querier/querier data/cs50-3 data/cs50-index3
querier/fuzzquery: generating 10 queries from 5586 words
KEY WORDs:> Query: captured and despite 
No documents match.
-----------------------------------------------
KEY WORDs:> Query: pcs or frontiers activityaware or relay tour 
Matches 39 documents (ranked):
score  37 doc 349: http://old-www.cs.dartmouth.edu/~dfk/papers/index-t.html
score  37 doc 348: http://old-www.cs.dartmouth.edu/~dfk/papers/index-a.html
score  37 doc 347: http://old-www.cs.dartmouth.edu/~dfk/papers/index-c.html
score  37 doc  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
score   2 doc  53: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/oldfield-app-pario.html
...
-----------------------------------------------
KEY WORDs:> Query: unix downloading or pre 
Matches 1 documents (ranked):
score   1 doc 104: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/khanna-group.html
-----------------------------------------------
KEY WORDs:> Error: bad character '-' in query.
KEY WORDs:> Query: uncompressed or early taxonomy austrian and jewelry or manages 
Matches 3 documents (ranked):
score   2 doc  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
score   1 doc  81: http://old-www.cs.dartmouth.edu/~dfk/STARFISH/
score   1 doc  67: http://old-www.cs.dartmouth.edu/~dfk/RAPID-Transit.html
-----------------------------------------------
KEY WORDs:> Query: once forced odame localization or marsch 
Matches 5 documents (ranked):
score   2 doc  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
score   1 doc 316: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/anthony-sith3.html
score   1 doc 349: http://old-www.cs.dartmouth.edu/~dfk/papers/index-t.html
score   1 doc 348: http://old-www.cs.dartmouth.edu/~dfk/papers/index-a.html
score   1 doc 347: http://old-www.cs.dartmouth.edu/~dfk/papers/index-c.html
-----------------------------------------------
KEY WORDs:> Query: comparison 
Matches 11 documents (ranked):
score   3 doc 349: http://old-www.cs.dartmouth.edu/~dfk/papers/index-t.html
score   3 doc 348: http://old-www.cs.dartmouth.edu/~dfk/papers/index-a.html
score   3 doc 347: http://old-www.cs.dartmouth.edu/~dfk/papers/index-c.html
...
-----------------------------------------------
KEY WORDs:> Query: suffer desires or workflow 
Matches 1 documents (ranked):
score   1 doc 336: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/mare-thesis.html
-----------------------------------------------
KEY WORDs:> Query: facilitated 
Matches 2 documents (ranked):
score   1 doc 260: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/chen-fusenet.html
score   1 doc 180: http://old-www.cs.dartmouth.edu/~dfk/papers/abstracts/tan-crf-s3.html
-----------------------------------------------
KEY WORDs:> Query: garth or yang or cardiac and ruslan and synthetic 
Matches 3 documents (ranked):
score   1 doc  19: http://old-www.cs.dartmouth.edu/~dfk/papers/index.html
score   1 doc  90: http://old-www.cs.dartmouth.edu/~dfk/charisma/
score   1 doc   9: http://old-www.cs.dartmouth.edu/~dfk/people.html
-----------------------------------------------
```

We could generate a different series of random queries by changing the random seed, and we can run a lot more queries, too!

```
$ querier/fuzzquery data/cs50-index3 10 999 | querier/querier data/cs50-3 data/cs50-index3 > /dev/null
querier/fuzzquery: generating 10 queries from 5586 words
$ querier/fuzzquery data/cs50-index3 10000 999 | querier/querier data/cs50-3 data/cs50-index3
querier/fuzzquery: generating 10000 queries from 5586 words
```

The fuzz tester does not test *all* aspects of the querier; in particular, it will not generate syntactically incorrect inputs.
Those should be tested by another program, perhaps another fuzz tester.
Furthermore, it does not verify whether the querier actually produces the right answers!

For regression testing, we might save the querier output in a file, and then compare the output of a fresh test run against the saved results from earlier runs.
If we had earlier believed those results to be correct, then seeing unchanged output would presumably indicate the results (and thus the new code) are still correct.

## Expressions and accumulators {#expressions}

Thinking ahead to the querier, let's think about how one evaluates an expression involving operators.
We'll work with an arithmetic analogy.

### Arithmetic expressions

Consider the following arithmetic expression:

```c
sum = a + b + c + d
```

Since addition is a *left-associative* operator, this means the same thing as

```c
sum = (((a + b) + c) + d)
```

This means we can scan the expression from left to right, accumulating a sum as we go, effectively like this:

```c
sum = 0
sum = sum + a
sum = sum + b
sum = sum + c
sum = sum + d
```

Here, the `sum` acts as an *accumulator*.
(Indeed, many early hardware architectures include an explicit register called an 'accumulator'.)

We often see this approach generalized in code:

```c
int n = 5;
int array[n] = {42, 34, 12, -5, 19};
int sum = 0;
for (int i = 0; i < n; i++)
	sum += array[i];
printf("sum = %d; average = %f\n", sum, (float) sum / n);
```

### Precedence

What if you have a mixture of operators, with precedence?

Consider the following arithmetic expression:

```c
sum = a + b * c + d
```

Both addition and multiplication are *left-associative* operators, but multiplication has precedence over addition.
Thus, we implicitly rewrite the above expression as follows:

```c
sum = ((a + (b * c)) + d)
```

or, in sequence,

```c
sum = 0
sum = sum + a 
prod = 1
prod = prod * b
prod = prod * c
sum = sum + prod
sum = sum + d
```

Notice how we 'step aside' from the sum for a moment while we compute the product `b * c` ... using an exactly analogous process.  `prod` is an accumulator for the product; it is initialized to the *multiplicative identity* (1) instead of the *additive identity* (0), for reasons I hope are obvious.
But then we just multiply in each of the successive items, one at a time.

This generalizes to longer expressions like

```c
sum = a * b + c * d * e + f + g * h * i
```

becomes

```c
sum = 0
prod = 1
prod = prod * a
prod = prod * b
sum = sum + prod
prod = 1
prod = prod * c
prod = prod * d
prod = prod * e
sum = sum + prod
prod = 1
prod = prod * f
sum = sum + prod
prod = 1
prod = prod * g
prod = prod * h
prod = prod * i
sum = sum + prod
```

Let's add some indentation to make this a little easier to read:

```c
sum = 0
	prod = 1
	prod = prod * a
	prod = prod * b
sum = sum + prod
	prod = 1
	prod = prod * c
	prod = prod * d
	prod = prod * e
sum = sum + prod
	prod = 1
	prod = prod * f
sum = sum + prod
	prod = 1
	prod = prod * g
	prod = prod * h
	prod = prod * i
sum = sum + prod
```

Notice what I did with `f`, and that I *never add anything to `sum` other than `prod`*.

This structure should give you a hint about how you might write code to evaluate such expressions...
if you have a `product` function to scan the expression left to right from a given starting point, accumulating a product of individual items until it sees a `+` or the end of the expression, you can then write a function `sum` that scans the expression left to right from the start, accumulating a sum of products by calling `product` at the start and after each `+`.

## Activity

In today's [activity](activity.html) your group will discuss how the above ideas relate to `and` an `or` operators in a query expression.
