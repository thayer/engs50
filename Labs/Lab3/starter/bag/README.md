# CS50 Lab 3
## David Kotz, April 2017

### bag

A *bag* is an unordered collection of (items).
The bag starts empty, grows as the caller adds one item at a time, and shrinks as the caller extracts one item at a time.
It could be empty, or could contain hundreds of items.
Items are indistinguishable, so the *extract* function is free to return any item from the bag.

### Usage

The *bag* module, defined in `bag.h` and implemented in `bag.c`, implements a bag of `void*`, and exports the following functions through `bag.h`:

```c
/* Create a new (empty) bag; return NULL if error. */
bag_t *bag_new(void);

/* Add new item to the bag; a NULL bag is ignored; a NULL item is ignored. */
void bag_insert(bag_t *bag, void *item);

/* Return any data item from the bag; return NULL if bag is NULL or empty. */
void *bag_extract(bag_t *bag);

/* Print the whole bag; provide the output file and func to print each item.
 * If fp==NULL; do nothing. If bag==NULL, print (null). 
 * If itemprint==NULL, print nothing for each item.
 */
void bag_print(bag_t *bag, FILE *fp, 
	       void (*itemprint)(FILE *fp, void *item));

/* Iterate over the whole bag; call the given function on each item, 
 * passing both the item and an argument. Ignore if NULL bag or NULL itemfunc.
 */
void bag_iterate(bag_t *bag, void *arg,
		 void (*itemfunc)(void *arg, void *item) );

/* Delete the whole bag; ignore NULL bag.
 * Provide a function that will delete each item (may be NULL).
 */
void bag_delete(bag_t *bag, void (*itemdelete)(void *item) );
```

### Implementation

We implement this bag as a linked list.
The *bag* itself is represented as a `struct bag` containing a pointer to the head of the list; the head pointer is NULL when the bag is empty.

Each node in the list is a `struct bagnode`, a type defined internally to the module.
Each bagnode includes a pointer to the `void *item` and a pointer to the next bagnode on the list.

To insert a new item in the bag we create a new bagnode to hold the `item`, and insert it at the head of the list.

To extract an item from the bag we pop off the head of the list and return its item, deleting its bagnode.
Of course, if the list is empty, we return NULL instead.

The `bag_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by scanning the linked list.

The `bag_iterate` method calls the `itemfunc` function on each item by scanning the linked list.

The `bag_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing bagnodes as it proceeds.
It concludes by freeing the `struct bag`.

### Assumptions

No assumptions beyond those that are clear from the spec.

The `item` inserted cannot be NULL, and thus a NULL return from `bag_extract` must indicate either error or empty bag, not simply a NULL `item` coming out of the bag.

Because of the semantics of a *bag*, we have great freedom in our implementation.
Our linked-list approach actually implements a stack: `bag_insert` pushes a new item on the stack, and `bag_extract` pops the top item off the stack.
Other implementations are permitted, but this LIFO list approach is fast and easy to implement.

### Compilation

To compile, simply `make bag.o`.

To test, simply `make test`.
See [TESTING](TESTING.md) for details of testing and an example test run.

Try testing with `MEMTEST` by editing Makefile to turn on that flag and then `make test`.
