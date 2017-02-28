#ifndef __MULLINSN_IO__
#define __MULLINSN_IO__
#include<stdio.h>

//Reused from A1

/**
 * name: getFile
 * 
 * Accepts a file path and mode character and returns the file
 * 
 * in: char*, char
 * Mode can be 'r' (read), 'w' (write), or 'a' (append)
 * out: returns a pointer to the opened file
 * post: none
 * Error: must pass in a a vaild file path and a vai
 **/
FILE* getFile(char *fileName, char mode);

/**
 * name: readLine
 * 
 * Accepts a FILE and string, then reads in the next line of the file
 * into the string
 * 
 * in: FILE, char*
 * out: returns 0 if succesful or 1 if failed
 * post will edit the line variable
 * Error: Must be an initialized and opened file
 **/
int readLine(FILE *file, char *line);

#endif
