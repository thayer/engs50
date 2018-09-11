/* 
 * Code fragments for discussion of cohesion and coupling.
 * 
 * David Kotz - May 2017 
 * adapted from C++ code used in CS23, January 1996
 */

// pseudo-code from a calendar/datebook application

typedef struct date date_t;
typedef struct calendar calendar_t;
typedef struct event event_t;

// given one date, compute the next date;
// account for leap years, etc.
date_t *date_next(date_t *day);

// compute the number of days from "this" date until "that" date
int date_ComputeDaysUntil(const date_t *this, const date_t *that);

// return current date
date_t *date_today(void);

// print calendar
void calendar_print1(calendar_t *cal)
{
  // print the month name
  // print the day names 
  // for each row, print the dates in that row
}

// print calendar
void calendar_print2(calendar_t *cal, int which, date_t *day) 
{
  // if which==1 
  //   print the month name
  //   print the day names 
  //   for each row, print the dates in that row
  // else if which==2
  //   print the month name, day name, and day number
  //   print the events occurring on that day
}

// print calendar
void calendar_print3(calendar_t *cal)
{
  // print the month name, day name, and day number
  // foreach event occurring on that day
  //   print the time of the event
  //   print the type of event
  //   print the description of the event
}

void DoPrintBook(calendar_t *cal, const char *intro,
		 image_t *frontCover, image_t *backCover)
{
  // print the frontCover
  // print the intro
  // foreach month
  //   foreach day of that month
  //     calendar_print2(cal, 2, day);
  // print the backCover
}

calendar_t theCalendar;      // the calendar we use below

void Initialize(string filename, window_t *window)
{
  // initialize theCalendar
  // for each event read from the file
  //   add event to the calendar
  // initialize the window
  // create some buttons on the window
  // current date =  Today()
  // display the current day in window
  // look for any events in the next hour
  //    pop up dialog box for each such event 
  // Update(cal, window);
}

void Update(date_t *today, window_t *window)
{
  // check the current time
  // look through theCalendar.eventlist for events on date "today"
  //   if some events are now in the past, change their state to "past"
  //   update today's events on the window
}



