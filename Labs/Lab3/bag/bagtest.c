/* 
 * bagtest.c - test program for CS50 bag module
 *
 * usage:
 *   read stock quotes from stdin to use as test data.
 * each line should be comma-separated values, with 
 *  "symbol",close,price,volume
 * where close and price are floats and volume is an int.
 * for example, pipe the output of curl into this program:
 *  curl 'http://download.finance.yahoo.com/d/quotes.csv?s=AAPL,GOOG,MSFT,FB&f=spl1v&e=.csv' | ./bagtest
 * Old documentation about that API:
 *  http://www.financialwisdomforum.org/gummy-stuff/Yahoo-data.htm
 *  http://www.marketindex.com.au/yahoo-finance-api
 *
 * David Kotz, April 2016, 2017
 * 
 * Updated by Rui Liu, Xia Zhou, July 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "readlinep.h"

struct stock {
  char symbol[8];	      // stock symbol, usually 4 chars
  float close;		      // previous close
  float price;		      // last trade price
  int volume;		      // trading volume
};

struct gainloss {
  int ngainers;
  int nlosers;
};

static void simpleprint(void *arg, void *item);
static void itemcount(void *arg, void *item);
static void stockgainloss(void *arg, void *item);
static void stockprint(FILE *fp, void *item);
static void stockdelete(void *item);
static int stockcount = 0;

/* **************************************** */
int main() 
{
  bag_t *bag;		      // the bag
  char *line;		      // a line of input

  bag = bag_new();
  if (bag == NULL) {
    fprintf(stderr, "bag_new failed\n");
    exit(1);
  }

  printf("\ntesting bag_insert:\n");
  // read stocks from stdin and insert each into the bag
  while ( (line = readlinep()) != NULL) {
    struct stock *stp = malloc(sizeof(struct stock));
    if (stp == NULL) {
      fprintf(stderr, "stock new failed\n");
      exit(2);
    }
    sscanf(line, "\"%[^\"]\",%f,%f,%d", stp->symbol, &stp->close, &stp->price, &stp->volume);
    printf("%s,%f,%f,%d\n", stp->symbol, stp->close, stp->price, stp->volume);
    bag_insert(bag, stp);
    stockcount++;
    free(line);
  }

  // test with null bag, null item
  bag_insert(NULL, NULL);
  bag_insert(bag, NULL);

  printf("\nThe bag:\n");
  bag_print(bag, stdout, stockprint);
  printf("\n");

  printf("\nSimpleprint:\n");
  bag_iterate(bag, stdout, simpleprint);
  printf("\n");

  printf("\nCount: ");
  int nitems = 0;
  bag_iterate(bag, &nitems, itemcount);
  printf("%d\n", nitems);

  printf("\nChanges: ");
  struct gainloss changes = {0,0};
  bag_iterate(bag, &changes, stockgainloss);
  printf("gainers: %d; losers: %d\n", changes.ngainers, changes.nlosers);

  printf("\ndelete the bag...\n");
  bag_delete(bag, stockdelete);
  printf("done, with %d stocks still allocated\n", stockcount);
}

/* print the given item to the given file;
 * just print the stock symbol
 */
static void 
simpleprint(void *arg, void *item)
{
  FILE *fp = arg;
  struct stock *stp = item;

  if (fp != NULL && stp != NULL)
    fprintf(fp, "%s ", stp->symbol);
}

/* count the non-null items in the bag.
 * note here we don't care what kind of item is in bag.
 */
static void 
itemcount(void *arg, void *item)
{
  int *nitems = arg;

  if (nitems != NULL && item != NULL)
    (*nitems)++;
}

/* count the number of gainers and losers.
 */
static void 
stockgainloss(void *arg, void *item)
{
  struct gainloss *gl = arg;
  struct stock *stp = item;

  if (gl != NULL && stp != NULL) {
    if (stp->price > stp->close)
      gl->ngainers++;
    if (stp->price < stp->close)
      gl->nlosers++;
  }
}


/* print the given item to the given file;
 * print the stock symbol, close, price, and volume..
 */
static void 
stockprint(FILE *fp, void *item)
{
  struct stock *stp = item;
  if (stp == NULL)
    fprintf(fp, "[(null)]");
  else 
    fprintf(fp, "[%s: close %f, price %f, vol %d]", 
	    stp->symbol, stp->close, stp->price, stp->volume);
}

static void 
stockdelete(void *item)
{
  if (item) {
    free(item);
    stockcount--;
  }
}

