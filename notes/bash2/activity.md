---
layout: page
title: Activity - shell pipelines
---

## Billboard Hot 100 (2016)

Let's play with the [Billboard Hot 100 from 2016](http://www.billboard.com/charts/year-end/2016/hot-100-songs), which I extracted into a text file.

Write pipelines to find out

1. sort the list to start at 100 and countdown to 1
2. how many song titles mention ``love''?
3. how many artists are in the top 100?
4. which artist had the most hits in top 100?

Some useful commands:

```bash
$ BB=~cs50/public_html/Lectures/bash2/Billboard2016-hot100.txt
$ less $BB
$ cut -d : -f 3 $BB | less
$ wc -l $BB
```

<!--
### solutions

```bash
1. sort -nr $BB
2. cut -d : -f 2 $BB | grep -i love | wc -l
3. cut -d : -f 3 $BB | sort -u | wc -l
4. cut -d : -f 3 $BB | sort | uniq -c | sort -nr | head
```
-->
