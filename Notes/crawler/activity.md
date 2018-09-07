---
layout: page
title: Activity - TSE Crawler
---

### Goals

* to run the *Crawler* over a small website
* to understand how it explores from page to page

### Activity

***One*** person in your group should run my crawler over a little website, at various depths, and try to understand what it's doing.
It's a long command so I broke it over several lines:

```
~cs50/demo/crawler \
  http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html \
  data 0
```

***Another*** person in your group should examine the source files for that website:

```
cd ~cs50/data/tse/letters
less *.html
```

***Another*** person in your group can visit the page in your browser, [here](http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters/index.html).

