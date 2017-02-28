#ifndef __MULLINSN_GAME__
#define __MULLINSN_GAME__
#include <stdbool.h>

/**
 * name: display2s
 * 
 * Purpose: display the game
 * 
 * in: The map
 * out: displays the rooms and player
 * post: will change the screen
 * Error: Has to be 6 rooms
 **/
void display2(char** map, int width, int height, Hero* atGuy, char* eventbar, Room** rooms);

/**
 * name: movePlayer
 * 
 * Purpose: accepts keyboard input then checks if the player can move
 * there if so then moves them
 * 
 * in: char, Room**, Hero*
 * out: new location for the player
 * post: will edit the hero, monster and items in the game (mainly the cordinates and stats of the objects)
 * will also edit the map
 * Error: could segfault if incorrect pointers are passed, must have 6 rooms
 **/
void movePlayer(char input, Room** rooms, Hero* atGuy, char** map, char* eventBar, int mapW, int mapH);

/*
 * name: moveMonsters
 *
 * purpose: Will accept the world data and update the monsters
 *
 * in: Room** , Hero*, char**, char*
 * out: updated monsters
 * post: will edit the data within the monsters and hero
 * error: more or less than 6 rooms
 */
void moveMonsters(Room** rooms, Hero* player, char** map, char* eventBar);

/*
 * name: makeMonsterMove
 *
 * purpose: take an idividual monster and update it
 *
 * in: char, char**, Hero*, Monster*, Room*, char*
 * out: updated monster and hero
 * post: will edit the monster and hero stats
 * error: direction but be either n,s,e,w
 */
void makeMonsterMove(char dir, char** map, Hero* player, Monster* myMonster, Room* room, char* eventBar);

/**
 * name: endGame
 * 
 * Purpose: ends the game
 * 
 * in: Room**, Hero*
 * out: how much gold the player gathered, and free RAM
 * post: will free all memory sent to it, then de init ncurses
 * Error: ncurses must be open
 **/
void endGame(Room** rooms, Hero* atGuy, char** map, int width, int height);

/**
 * name: checkHitDoor
 * 
 * Purpose: checks if the hero hit a door
 * 
 * in: Room*, int, int
 * out: bool
 * post: none
 * Error: no doors in the room
 **/
bool checkHitDoor(Room* myRoom, int newX, int newY);

/**
 * name: checkHitItem
 * 
 * Purpose: checks if the hero hit an item
 * 
 * in: Room*, int, int, Hero*, char**, char*
 * out: int
 * post: will edit the stats of the Hero, will edit the eventBar
 * Error: null map
 **/
int checkHitItem(Room* myRoom, int newX, int newY, Hero* atGuy, char** map, char* eventBar);

/**
 * name: hitItem
 * 
 * Purpose: performs the collision action between the hero and the item
 *  
 * in: Hero*, Item*, char**, char* 
 * out: int will be 2 if stairs r hit and the game needs to be ended
 * post: Will edit the stats of the hero, item and eventbar
 * Error: anything null
 **/
int hitItem(Hero* atGuy, Item* myItem, char** map, char* Eventbar);

/**
 * name: usePotion
 * 
 * Purpose: Will try to use a potion
 * 
 * in: Hero*, char*
 * out: void
 * post: will edit the health of the hero and the eventBar
 * Error: anything null
 **/
void usePotion(Hero* player, char* eventBar);

/**
 * name: attackPlayer
 * 
 * Purpose: monster attacks the player
 * 
 * in: Hero*, Monster*, char*
 * out: void
 * post: will edit the players health or attack, will also edit eventbar
 * Error: anything null
 **/
void attackPlayer(Hero* player, Monster* scott, char* eventBar);

/**
 * name: attackMonster
 * 
 * Purpose: player attacks monster
 * 
 * in: Hero*, Monster*, char*
 * out: void
 * post: Will edit the health of the monster and the eventBar
 * Error: anything null
 **/
void attackMonster(Hero* player, Monster* scott, char* eventBar);

#endif
