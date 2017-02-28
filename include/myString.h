#ifndef __MULLINSN_MYSTRING__
#define __MULLINSN_MYSTRING__
/**
 * name: getPos
 * 
 * Accepts a start pos, string and a hook, returns the next position of the hook in the
 * string
 * 
 * in: int, char*, char
 * out: returns the pos of the hook, or -1 if not found
 * post: none
 * Error: invalid string
 **/
 int getPos(int start, char *string, char hook);
 
/**
 * name: subString
 * 
 * Accepts a string and and 2 ints representing the start and end
 * of what they what copied into the new string
 * 
 * in: char*, char*, int, int
 * out: the substring
 * post: will put the newString into char* newString
 * Error: start must be 0 <= start < length
 **/
void subString(char *oldString, char *newString, int start, int end);

/**
 * name: parseNumber
 * 
 * Accepts a string and and an int representing the starting location of the
 * number within the string, returns the number attached to it
 * 
 * in: char*, int
 * out: the integer found
 * post: none
 * Error: start must be 0 <= start < length
 * Error: no number attached will return 0
 **/
int parseNumber(char* string, int start);
#endif
