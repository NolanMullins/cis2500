#include "room.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "myString.h"
#include "struct.h"

#define MAX_STRING 256

Room* loadRoom(char* line, Hero* atGuy, int roomNum, Room** rooms)
{
    int pos = 0;
    int len = strlen(line);
    int dimension[2];
    
    int doorNum = 0;
    int itemNum = 0;
    int monsterNum = 0;
    
    Room* newRoom = malloc(sizeof(Room));

    if (newRoom == NULL)
    {
        printf("Memory Error\n");
        exit(0);
    }
    //init all door pointers to NULL
    for (int a = 0; a < 6; a++)
    {
        newRoom->doors[a] = NULL;
    }
    //init all item and monster pointers to NULL
    for (int a = 0; a < 10; a++)
    {
        newRoom->items[a] = NULL;
        newRoom->monsters[a] = NULL;
    }

    //loop through the line
    while (pos < len && line[pos] != '\n')
    {
        //Move through the spaces if there are extra
        while (line[pos] == ' ')
        {
            pos++;
        }
        
        //Check if its the dimensions
        if (isdigit(line[pos]))
        {
            dimension[0] = 0;
            dimension[1] = 1;
            //loop through the digits
            for (int a = 1; a >= 0; a--)
            {
                dimension[a] = parseNumber(line, pos);
                pos++;
                //2 digit num
                if (dimension[a]>9)
                    pos++;
                //Skip the X
                pos++;
            }
        }
        //its an item
        else
        {
            int nextSpace = getPos(pos, line, ' ');
            //Check if there are no more spaces
            if (nextSpace < 0)
            {
                nextSpace = getPos(pos, line, '\n');
                if (nextSpace < 0)
                {
                    nextSpace = len;
                }
            }
            
            //substring out the data chunk
            char sec[MAX_STRING];
            memset(sec, 0, MAX_STRING);
            subString(line, sec, pos, nextSpace-1);
            
            int x,y;
            char type = sec[0];
            //door
            if (type == 'd')
            {
                int num = parseNumber(sec, 2);
                //which side of the wall its on
                switch (sec[1])
                {
                    //north
                    case 'n':
                        x = num;
                        y = 0;
                    break;
                    //south
                    case 's':
                        x = num;
                        y = dimension[1]+1;
                    break;
                    //east
                    case 'e':
                        x = dimension[0]+1;
                        y = num;
                    break;
                    //west
                    case 'w':
                        x = 0;
                        y = num;
                    break;
                }
                //store a new door in the room
                newRoom->doors[doorNum] = createDoor(x, y, sec[1]);
                doorNum++;
            }
            //item
            else
            {
                y = parseNumber(sec, 1);
                x = parseNumber(sec, getPos(1, sec, ',')+1);
                //check against hero
                if (type != 'h')
                {
                    //if weak monster randomly generate it
                    if (type == 'm')
                    {
                        switch (rand()%4)
                        {
                            case 0:
                                type = 'A';
                                break;
                            case 1:
                                type = 'B';
                                break;
                            case 2:
                                type = 'S';
                                break;
                            case 3:
                                type = 'Z';
                                break;
                        }
                        //create a new monster
                        newRoom->monsters[monsterNum] = createMonster(x,y,type);
                        monsterNum++;
                    }
                    else if (type == 'M')
                    {
                        type = 'T';
                        //create a new monster
                        newRoom->monsters[monsterNum] = createMonster(x,y,type);
                        monsterNum++;
                    }
                    else
                    {
                        //check that the gold value hasnt been used
                        int value = 0;
                        if (type == 'g' || type == 'G')
                        {
                            value = getGoldValue(rooms, newRoom, type, 0);
                        }
                        else if (type == 'w')
                        {
							value = rand()%9+1;
						}
						else if (type == 'W')
						{
							value = rand()%6+10;
						}
						else if (type == 'e')
						{
							value = rand()%21;
						}
                        //add item to room
                        newRoom->items[itemNum] = createItem(type, x, y, value);
                        itemNum++;
                    }
                } else {
                    //init hero
                    atGuy->x = x;
                    atGuy->y = y;
                    atGuy->gold = 0;
                    atGuy->roomNum = roomNum;
                }
            }
            pos = nextSpace;
        }
    }
    
    newRoom->width = dimension[0]+2;
    newRoom->height = dimension[1]+2;
    
    return newRoom;
}



Door* createDoor(int x, int y, char side)
{
    Door* newDoor = malloc(sizeof(Door));
    if (newDoor == NULL)
    {
        printf("Memory error");
        exit(0);
    }
    newDoor->x = x;
    newDoor->y = y;
    newDoor->side = side;
    return newDoor;
}

Item* createItem(char type, int x, int y, int value)
{
    Item* newItem = malloc(sizeof(Item));
    newItem->type = type;
    newItem->x = x; 
    newItem->y = y;
    newItem->value = value;
    return newItem;
}

int getGoldValue(Room** rooms, Room* thisRoom, char type, int loopNum)
{
    //block an infinite loop
    if (loopNum > 500)
        return 0;
    //random assign a value
    int value = 0;
    if(type == 'g')
    {
        value = rand()%51;
    }
    else
    {
        value = rand() % 200 + 50;
    }
    int a = 0;
    //check if its been used
    while (rooms[a] != NULL)
    {
        int b = 0;
        //loop through items in the room
        while (rooms[a]->items[b] != NULL)
        {
            //check for equal value
            if (rooms[a]->items[b]->value == value && rooms[a]->items[b]->type == type)
                return getGoldValue(rooms, thisRoom, type, loopNum+1);
                
            b++;
        }
        a++;
    }
    a = 0;
    while(thisRoom->items[a] != NULL)
    {
        //check for equal value
        if (thisRoom->items[a]->value == value)
            return getGoldValue(rooms, thisRoom, type, loopNum+1);
                
        a++;
    }
    return value;
}

Monster* createMonster(int x, int y, char type)
{
    Monster* scaryGuy = malloc(sizeof(Monster));
    if (scaryGuy == NULL)
    {
        printf("Mem error");
        exit(0);
    }

    //set monster stats
    scaryGuy->x = x;
    scaryGuy->y = y;
    scaryGuy->isDead=0;

    int health = 0;
    int speed = 0;
    int attack = 5;
    //stats based on monster
    switch (type)
    {
        case 'A':
            health = 5;
            attack = 1;
            speed = 2;
            break;
        case 'B':
            health = 2;
            speed = 4;
            break;
        case 'S':
            health = 5;
            speed = 4;
            break;
        case 'Z':
            health = 15;
            speed = 2;
            break;
        case 'T':
            health = 50;
            speed = 3;
            break;
    }
    //set the rest of the monsters stats
    scaryGuy->health = health;
    scaryGuy->speed = speed;
    scaryGuy->attack = attack;
    scaryGuy->cycle = 0;
    scaryGuy->type = type;
    return scaryGuy;
}
