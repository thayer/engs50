/* 
 * enum.c - brief example of enumerated types
 * 
 * David Kotz, May 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// An enumerated type to represent a day of the week;
// including a 'non-day', which can be handy as initialized value.
enum dayOfWeek {Unday, Sunday, 
		Monday, Tuesday, Wednesday, 
		Thursday, Friday, Saturday};

struct {
  char * name;         // name of the day
  enum dayOfWeek day;  // enumerated day
} days[] = {
  { "Sunday", Sunday },
  { "Monday", Monday },
  { "Tuesday", Tuesday },
  { "Wednesday", Wednesday },
  { "Thursday", Thursday },
  { "Friday", Friday },
  { "Saturday", Saturday },
};
const int daysInWeek = 7;

int
main(int argc, char *argv[])
{
  // loop over args
  for (int i = 1; i < argc; i++) {
    char *dayname = argv[i];	  // assume argument is a day name
    enum dayOfWeek today = Unday; // initialize to an unknown day
    for (int j = 0; j < daysInWeek; j++) {
      if (strcasecmp(dayname, days[j].name) == 0) {
	today = days[j].day;
      }
    }

    /* At this point, variable 'today' holds one of the 8 enumerated
     * values in the dayOfWeek type. It's not a string; it's more like
     * an integer, and can be directly compared for equality (==) or used
     * in switch statements.
     */

    printf("%s: ", dayname);

    if (today == Unday) {
      printf("unrecognized day\n"); 
      continue;
    }

    switch (today) {
    case Unday: { break; } // already handled above
    case Sunday:
    case Monday:
    case Tuesday: { 
      printf("First half of the week, get started on the lab!\n"); 
      break;
    }
    case Wednesday:
    case Thursday:
    case Friday: { 
      printf("Second half of the week, better wrap up that lab!\n"); 
      break;
    }
    case Saturday: { 
      printf("Still not finished? submit the lab late...\n"); 
      break;
    }
    }
  }
}

/* An example run:
   $ ./enum Sunday monday wodensday Friday Saturday d-day
   Sunday: First half of the week, get started on the lab!
   monday: First half of the week, get started on the lab!
   wodensday: unrecognized day
   Friday: Second half of the week, better wrap up that lab!
   Saturday: Still not finished? submit the lab late...
   d-day: unrecognized day
 */
