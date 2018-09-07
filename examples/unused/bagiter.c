/* 
 * bagtest.c - test program for simple bag module
 *
 * usage:
 *   read stock quotes from stdin to use as test data.
 * each line should be comma-separated values, with 
 *  "symbol",previousClose,price,volume
 * where previousClose and price are floats, and volume is integer.
 * for example, pipe the output of curl into this program:
 *  curl 'http://download.finance.yahoo.com/d/quotes.csv?s=NKE,AAPL,MCD,TWTR,IBM,YHOO,ORCL,GOOG,MSFT,NFLX,FB&f=spl1v&e=.csv' | ./bagtest
 *
 * David Kotz, April 2016, updated May 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "readline.h"

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

static void simpleprint(void *arg, void *data);
static void bagcount(void *arg, void *data);
static void stockgainloss(void *arg, void *data);
static void stockprint(FILE *fp, void *data);
static void stockdelete(void *data);
static int stockcount = 0;


int main() 
{
  bag_t *bag;		      // the bag

  bag = bag_new(stockprint, stockdelete);
  if (bag == NULL) {
    printf("bag_new failed\n");
    exit(1);
  }

  printf("\ntesting bag_insert:\n");
  // read stocks from stdin and insert each into the bag
  while (!feof(stdin)) {
    struct stock *stp = malloc(sizeof(struct stock));

    if (stp == NULL) {
      printf("out of memory for stocks\n");
    } else {
      // crude parsing of the input line, each with format:
      // "symbol",previousClose,price,volume
      char line[100];
      if (readline(line, 100)) {
	// I can't use sscanf with %s to pick out the stock symbol,
	// so let's first pick out the numbers after the first comma:
	char *numbers = strchr(line, ','); // find first comma
	sscanf(numbers, ",%f,%f,%d\n", 
	       &stp->close, &stp->price, &stp->volume);
	// then let's get the symbol from between the quotation marks:
	char *symbol = line+1; // skip the first quotation mark
	char *end = strchr(symbol, '"'); // find next quotation mark
	*end = '\0'; // truncate from that mark onward
	strcpy(stp->symbol, symbol);
	// insert into bag, using the symbol as key
	bag_insert(bag, stp);
	stockcount++;
	printf("Loaded: "); stockprint(stdout, stp); putchar('\n');
      } else
	free(stp);
    }
  }

  // test with null bag, null data
  bag_insert(NULL, NULL);
  bag_insert(bag, NULL);

  printf("\nThe bag:\n");
  bag_print(stdout, bag);
  printf("\n");

  printf("\nSimpleprint:\n");
  bag_iterate(bag, simpleprint, stdout);
  printf("\n");

  printf("\nCount: ");
  int nitems = 0;
  bag_iterate(bag, bagcount, &nitems);
  printf("%d\n", nitems);

  printf("\nChanges: ");
  struct gainloss changes = {0,0};
  bag_iterate(bag, stockgainloss, &changes);
  printf("gainers: %d; losers: %d\n", changes.ngainers, changes.nlosers);

  printf("\ndelete the bag...\n");
  bag_delete(bag);
  printf("done, with %d stocks still allocated\n", stockcount);
}


/* print the given data to the given file;
 * just print the stock symbol
 */
static void 
simpleprint(void *arg, void *data)
{
  FILE *fp = arg;
  struct stock *stp = data;

  if (fp != NULL && stp != NULL)
    fprintf(fp, "%s ", stp->symbol);
}

/* count the non-null items in the bag.
 * note here we don't care what kind of data is in bag.
 */
static void 
bagcount(void *arg, void *data)
{
  int *nitems = arg;

  if (nitems != NULL && data != NULL)
    (*nitems)++;
}

/* count the number of gainers and losers.
 */
static void 
stockgainloss(void *arg, void *data)
{
  struct gainloss *gl = arg;
  struct stock *stp = data;

  if (gl != NULL && stp != NULL) {
    if (stp->price > stp->close)
      gl->ngainers++;
    if (stp->price < stp->close)
      gl->nlosers++;
  }
}


/* print the given data to the given file;
 * print the stock symbol, close, price, and volume..
 */
static void 
stockprint(FILE *fp, void *data)
{
  struct stock *stp = data;
  if (stp == NULL)
    fprintf(fp, "[(null)]");
  else 
    fprintf(fp, "[%s: close %f, price %f, vol %d]", 
	    stp->symbol, stp->close, stp->price, stp->volume);
}

static void 
stockdelete(void *data)
{
  if (data) {
    free(data);
    stockcount--;
  }
}

