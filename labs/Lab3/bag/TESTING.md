# CS50 Lab 3
## David Kotz, April 2017

### Testing 'bag'

To test my *bag* module I wrote a test program, [bagtest](bagtest.c), to explore the capabilities of the *bag* data structure and to demonstrate the use of a non-trivial `item` type.

This test program assumes its stdin is a series of lines, each line containing a comma-separated set of information about a given stock (symbol, closing price, current price, and volume); it constructs a structure `item` for each, and inserts that item into the bag.

It then tests some corner cases by calling `bag_insert()` on a variety of special cases.
(In the test results below you'll see that neither of those special cases resulted in the inclusion of new items in the bag.)

It then tests `bag_print()` and `bag_iterate()` with simple printing tasks, and a simple iteration function that just tracks a counter as it passes over the items.

It then tries a `bag_iterate()` with a less trivial `arg` and function showing how one might pass *two* arguments to the iteration function - by rolling them both into a struct.

Finally, I run this test program from the `Makefile` with a dedicated rule run by `make test`.
This rule actually downloads some recent stock prices into a file `stocks` and then passes that file to `bagtest` as input.

### Test run

An example test run is in `bagtest.out`, built with

	make test > bagtest.out

In that file one can see the progress of building a bag, the results of `bag_print`, the results of three different `bag_iterate` tests, and the `stockcount` after `bag_delete`.

### Limitations

I never tested `bag_extract`!
I really should write another loop, or another test program, to test the extraction of some items from the bag.

