/*
 * life.c - Conway's Game of Life
 * 
 * Read about the game at https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 * compile with
 *   mygcc life.c -lcurses -o life
 * run with
 *   ./life [startboard.txt]
 * where the optional file has lines of text containing only the letter 'O' 
 * and spaces, and no line longer than the width of the window.
 * 
 * Tap any key to step from one generation to the next.
 * Use ^C to quit.
 * 
 * This program serves as an example of
 *  - the use of the ncurses library (search for CURSES)
 *  - the allocation and use of a 2-dimensional array of char
 *  - the use of fgets() to read lines from a file
 *
 * David Kotz, May 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h> // CURSES

// size of board, initialized to initial window size
static int NROWS;
static int NCOLS;

/* characters representing live and dead cells */
static const char LIVECELL = 'O';
static const char DEADCELL = ' ';

/* Local function prototypes */
static void initialize_curses();
static char **new_board(void);
static void load_simple_board(char **board);
static void load_board(char **board, FILE *fp);
static void display_board(char **board, int generation);
static void evolve(char **now, char **next);
static int numNeighbors(char **now, const int x, const int y);
static int neighbor(char **now, const int x, const int y);


/* ***************** main ********************** */
int
main(int argc, char *argv[])
{
  int generation = 0;	      // count the generations
  FILE *fp = NULL;	      // the file with the initial board

  if (argc > 1) {
    if ( (fp = fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "%s: cannot open '%s'\n", argv[0], argv[1]);
    }
  }

  // initialize curses library
  initialize_curses(); // CURSES

  // initialize and display the board
  char **board1 = new_board();
  if (fp == NULL) {
    load_simple_board(board1);
  } else {
    load_board(board1, fp);
    fclose(fp);
  }
  display_board(board1, generation++);
  getch(); // pause until keystroke // CURSES

  // initialize a second board
  char **board2 = new_board();

  // evolve life forward  
  while(1) {
    // from board1 to board2
    evolve(board1, board2);
    display_board(board2, generation++);
    getch(); // pause until keystroke // CURSES

    // from board2 to board1
    evolve(board2, board1);
    display_board(board1, generation++);
    getch(); // pause until keystroke // CURSES
  }

  endwin(); // CURSES

  // I don't bother to free malloc'd memory because exit is via ^C
}

/* ************ initialize_curses *********************** */
/* 
 * initialize curses // CURSES everywhere in this function
 */
static void 
initialize_curses()
{
  // initialize the screen - which defines LINES and COLS
  initscr();

  // cache the size of the window in our global variables
  NROWS = LINES;
  NCOLS = COLS;

  cbreak(); // actually, this is the default
  noecho(); // don't show the characters users type

  // I like yellow on a black background
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  attron(COLOR_PAIR(1));
}

/* ************ new_board *********************** */
/* 
 * allocate and erase a new board - fill with DEADCELL
 */
static char**
new_board(void)
{
  // allocate a 2-dimensional array of NROWS x NCOLS
  char **board = calloc(NROWS, sizeof(char*));
  char *contents = calloc(NROWS * NCOLS, sizeof(char));
  if (board == NULL || contents == NULL) {
    fprintf(stderr, "cannot allocate memory for board\r\n");
    exit(1);
  }

  // set up the array of pointers, one for each row
  for (int y = 0; y < NROWS; y++) {
    board[y] = contents + y * NCOLS;
  }

  // fill the board with empty cells
  for (int y = 0; y < NROWS; y++) {
    for (int x = 0; x < NCOLS; x++) {
      board[y][x] = DEADCELL;
    }
  }
  return board;
}


/* ************ load_simple_board *********************** */
/* 
 * Load the board with a simple pattern
 */
static void
load_simple_board(char **board)
{
  if (NCOLS >= 4) {
    for (int y = 0; y < NROWS; y++) {
      strncpy(board[y], " OOO", 4);
    }
  }
}

