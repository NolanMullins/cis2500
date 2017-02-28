#include "room.h"
#include "game.h"
#include "struct.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define yBound 1

void display2(char** map, int width, int height, Hero* atGuy, char* eventBar, Room** rooms)
{
    int maxX;
    int maxY;
    getmaxyx(stdscr, maxY, maxX);
    //loop through the map
    for (int x = 0; x < width && x < maxX-1; x++)
    {
        for (int y = 0; y < height && y < maxY-yBound; y++)
        {
            //display the tile at cor x,y
            mvaddch(y, x, map[x][y]);
        }
    }
    //if the player is on the screen display them
    if (atGuy->x < maxX-1 && atGuy->y < maxY-yBound)
        mvaddch(atGuy->y, atGuy->x, '@');
    //loop through rooms
    for (int a = 0; a < 6; a++)
    {
        int b = 0;
        while (rooms[a]->monsters[b] != NULL)
        {
            if (rooms[a]->monsters[b]->x < maxX -1 && rooms[a]->monsters[b]->y < maxY - yBound && rooms[a]->monsters[b]->isDead == 0)
                mvaddch(rooms[a]->monsters[b]->y, rooms[a]->monsters[b]->x, rooms[a]->monsters[b]->type);
            b++;
        }
    }
    //print the event bar
    mvprintw(0,0,"%s", eventBar);
    //print out the status bar
    mvprintw(maxY-1, 0, "Health: %d, Potions: %d, Attack: %d, Inv: %d/5", atGuy->health, atGuy->potions, atGuy->attack, atGuy->numItems);
}

void moveMonsters(Room** rooms, Hero* player, char** map, char* eventBar)
{
    for (int a = 0; a < 6; a++)
    {
        int b = 0;
        while (rooms[a]->monsters[b] != NULL)
        {
            char direction = ' ';
            switch (rooms[a]->monsters[b]->type)
            {
                case 'B':
                    {
                        int move = rand() % 4;

                        //switch on direction
                        switch (move)
                        {
                            case 0:
                                direction = 'n';
                                break;
                            case 1:
                                direction = 's';
                                break;
                            case 2:
                                direction = 'e';
                                break;
                            case 3:
                                direction = 'w';
                                break;
                        }
                    }  
                    break;
                case 'S':
                    {
                        char seq[] = {'e','e','w','w'};
                        direction = seq[rooms[a]->monsters[b]->cycle];
                        rooms[a]->monsters[b]->cycle += 1;
                        if (rooms[a]->monsters[b]->cycle > 3)
                            rooms[a]->monsters[b]->cycle = 0;
                    }
                    break;
                case 'Z':
                    {
                        char seq[] = {'n','s',};
                        direction = seq[rooms[a]->monsters[b]->cycle];
                        rooms[a]->monsters[b]->cycle += 1;
                        if (rooms[a]->monsters[b]->cycle > 1)
                            rooms[a]->monsters[b]->cycle = 0;
                    }
                    break;
                case 'T':
                    {
                        char seq[] = {'n','e','s','w'};
                        direction = seq[rooms[a]->monsters[b]->cycle];
                        rooms[a]->monsters[b]->cycle += 1;
                        if (rooms[a]->monsters[b]->cycle > 3)
                            rooms[a]->monsters[b]->cycle = 0;
                    }
                    break;
            }
            makeMonsterMove(direction, map, player, rooms[a]->monsters[b], rooms[a], eventBar);
            b++;
        }
    }
}

void makeMonsterMove(char dir, char** map, Hero* player, Monster* myMonster, Room* room, char* eventBar)
{
    int newCor[2];

    newCor[0] = myMonster->x;
    newCor[1] = myMonster->y;

    switch (dir)
    {
        case 'n':
            newCor[1] -= 1;
            break;
        case 's':
            newCor[1] += 1;
            break;
        case 'e':
            newCor[0] += 1;
            break;
        case 'w':
            newCor[0] -= 1;
            break;
    }

    int b = 0;
    //loop through the monsters in the room
    while (room->monsters[b] != NULL)
    {
        //make sure im not looking at the same monster
        if (room->monsters[b] != myMonster)
        {
            //if collision with another monster, dont move
            if (room->monsters[b]->x == newCor[0] && room->monsters[b]->y == newCor[1])
            {
                return;
            }
        }
        b++;
    }

    //if collision with player
    if (player->x == newCor[0] && player->y == newCor[1])
    {
        //Combat instance
        if (rand()%10+1 > myMonster->speed)
        {
       		attackMonster(player, myMonster, eventBar);
       		return;
        }
       	attackPlayer(player, myMonster, eventBar);
        return;
    }


    char next = map[newCor[0]][newCor[1]];
    if (next == '.')
    {
        myMonster->x = newCor[0];
        myMonster->y = newCor[1];
    }
}

