/* 
 * Scores - load sport scores into a table.
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

// represents a game between team 1 and team 2
struct game {
  char *team1, *team2;	      // names of each team
  int score1, score2;	      // score for each team
};

// node in a list of games
struct gamenode {
  struct game game;	      // this game
  _____________________;      // link to next game
};

// array of games, and the number of games
_____________games;
int gamecount;

// prototypes (should be in reader.h but I include them here for you to see)
// Read a string from the stdin and return pointer to new string;
// caller is responsible to later free that string.
// Assume this function always succeeds.
char *readstring();

// Read an integer from the stdin and return that value.
// Assume this function always succeeds.
int readint();

int main()
{
  struct gamenode headnode;	     // dummy node at the head
  struct gamenode *head = &headnode; // pointer to the current head
  struct gamenode *node;	     // an element in the list

  // Initialization code:

  // read from stdin and build a linked list
  while (!feof(stdin)) {
    // allocate a new node
    node = 

    // initialize the new node using readstring() and readint() 







    // link the new node into list





    // keep track of the number of games
    gamecount++;
  }

  // allocate an array to hold all the games
  games = ___________________________________

  // loop over all games, to add them to the new array
  int i = gamecount;
  for (
    games[--i] = 
  }

  // print the array of games
  for (
    printf("%s (%d) vs. %s (%d)\n", 
	   games[i].team1, games[i].score1, games[i].team2, games[i].score2);
  }

  // free the list
  for (







  }

}

/* For each of the following pointer variables, identify where that variable 
 * lives (static, stack, heap), and where it points to (static, stack, heap).
 *
 * games
 * headnode
 * head
 * node
 * team1, team2
 * score1, score2
 */
