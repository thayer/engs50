/* 
 * fntable - a demonstration of function tables used for command dispatch.
 * 
 * A function dispatch table makes it possible to write a small code 
 * loop that calls one of the functions in the table, depending on some 
 * tidbit of information - in this case, a short command string.
 * 
 * David Kotz, May 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

/**************** functions ****************/
static void fn_get(char *rest_of_line);
static void fn_put(char *rest_of_line);
static void fn_hello(char *rest_of_line);
static void fn_goodbye(char *rest_of_line);

/**************** function dispatch table ****************/

static const struct {
  const char *command;
  void (*func)(char *rest_of_line);
} dispatch[] = {
  { "GET", fn_get },
  { "PUT", fn_put },
  { "HELLO", fn_hello },
  { "GOODBYE", fn_goodbye },
  { NULL, NULL }
};

/**************** main ****************/
int main()
{
  char *line;

  // print the list of commands
  printf("Input one of the commands");
  for (int fn = 0; dispatch[fn].command != NULL; fn++)
    printf(", %s", dispatch[fn].command);
  printf(".\n");

  // loop over lines of input
  while ( (line = readlinep(stdin)) != NULL) {
    // break the line at the first space
    char *command = line;
    char *space = index(line, ' ');
    char *rest_of_line;
    if (space == NULL) {
      rest_of_line = NULL;
    } else {
      rest_of_line = space+1;
      *space = '\0';
    }

    // dispatch the appropriate function
    int fn;
    for (fn = 0; dispatch[fn].command != NULL; fn++) {
      if (strcmp(command, dispatch[fn].command) == 0) {
	(*dispatch[fn].func)(rest_of_line);
	break;
      }
    }
    if (dispatch[fn].command == NULL)
      printf("Unknown command: '%s'\n", command);

    free(line);
  }
  
  return 0;
}

/**************** silly functions ****************/

static void fn_get(char *rest_of_line)
{
  printf("ok, you want to GET '%s'\n", rest_of_line);
}

static void fn_put(char *rest_of_line)
{
  printf("ok, you want to PUT '%s'\n", rest_of_line);
}

static void fn_hello(char *rest_of_line)
{
  printf("How's it going? '%s'\n", rest_of_line);
}

static void fn_goodbye(char *rest_of_line)
{
  printf("Goodbye!   '%s'\n", rest_of_line);
}
