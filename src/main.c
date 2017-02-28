#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "io.h"
#include "room.h"
#include "game.h"
#include "struct.h"
#include "load.h"
#include <string.h>

#define MAX_STRING 256

int main(int argc, char *argv[])
{
    //check for a file
    if (argc == 1)
    {
        printf("Give me a file\n");
        exit(0);
    }
    
    //seed randum number generator
    srand(time(NULL));
    
    //create variables for map objects
    Room* rooms[6];
    Hero* atGuy = malloc(sizeof(Hero));
    
    if (atGuy == NULL)
    {
        printf("Memory Error\n");
        exit(0);
    }
    //create space in memory for items
    for (int a = 0; a < 5; a++)
    {
        atGuy->items[a] = malloc(sizeof(Item));
        if (atGuy->items[a] == NULL)
        {
            printf("Memory Error");
            exit(0);
        }
        atGuy->items[a]->isEmpty=0;
    }
    //init hero
    atGuy->x=1;
    atGuy->y=1;
    atGuy->potions = 0;
    atGuy->numItems = 0;
    atGuy->attack = 5;
    atGuy->health = 50;
   	//just to make sure
    for (int a = 0; a < 6; a++)
    {
        rooms[a] = NULL;
    }

    //LOAD
    printf("Test");
    FILE* dataFile = NULL;
    dataFile = getFile(argv[1], 'r');
    
    char line[MAX_STRING];

    int a = 0;
    
    //load the rooms
    while (readLine(dataFile, line) == 0)
    {
        rooms[a] = loadRoom(line, atGuy, a, rooms);
        a++;
    }
    
    fclose(dataFile);
    
    int mapW = 0;
    int mapH = 0;
    
    //init game

    //load the data into the map
    char** map = loadMap(rooms, atGuy, &mapW, &mapH);
    char eventBar[256];
    strcpy(eventBar, "Welcome");
    initscr();

    //hide cursor
    curs_set(0);
    noecho();   
 
    //display the game
    //display(rooms, atGuy);
    display2(map, mapW, mapH, atGuy, eventBar, rooms);
    
    char userMove = 'a';
    move(0,0);
    //start the game loop
    while (userMove != 'q')
    {
    	//clear the event bar
        sprintf(eventBar, " ");
        userMove = getch();

        //if they use a potion
        if (userMove == 'p')
        {
			usePotion(atGuy, eventBar);
		}
        else
        {
        	//normal turn
            movePlayer(userMove, rooms, atGuy, map, eventBar, mapW, mapH);
        }
        
        //move the monsters
        moveMonsters(rooms, atGuy, map, eventBar);
           	if (atGuy -> health <= 0)
           		endGame(rooms, atGuy, map, mapW, mapH);

        //display game
        display2(map, mapW, mapH, atGuy, eventBar, rooms);
    }
    
    
    
    //DONT FORGET TO FREE
    //DONT FORGET TO FREE
    //DONT FORGET TO FREE
    //DONT FORGET TO FREE
    //DONT FORGET TO FREE
    
    endGame(rooms, atGuy, map, mapW, mapH);
    
    return 0;
}


