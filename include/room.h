#ifndef __MULLINSN_ROOM__
#define __MULLINSN_ROOM__
#include "struct.h"

/** 
 * door
 * -------------
 * -x : int
 * -y : int
 * -cx : int
 * -cy : int
 * -side : char
 * 
 * +createDoor(int, int, int, int, char)
 **/
typedef struct door
{
	int x;
	int y;
	char side;
}Door;

/** 
 * item
 * -------------
 * -x : int
 * -y : int
 * -type : char
 * -value : int
 * 
 * +createItem(char, int, int, int)
 * */
typedef struct item
{
	int x;
	int y;
	char type;
	int value;
	
	int isEmpty;
}Item;

/** 
 * room
 * -------------
 * -width : int
 * -height : int
 * -doors : char
 * -loadRoom(char*, Hero*, int)
 * */
typedef struct room
{
    int x;
    int y;

	int width;
	int height;
	
	Door* doors[6];
	Item* items[10];
	Monster* monsters[10];
}Room;

/**
 * name: loadRoom
 * 
 * Purpose: given a line of text, load the room into a struct
 * 
 * in: char*, Hero*, int, Rooms**
 * out: Room*
 * post: may edit he Hero values
 * Error: width and height must come before the doors on the line
 **/
Room* loadRoom(char* line, Hero* atGuy, int roomNum, Room** rooms);

/**
 * name: createDoor
 * 
 * Purpose: accepts door data and returns a pointer to a new struct
 * 
 * in: int, int, int, int char
 * out: a pointer to a new door struct
 * post: new dynamic memory, must be freed
 * Error: if malloc goofs then rip
 **/
Door* createDoor(int x, int y, char side);

/**
 * name: createItem
 * 
 * Purpose: accepts item data then returns an item struct
 * 
 * in: char, int, int, int
 * out: a pointer to an item
 * post: new dynamic memory, must be freed
 * Error: if malloc goofs then rip
 **/
Item* createItem(char type, int x, int y, int value);

/**
 * name: getGoldValue
 * 
 * Purpose: makes sure the gold value hasnt been assigned
 * 
 * in: Room**, Room*, char
 * out: unused gold value
 * post: none
 * Error: if too many gold pieces in play
 **/
int getGoldValue(Room** rooms, Room* thisRoom, char type, int loopNum);

/**
 * name: createMonster
 * 
 * Purpose: return space in memory for a Monster
 * 
 * in: int, int, char
 * out: Monster*
 * post: new dynamic memory in use (must be freed)
 * Error: if malloc dies
 **/
Monster* createMonster(int x, int y, char type);
#endif
