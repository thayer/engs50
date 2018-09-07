### Lab 4 

Before releasing the TSE starter kit, consider purging the earlier commits from the [TSE-starter repo](https://gitlab.cs.dartmouth.edu/CS50/tse/commits/master), especially if you desire to provide *less* code than what has been provided before.  Keep in mind that students fork and clone this repo and thus get the full commit history!

* in particular, it's possible that some or all of the Lab3 solutions, or a different mixture of starter-provided files, might have been distributed in the Lab4 starter kit.

* clone the [TSE-starter repo](https://gitlab.cs.dartmouth.edu/CS50/tse/) into a directory `tse-starter` that is a peer to `tse-solution`; this arrangement will make it easier to use the scripts that export subsets of the solution into the starter.

* run `tse-solution/export-starter4` to copy a fresh starter over top of the existing starter kit.  commit and push.  make sure the Gitlab copy of the repo contains exactly the set of files you plan to distribute.

Remember to add all grad and ugrad TAs as "Reporter" member of [TSE solution](https://gitlab.cs.dartmouth.edu/CS50/tse-solution/settings/members) repo.  Remove membership from TAs no longer involved.

Consider changes:

* update spec about parameters: seedURL must be an 'internal' URL.

* remove the side-effect of `IsInternalURL` - which currently causes a `NormalizeURL`.  not immediately clear how best to change it, but it would be cleaner and less confusing.

* reconsider the API for `getNextWord` and `getNextURL`; maybe they would be better like this:

```c
char *webpage_getNextWord(webpage_t *page, int *pos);
char *webpage_getNextURL(webpage_t *page, int *pos);
```

* replace `checkp` with `assertp` in webpage.c

* require logging output, like that with my APPTEST flag? it helps them debug, and it helps us grade.  if logging is required, be clear about what to log and what not to log.

* reconsider the behavior of `webpage_new()` - it copies the URL string but not the HTML string.  Better behavior would be to copy neither - but say they must both be malloc'd space and caller agrees to let webpage_delete() later free both.

* change spec: the pageDirectory should exist and *be empty of files*, or perhaps should *not exist* prior to the run.  Filling an existing directory with new files could lead to confusion if the current run produces fewer files than an earlier run of crawler.  This year I told them it was the responsibility of the user to provide a clean directory.

* update spec: what should crawler do if there is an error creating a file, or writing to a file, in the pageDirectory. (my solution aborts, but an alternative would be to log the error and continue.)

* update spec: what should the crawler do if it encounters an error in webpage_fetch?  (my solution logs an error and continues, which should be the required behavior.)

* update spec: should there be a maximum allowable value for `maxDepth` parameter?  spec does not specify, but my solution imposes one.

* update lab instructions, or insert more lecture material prior to Lab4, and provide examples, so they know more about Makefiles and how to use `-I` flags and libraries like `-lcurl` and `.a` files. Those are needed to compile crawler, but I had not really shown them those tricks in depth.

* remove dependency on `libcurl`; it has memory-leak issues.  in the current version of the course they do not use the library, and we wrap it transparently with `webpage_fetch`; thus, we could just rewrite `webpage_fetch` with the necessary networking code to fetch pages with http and drop use of `libcurl` entirely.  Such a move would also then allow `webpage_fetch` to be brought back inside `webpage.c`, eliminating `webpage_internal.h`.

* I gave them my compiled crawler, and sample output. I made the mistake of leaving that in `~cs50/demo` but I should have put the output in `~cs50/data`, to be consistent with the intent of the latter directory and to keep `demo` clean for use in other class demos.  (I tended to empty it after every class so it could be a clean place for a new class demo.)

* I suggested the use of a Makefile in `common/` but did not *require* it and that led to grading inconsistencies.  Just require it.

* the rubric requires `common/Makefile` if `common/` exists, but the spec does not specifically require the Makefile.  better to make the lab require `common` and its Makefile, or not mention it at all. these 'optional' features cause grading headaches.