void movePlayer(char input, Room** rooms, Hero* atGuy, char** map, char* eventBar, int mapW, int mapH)
{
    int oldX, oldY;
    int newX, newY;
    
    oldX = atGuy->x;
    oldY = atGuy->y;
    
    newX = oldX;
    newY = oldY;
    
    //check which direction to move in
    switch (input)
    {
        case 'w':
            newY-=1;
        break;
        case 'a':
            newX-=1;
        break;
        case 's':
            newY+=1;
        break;
        case 'd':
            newX+=1;
        break;
            
    }

    char next = map[newX][newY];

    //Monster collision
    int b = 0;
    //loop through the monsters in the room
    while (rooms[atGuy->roomNum]->monsters[b] != NULL)
    {
        //check for attack on this monster
        if (rooms[atGuy->roomNum]->monsters[b]->x == newX && rooms[atGuy->roomNum]->monsters[b]->y == newY && rooms[atGuy->roomNum]->monsters[b]->isDead == 0)
        {
           	//Combat instance
           	if (rand()%10+1 > rooms[atGuy->roomNum]->monsters[b]->speed)
           	{
           		attackMonster(atGuy, rooms[atGuy->roomNum]->monsters[b], eventBar);
           		return;
           	}
           	attackPlayer(atGuy, rooms[atGuy->roomNum]->monsters[b], eventBar);
           	return;
        }
        b++;
    }
    

    //map collision
    if (next != '.' && next != '#' && next != '-' && next != '|' && next != ' ')
    {
		//loop through rooms
		for (int a = 0; a < 6; a++)
		{
			//check for door collision
			if (next == '+')
			{
				if (checkHitDoor(rooms[a], newX, newY))
                {
                    sprintf(eventBar, "Hero opened a door");
                    atGuy->roomNum = a;
                    break;
                }
			}
            else
            {
            	//check which item it it hit
                int hit = checkHitItem(rooms[a], newX, newY, atGuy, map, eventBar);
                //if stairs end game
                if (hit == 2)
                {
                    endGame(rooms, atGuy, map, mapW, mapH);
                    break;
                }
            }
		}
	}
	//check for walls
    else if (next == '-' || next == '|' || next == ' ')
    {
        newX = oldX;
        newY = oldY;
    }
    atGuy->x = newX;
    atGuy->y = newY;
 }

bool checkHitDoor(Room* myRoom, int newX, int newY)
{
    int b = 0;
    //loop through doors and see if the player stepped on them
	while (myRoom->doors[b] != NULL)
    {
        if (myRoom->doors[b]->x == newX && myRoom->doors[b]->y == newY)
        {
            return true;
        }
        b++;
    }
    return false;
}

int checkHitItem(Room* myRoom, int newX, int newY, Hero* atGuy, char** map, char* eventBar)
{
	//loop through the rooms
    for (int a = 0; a < 6; a++)
    {
        int b = 0;
        //loop through the items
        while (myRoom->items[b] != NULL)
        {
        	//check if they hit that item
            if (myRoom->items[b]->x == newX && myRoom->items[b]->y == newY)
            {
            	//run the hit item method
                return hitItem(atGuy, myRoom->items[b], map, eventBar);
            }
            b++;
        }
    }
    return 0;
}

