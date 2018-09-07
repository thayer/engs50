/* 
 * Scores - load sport scores into a table
 *
 * We desire an array containing the scores of many sporting games.
 * Each game is represented by two team names, and score for each team.
 * The problem is, we don't know in advance how many games there are!
 * So we must allocate memory dynamically for the array.
 * 
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reader.h"

// represents a game between team 1 and team 2
struct game {
  char *team1, *team2;	      // names of each team
  int score1, score2;	      // score for each team
};

// node in a list of games
struct gamenode {
  struct game *game;	      // this game
  struct gamenode *next;      // link to next game
};

// array of game pointers, and the number of games
struct game **games;
int gamecount;

int main()
{
  struct gamenode headnode;	     // dummy node at the head
  struct gamenode *head = &headnode; // pointer to the current head
  struct gamenode *node;	     // an element in the list
  headnode.next = NULL;		     // initialize the dummy node
  int gamecount = 0;		     // number of games loaded

  // read from stdin and build a linked list
  while (!feof(stdin)) {
    node = malloc(sizeof(struct gamenode));
    // I am skipping all the error-checking code
    node->game = malloc(sizeof(struct game));
    node->game->team1 = readstring();
    node->game->team2 = readstring();
    node->game->score1 = readint();
    node->game->score2 = readint();
    node->next = head->next;
    head->next = node;
    gamecount++;
  }

  // allocate an array to hold all the games
  games = calloc(gamecount, sizeof(struct game*));
  int i = gamecount;
  for (node = head->next; node != NULL; node = node->next) {
    games[--i] = node->game; // here we copy a game pointer
  }

  // print the array of games
  for (i = 0; i < gamecount; i++) {
    printf("%s (%d) vs. %s (%d)\n", 
	   games[i]->team1, games[i]->score1, games[i]->team2, games[i]->score2);
  }

  // free the list
  for (node = head->next; node != NULL; ) {
    struct gamenode *next = node->next;
    free(node->game->team1);
    free(node->game->team2);
    free(node->game);
    free(node);
    node = next;
  }
  // do not free 'head'

}

