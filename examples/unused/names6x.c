/* 
 * names.c - read in a list of names from stdin
 *   (sorted linked list - but then remove duplicates)
 *
 * usage: names < infile
 * stdin: list of names, one per line
 * stdout: numbered list of names, one per line
 * 
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"

// A structure for each node in linked list
struct listnode {
  char *name;
  struct listnode *next;
};

char *trunchar(char *p, char c);
bool listInsert(struct listnode *head, char *name);
struct listnode *newNode(char *name);
void freeNode(struct listnode *node);


int main()
{
  struct listnode head = {NULL, NULL}; // dummy node at head of empty list
  const int lineLength = 50;       // maximum length of a name
  char line[lineLength];           // buffer for reading lines
  int n = 0;		           // number of names read

  // read the list of names
  while (!feof(stdin))
    if (readline(line, lineLength))
      if (listInsert(&head, trunchar(line, '.')))
	n++; // only increment if no error

  // remove duplicates from list
  for (struct listnode *node = head.next; node != NULL; )
    if (node->next != NULL && strcmp(node->name, node->next->name) == 0) {
      // duplicate detected; remove node->next from list
      struct listnode *duplicate = node->next;
      node->next = node->next->next;
      freeNode(duplicate);
      n--;
    } else {
      // only advance when we do not find a duplicate
      node = node->next;
    }

  printf("%d names: ", n);
  // print the list of names
  for (struct listnode *node = head.next; node != NULL; node = node->next)
    printf("%s ", node->name);
  putchar('\n');
}


// trunchar:  truncate string at given character; 
// return the original string pointer as convenience.
char *trunchar(char *s, char c)
{
  char *p = s;
  while (*p != '\0' && *p != c)
    p++; // skip ahead until . is found
  *p = '\0'; // truncate
  
  return s; // the original string
}


// listInsert: insert the given name into the list
// return true if success, false if failure.
bool listInsert(struct listnode *head, char *name) 
{
  struct listnode *node = newNode(name);

  if (head == NULL || node == NULL)
    return false;
  else {
    // insert the new node at alphabetical place in list
    struct listnode *place = head;
    // slide along the list to the right place
    while (place->next != NULL && strcmp(name, place->next->name) > 0)
      place = place->next;
    // On exit, place points at last item on the list, or 
    // place points at a middle item, but new name comes before place->next.
    // Thus, we want to insert 'node' after place and before place->next.
    node->next = place->next;
    place->next = node;
  }
  return true;
}


// newNode: create a new node to store the given name.
// returns pointer to new node, if successful,
// else returns NULL.
struct listnode *newNode(char *name) 
{
  // allocate memory for the new node
  struct listnode *node = malloc(sizeof(struct listnode));
  
  if (node == NULL)
    return NULL;
  else {
    // initialize node contents
    node->next = NULL;
    node->name = malloc(strlen(name)+1);
    if (node->name == NULL) {
      // clean up and return failure
      free(node);
      return NULL;
    } else 
      // store the name in the node
      strcpy(node->name, name);
  }

  return node;
}


// freeNode: delete memory for the given node
void freeNode(struct listnode *node)
{
  if (node != NULL) {
    if (node->name != NULL)
      free(node->name);
    free(node);
  }
}
