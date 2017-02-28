#ifndef MULLINS_LOAD
#define MULLINS_LOAD

/**
 * name: loadMap
 * 
 * Purpose: take the game information and stor in into a 2d array 
 * 
 * in: Room**, Hero*, int*, int*
 * out: char**
 * post: will edit the mapW and mapH to the size of the returned array
 * Error: anything null
 **/
char** loadMap(Room** rooms, Hero* atGuy, int* mapW, int* mapH);

/**
 * name: addRoom
 * 
 * Purpose: add a room to the map
 * 
 * in: Room*, char**, Hero*, int,int,int
 * out: void
 * post: will edit the map and the room*
 * Error: anything null, incorrect rX, and rY or roomNum
 **/
void addRoom(Room* myRoom, char** map, Hero* atGuy, int rX, int rY, int roomNum);

/**
 * name: setHalls
 * 
 * Purpose: add halls to the map
 * 
 * in: Room**, char**, int,int,int,int,int
 * out: void
 * post: will edit the map to have halls in it
 * Error: -ve buffers, bad midY, null Room** or null map
 **/
void setHalls(Room** rooms, char** map, int width, int height, int buffer, int bufferMid, int midY);

/**
 * name: drawHall
 * 
 * Purpose: draw an indavidual section of a hall
 * 
 * in: 
 * out: map**, int, int,int,int
 * post: will edit the map
 * Error: null map**, -ve cor or outofbounds cor
 **/
void drawHall(char** map, int x1, int y1, int x2, int y2);

/**
 * name: checkLR
 * 
 * Purpose: checks if the variable is greater than the right or less then the left
 * 
 * in: int,int*,int*
 * out: void
 * post: will edit the left or right variable accordingly
 * Error: null variables
 **/
void checkLR(int x, int* left, int* right);

/**
 * name: abs
 * 
 * Purpose: return the absolute of the input
 * 
 * in: int
 * out: int
 * post: none
 * Error: input must be valid integer
 **/
int abs(int num);

/**
 * name: swap
 * 
 * Purpose: swap 2 variables values
 * 
 * in: int*, int*
 * out: void
 * post: will swwap their values
 * Error: null variables
 **/
void swap(int* a, int* b);
#endif
