/* quickie functions to read string and int from stdin, one per line */

// Read a string from the stdin and return pointer to new string;
// caller is responsible to later free that string.
// Assume this function always succeeds.
char *readstring();

// Read an integer from the stdin and return that value.
// Assume this function always succeeds.
int readint();

