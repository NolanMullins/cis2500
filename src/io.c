/* Nolan Mullins
 * 0939720
 * 2016 01 24
 * Reused from A1
 */
#include "io.h"
#include <stdio.h>
#include <string.h>

//Will load and return a file
FILE* getFile (char *fileName, char mode)
{
    return fopen(fileName, &mode);
}

//when called will read the next line of the file
int readLine (FILE *file, char *line)
{
    //Check if there is a line to be read
    memset(line, 0, 7);
    if (fgets(line, 255, file) != NULL)
    {
        return 0;
    }
    return 1;
}

