#include "myString.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/* Reused from A1
 * accepts a string and a section, copies everything from that section into newString
 */
void subString(char *oldString, char *newString, int start, int end)
{
    if (oldString == NULL || newString == NULL)
    {
        printf("NULL variable detected");
        return;
    }
    
    int loop = 0;
    for (int a = start; a <= end; a++, loop++)
    {
        newString[loop] = oldString[a];
    }
}

/* Reused from A1
 * Accepts a string and a character and return the position of the first occurence
 */
int getPos(int start, char *string, char hook)
{
    if (string == NULL)
    {
        printf("NULL variable detected");
        return -1;
    }
    
    int strLen = strlen(string);
    int a = 0;
    int b = -1;
    //loop through the string
    for (a = start; a < strLen; a++)
    {
        //Found the char
        if (string[a] == hook)
        {
            b = a;
            break;
        }
    }
    return b;
}
//Accepts a string and the starting point of the number, returns the number attached 
//will improve it some other time TODO
int parseNumber(char* string, int start)
{
    char number[32];
    int a = start;
    int num = 0;
    int multi = 1;
    
    memset(number, 0, 32);
    
    //loop while there is another digit to be read
    while (isdigit(string[a]))
    {
        number[a-start] = string[a];
        a++;
    }
    //reverse their order
    for (a=a-start-1; a >= 0; a--)
    {
        num += multi*(number[a] - '0');
        multi *= 10;
    }
    return num;
}
