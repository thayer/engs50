
### Lab 3

 * consider adding `const` to function parameters where appropriate

 * change `counters_add` to return an int, the new value of that counter.
This allows one to test whether the counter just added was a new counter (return value 1).
It could return 0 on error?
	 * this would be useful in a crawler that is built using a bag and counters instead of a bag and hashtable.

 * switch the order of `set` and `counters` in the lab description, so `counters` comes first.
it is easier to implement and it may be cleaner to have `set` next to the `hashtable`, which is related.

 * consider changing `counters_set` to return bool so it can return false instead of ignoring errors.
 * consider making the *counters* module use `unsigned int count` and `unsigned int key`

 * remove the library build from the top-level Makefile
 * remove(?) the 'starter' target from the top-level Makefile - use a script instead - so that code doesn't propagate to the starter kit's Makefile.

 * write `README.md` and `TESTING.md` for each of the subdirectories, so they can be released as part of the solution.

 * back-port improvements to `memory` and `jhash`, and other files from the tse-solution, to lab3/solution, Lab3/starter, and examples/.

 * develop a cleaner mechanism to keep the multiple copies of the data-structure code synchronized:
	 * admin/labs/lab3/solution
	 * Labs/Lab3/starter
	 * tse-starter repo
	 * tse-solution repo
