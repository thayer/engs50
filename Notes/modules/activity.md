---
layout: page
title: Activity - Modular data structures in C
---

Grab my classroom demo code,

```
cd ~/cs50
cp ~cs50/demo/names9.c .
cp ~cs50/demo/readlinep.[ch] .
```

and **work in pairs** to modify the *bag* module so it keeps track of the number of items in the bag.
You'll need to modify

* `struct bag`  (to include a counter)
* `bag_new`     (to initialize the counter)
* `bag_insert`  (to increment the counter)
* `bag_extract` (to decrement the counter)
* `bag_print`   (so you can print the counter!)

#### Compiling

```c
mygcc names.c readlinep.c -o names
```
