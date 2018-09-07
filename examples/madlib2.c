/* 
 * madlib2 - plays "Mad Libs" by reading a template and prompting the
 * user for the word substitutions. (madlib2: prints the resulting story.)
 * 
 * usage: madlibs template.txt output.txt
 *   where the file 'template.txt' has substitutable codes enclosed in 
 * angle brackets, e.g., <noun> or <adjective>.  The user is prompted for each,
 * in turn, on stdout, and provides answers on stdin. The translated file
 * is then written to the output file.
 * 
 * assumptions: 
 * 1. the template file is well-formed, that is, brackets are not nested.
 * 2. the <name> enclosed in brackets is short, less than codeLength.
 * 3. the substitution for a code is also short, less than subLength.
 *
 * exit: zero in normal play; non-zero if wrong # args or if errors in 
 * opening/reading/writing files.
 * 
 * David Kotz
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "readline.h"

/* global constants */
const int codeLength = 21;    // maximum length of substitution code
const int subLength = 81;     // maximum length of substitution text

/* function prototypes */
bool fillTemplate(FILE *in, FILE *out);
void printFile(FILE *fp);

/* main */
int main (const int argc, char *argv[]) {
  char *progName = argv[0];   // name of this program
  char *templateFilename;     // template file name
  char *outputFilename;	      // output file name
  FILE *in, *out;	      // input and output files

  // parse arguments
  if (argc != 3) {
    fprintf(stderr, "usage: %s templateFilename outputFilename\n", progName);
    exit(1);
  } else {
    templateFilename = argv[1];
    outputFilename = argv[2];
  }

  // open template file
  if ((in = fopen(templateFilename, "r")) == NULL) {
    fprintf(stderr, "%s: cannot open template file '%s'\n", 
	    progName, templateFilename);
    exit(2);
  }

  // open output file
  if ((out = fopen(outputFilename, "w")) == NULL) {
    fprintf(stderr, "%s: cannot open output file '%s'\n", 
	    progName, outputFilename);
    exit(3);
  }

  // fill the template - and confirm success/failure
  bool success = fillTemplate(in, out);
  fclose(in);
  fclose(out);

  if (success) {
    // open output file for *reading*
    if ((in = fopen(outputFilename, "r")) == NULL) {
      fprintf(stderr, "%s: cannot re-open output file '%s'\n", 
	      progName, outputFilename);
      exit(2);
    }

    printf("\n---------------------------------\n");

    printFile(in);

    exit(0);
  } else {
    printf("error - incomplete Mad Lib in '%s'\n", outputFilename);
    exit(4);
  }
}

/* printFile */
/* printFile:
 * copy characters from the given (already open) file to stdout.
 * returns nothing (hence, "void").
 */
void printFile(FILE *fp)
{
  char c;
  while ((c = fgetc(fp)) != EOF)
    putchar(c);
}


/* fillTemplate - translate the template into full text
 * copying from input file to output file, except:
 * wherever a <codeName> is seen in the input,
 * prompt user for a substitution for each codeName,
 * and outputting their substitution instead of <codeName>.
 * 
 * return True iff the input file was processed completely.
 * non-fatal errors print a warning but continue to process input.
 */
bool fillTemplate(FILE *in, FILE *out)
{
  char c;                        // a character from input
  const char startCode = '<';	 // start of substitution code
  const char endCode = '>';	 // end of substitution code
  char codeName[codeLength];	 // name for a substitution code
  char substitution[subLength];	 // substitution text

  // loop through the characters of input
  while ( (c = fgetc(in)) != EOF) { 
    if (c == startCode) {
      // match! scan input until the close bracket.
      for (int i = 0; i < codeLength; i++) {
	// read char and add to code - or terminate string and break.
	c = fgetc(in);
	if (c == endCode) {
	  codeName[i] = '\0';
	  break;
	} else {
	  codeName[i] = c;
	}
      }

      // did we successfully read the code in the above loop?
      if (c != endCode) { // n.b., this also implies i == codeLength
	// the code name was too long; truncate it
	codeName[codeLength-1] = '\0'; // terminate the string
	printf("code name too long; truncated: '%s'\n", codeName);
	while ( (c = fgetc(in)) != endCode && c != EOF) {
	  ; // scan off the rest of the code
	}
      }

      // prompt for the substitution string
      printf("%s: ", codeName);
      if (!readline(substitution, subLength)) {
	printf("substitution too long, truncated to '%s'\n", substitution);
	// not a fatal error; proceed
      }
      // strip the newline from the string received
      substitution[strlen(substitution)-1] = '\0';
      
      // write the substitution to the output file
      if (fputs(substitution, out) == EOF) {
	// fputs returns EOF on error; this should never happen.
	fprintf(stderr, "output error\n");
	return false;
      }

    } else {
      // mismatch - not start of a code - just output the character
      if (fputc(c, out) == EOF) {
	// fputs returns EOF on error; this should never happen.
	fprintf(stderr, "output error\n");
	return false;
      }
    }
  }

  return feof(in); // true iff we reached EOF on input file
}