/* ************ load_board *********************** */
/* 
 * Load the board from a file.  All lines in the file should
 * have only DEADCELL or LIVECELL characters. 
 */
static void
load_board(char **board, FILE *fp)
{
  const int size = NCOLS+2;  // include room for \n\0
  char line[size];	      // a line of input
  int y = 0;

  // read each line and copy it to the board
  while ( fgets(line, size, fp) != NULL && y < NROWS) {
    int len = strlen(line);
    if (line[len-1] == '\n') {
      // normal line
      len--; // don't copy the newline
    } else {
      // overly wide line
      len = NCOLS;
      fprintf(stderr, "board line %d too wide for screen; truncated.\r\n", y);
      for (char c = 0; c != '\n' && c != EOF; c = getc(fp))
	; // scan off the excess part of the line
    }
    strncpy(board[y++], line, len);
  }

  if (!feof(fp)) {
    fprintf(stderr, "board too big for screen; truncated to %d lines\r\n", y);
  }
}


/* ************ display_board *********************** */
/* 
 * Display the board onto the screen; notice we just copy all chars 
 * of the board to the screen, then let curses figure out what to paint.
 */
static void
display_board(char **board, int generation)
{
  for (int y = 0; y < NROWS; y++) {
    for (int x = 0; x < NCOLS; x++) {
      move(y,x);	      // CURSES
      addch(board[y][x]);     // CURSES
    }
  }
  mvprintw(0,0, "Generation %d", generation); // CURSES
  refresh();				      // CURSES
}


/* ************ evolve ************** */
/* Produce the next board from the current board,
 * according to the rules:
 *
 * Every cell interacts with its eight neighbours, which are the cells
 * that are horizontally, vertically, or diagonally adjacent. At each
 * step in time, the following transitions occur:
 *
 * Any live cell with fewer than two live neighbours dies, as if caused
 * by underpopulation.
 *
 * Any live cell with two or three live neighbours lives on to the next
 * generation.
 *
 * Any live cell with more than three live neighbours dies, as if by
 * overpopulation.
 *
 * Any dead cell with exactly three live neighbours becomes a live cell,
 * as if by reproduction.
 *
 * From https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules
 */
static void
evolve(char **now, char **next)
{
  // Compute a new cell value for every cell, by counting its neighors
  // and following the above rules.
  for (int y = 0; y < NROWS; y++) {
    for (int x = 0; x < NCOLS; x++) {
      int neighbors = numNeighbors(now, y, x);
      if (now[y][x] == LIVECELL) {
	// cell currently live
	if (neighbors < 2 || neighbors > 3) {
	  next[y][x] = DEADCELL;
	} else {
	  next[y][x] = LIVECELL;
	}
      } else {
	// cell currently empty
	if (neighbors == 3) {
	  next[y][x] = LIVECELL;
	} else {
	  next[y][x] = DEADCELL;
	}
      }
    }
  }
}

/* ************** numNeighbors *************** */
/* 
 * Return the count of neighbors for this cell, 
 * respecting the boundaries of the board.
 */
static int
numNeighbors(char **now, const int y, const int x)
{
  return 
    neighbor(now, y-1, x-1) + // above left
    neighbor(now, y-1, x-0) + // above 
    neighbor(now, y-1, x+1) + // above right
    neighbor(now, y-0, x-1) + // left
    neighbor(now, y-0, x+1) + // right
    neighbor(now, y+1, x-1) + // below left
    neighbor(now, y+1, x-0) + // below
    neighbor(now, y+1, x+1);  // below right
}

// return 0 or 1, whether there is a neighbor at the given position
static int
neighbor(char **now, const int y, const int x)
{
  if (y < 0 || y >= NROWS || x < 0 || x >= NCOLS) {
    return 0; // out of bounds; implicitly no neighbor
  } else {
    if (now[y][x] == LIVECELL) {
      return 1; // neighbor!
    } else {
      return 0; // no neighbor
    }
  }
}
