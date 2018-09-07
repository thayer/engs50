/* 
 * subtemplate.c - substitute text into a template file
 * 
 * usage: subtemplate target replacement
 * where:
 *   target is a string to be replaced wherever it appears in the input;
 *   replacement is a filename for file containing replacement text
 * output:
 *   read the stdin, copying it to stdout, but wherever the 
 *   target text is found, replace it with the contents of the 
 *   replacement file.
 * stdin: the input template
 * stdout: the modified template
 * stderr: error messages
 *
 * David Kotz, April 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool fileReadable(const char *filename);
bool putFile(const char *filename);
bool subFile(const char *target, const char *filename);

/**************************************/
int main(const int argc, char *argv[])
{
  char *progname = argv[0];  // the program name
  char *target;              // the target string
  char *replacementFilename; // filename for replacement text

  // process arguments
  if (argc != 3) {
    fprintf(stderr, "usage: %s targetString replacementFilename\n", progname);
    exit(1);
  }

  target = argv[1];
  replacementFilename = argv[2];

  if (!fileReadable(replacementFilename)) {
    fprintf(stderr, "%s: replacement file %s nonexistent or not readable\n", 
	    progname, replacementFilename);
    exit(2);
  }

  if (!subFile(target, replacementFilename)) {
    fprintf(stderr, "%s: some error on input\n", progname);
    exit(3);
  }

  return 0;
}

// return true if the file exists and can be opened for reading
bool fileReadable(const char *filename)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    return false;
  }

  fclose(fp);
  return true;
}

// putFile: print the contents of file named in the argument
// return false if any error.
bool putFile(const char *filename)
{
  char c;   // a character from file
  bool eof; // true if EOF reached, false if error
  FILE *fp; // the file, once open for reading

  // open the file for reading
  if ( (fp = fopen(filename, "r")) == NULL) {
    return false;
  }

  // read and print characters until EOF reached, or error
  while ((c = fgetc(fp)) != EOF) {
    putchar(c);
  }

  eof = feof(fp);  // false if some kind of error occurred

  // don't forget to close the file
  fclose(fp);
  return eof;
}


// subFile: print the contents of the stdin, but wherever string
// 'target' appears, print instead the contents of the file named 'filename'
bool subFile(const char *target, const char *filename)
{
  char c;                // a character from stdin
  const char *expect = target; // the next target character we expect

  // loop through the characters of stdin
  while ( (c = getchar()) != EOF) {
    if (c == *expect) {
      // match! expect the next character
      expect++; 
      // if we reached the end of target
      if (*expect == '\0') {
	// copy the given file to stdout; if any error, return now.
	if (!putFile(filename)) {
	  return false;
	}
	// reset our expectation to the beginning of target
	expect = target;
      }
    } else {
      // mismatch: copy any partial match
      for (const char *t = target; t < expect; t++) {
	putchar(*t);
      }
      // then copy new unmatched character to stdout...
      putchar(c);
      // then reset expectation
      expect = target;
    }
  }

  if (feof(stdin)) {
    // EOF: copy any partial match
    for (const char *t = target; t < expect; t++) {
      putchar(*t);
    }
    return true;
  } else {
    // error of some kind
    return false;
  }
}