int hitItem(Hero* atGuy, Item* myItem, char** map, char* eventBar)
{
	/*switch on the item that was hit
	 * perform an action based on what they hit */
    switch (myItem->type)
    {
        case 'g':
            atGuy->gold += myItem->value;
            break;
        case 'G':
            atGuy->gold += myItem->value;
            break;
        case 'z':
        case 'a':
            return 2;
            break;
        case 'w':
            
        case 'W': 
            
        case 'e': ;
            
            char item[256];

            switch (myItem->type)
            {
                case 'w':
                    sprintf(item,"common weapon");
                break;
                case 'W':
                    sprintf(item, "rare weapon");
                break;
                case 'e':
                    sprintf(item, "equipment");
                break;
            }

            int pickedUp = 0;
            //loop through the heros inventory and add the item to the next open slot
            for (int a = 0; a < 5; a++)
            {
                if (atGuy->items[a]->isEmpty == 0)
                {
                    atGuy->items[a]->type = myItem->type;
                    atGuy->items[a]->value = myItem->value;
                    atGuy->items[a]->isEmpty = 1;
                    atGuy->numItems += 1;
                    //throw event msg
                    sprintf(eventBar, "Hero picked up a(n) %s", item);
                    pickedUp = 1;
                    break;
                }
            }
            //if they couldnt pick it up, throw event msg
            if (pickedUp == 0)
            {
                sprintf(eventBar, "Hero has stepped on %s, and it broke", item);
            }
            break;
        case 'p':
            atGuy->potions += 1;
            break;
    }
    map[myItem->x][myItem->y] = '.';
    return 1;
}

void usePotion(Hero* player, char* eventBar)
{
	//if they have potions, use one, else throw fail msg
    if (player->potions > 0)
    {
        player->health=50;
        player->potions-=1;
        sprintf(eventBar, "Hero used a potion");
    }
    else
    {
        sprintf(eventBar, "You out of potions fool");
    }
}

void attackPlayer(Hero* player, Monster* scott, char* eventBar)
{
	//if the monster is an A, player looses attack
	if (scott->type=='A')
	{
		player->attack -= scott->attack;
		sprintf(eventBar, "You lost %d attack", scott->attack);
		return;
	}
	//anything other than A, player looses health
	player->health -= scott->attack;
	sprintf(eventBar, "You lost %d health", scott->attack);
}

void attackMonster(Hero* player, Monster* scott, char* eventBar)
{
	//the monster looses health, then throw a msg depending 
	scott->health -= player->attack;
	sprintf(eventBar, "You dealt %d damage", player->attack);
	if (scott->health <= 0)
	{
		scott->isDead=1;
		char type[256];
		//get the string name of the monster type
		switch (scott->type)
		{
			case 'A':
				sprintf(type, "Aquator");
				break;
			case 'B':
				sprintf(type,"Bat");
				break;
			case 'S':
				sprintf(type, "Snake");
				break;
			case 'Z':
				sprintf(type, "Zombie");
				break;
			case 'T':
				sprintf(type, "Troll");
				break;
		}
		sprintf(eventBar, "You killed a %s", type);
	}
	
}

void endGame(Room** rooms, Hero* atGuy, char** map, int width, int height)
{
    //clear the screen
    clear();
    
    //print info
    mvprintw(0,0, "~~~~~~~~~~Game has Ended~~~~~~~~~~");
    
    //free memory
    for (int a = 0; a < width; a++)
    {
        free(map[a]);
    }
    free(map);

    for (int a = 0; a < 6; a++)
    {
        int b = 0;
        while (rooms[a]->doors[b] != NULL)
        {
            free(rooms[a]->doors[b]);
            b++;
        }
        b=0;
        while (rooms[a]->items[b]!=NULL)
        {
            free(rooms[a]->items[b]);
            b++;
        }
        b=0;
        while (rooms[a]->monsters[b] != NULL)
        {
            free (rooms[a]->monsters[b]);
            b++;
        }
            
        free(rooms[a]);
        
    }

    mvprintw(1,0, "Gold: %d", atGuy->gold);
    int b = 0;
    for (int a = 0; a < 5; a++)
    {
    	if (atGuy->items[a]->isEmpty==1)
    	{
    		char type[256];
    		switch (atGuy->items[a]->type)
    		{
    			case 'w':
    				sprintf(type, "Common weapon");
    				break;
    			case 'W':
    				sprintf(type, "Rare weapon");
    				break;
    			case 'e':
    				sprintf(type, "Equipment");
    				break;
    		}
   			mvprintw(2+a, 0, "Item slot %d: %s ~ value: %d", a+1, type, atGuy->items[a]->value);
   			b++;
   		}
    	free(atGuy->items[a]);
    }

    free(atGuy);


	mvprintw(3+b, 0, "Press any key to quit...");
    move(0,0);
    //confirm exit
    getch();
    
    endwin();
    
    //DONE
    exit(0);
}
