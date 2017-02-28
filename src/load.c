#include "room.h"
#include "struct.h"
#include "load.h"
#include "struct.h"
#include <stdlib.h>
#include <stdio.h>


char** loadMap(Room** rooms, Hero* atGuy, int* mapW, int* mapH)
{
	int buffer = 3;
    int bufferMid = 5;
    int bufferHalfMid=2;
    
    int maxHT = 0;
    int widthT = 0;
    int maxHB = 0;
    int widthB = 0;
	
	//Loop through the rooms
    for (int a = 0; a < 6; a++)
    {
        //top rooms
        if (a < 3)
        {
            //adjust for width of rooms
            widthT += rooms[a]->width;
            if (rooms[a]->height > maxHT)
                maxHT = rooms[a]->height;
        }
        //bottom rooms
        else
        {
            //adjust for width of rooms
            widthB += rooms[a]->width;
            if (rooms[a]->height > maxHB)
                maxHB = rooms[a]->height;
        }
        
    }
    //total width and height
    int width = buffer*4;
    int height = buffer*2+bufferMid + maxHT + maxHB;
    
    //add the bigger room width to the width
    if( widthB > widthT)
    {
        width+=widthB;
    }
    else
    {
        width+=widthT;
    }
    //store the data
    *mapW = width;
    *mapH = height;
    
    char** map;
    
    //2D array for the map
    map = malloc(sizeof(char*)*width);
    
    for (int x = 0; x < width; x++)
    {
            map[x] = malloc(sizeof(char)*height);
    }
    
    //clear array
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            map[x][y] = ' ';
        }
    }
    
    int rX = buffer;
    int rY = buffer;
    
    //loop through the rooms
    for (int a = 0; a < 6; a++)
    {
        //top rooms
        if (a < 3)
        {
            //add the room to the map
            addRoom(rooms[a], map, atGuy, rX, rY, a);
            //adjust buffer 
            rX += rooms[a]->width;
            rX += buffer;
        }
        else if (a == 3)
        {
            //adjust the buffer to the next line
            rX = buffer;
            rY = maxHT + bufferMid + buffer;
            //add the room to the map
            addRoom(rooms[a], map, atGuy, rX, rY, a);
            //adjust the buffer
            rX+=rooms[a]->width;
            rX += buffer;
        }
        else
        {
            //add the room
            addRoom(rooms[a], map, atGuy, rX, rY, a);
            rX+=rooms[a]->width;
            //adjust the room
            rX+=buffer;
        }
    }
    
    //add halls the map
    setHalls(rooms, map, width, height, buffer, bufferMid, maxHT+bufferHalfMid+buffer);
    
    return map;
    
}

void setHalls(Room** rooms, char** map, int width, int height, int buffer, int bufferMid, int midY)
{
    int left = width-1;
    int right = 0;
    
    //loop through rooms
    for (int a = 0; a < 6; a++)
    {
        int b = 0;
        //loop through doors
        while (rooms[a]->doors[b] != NULL)
        {
            int x = rooms[a]->doors[b]->x;
            int y = rooms[a]->doors[b]->y;
            
            //check the direction of the door
            switch (rooms[a]->doors[b]->side) 
            {
                case 'n':
                    //top side N
                    if (a < 3)
                    {
                        drawHall(map, x, y-1, x, y-buffer/2-1);
                        drawHall(map, x, y-buffer/2-1, rooms[a]->x-buffer/2-2, y-buffer/2-1);
                        drawHall(map, rooms[a]->x-buffer/2-2, y-buffer/2-1, rooms[a]->x-buffer/2-1, midY);
                        checkLR(rooms[a]->x-buffer/2-2, &left, &right);
                    }
                    //Bottom side N
                    else
                    {
                        drawHall(map, x, y-1, x, midY);
                        checkLR(x, &left, &right);
                    }
                    
                    break;
                case 's':
                    //Top side S
                    if (a < 3)
                    {
                        drawHall(map, x, y+1, x, midY);
                        checkLR(x, &left, &right);
                    }
                    //Bottom side S
                    else
                    {
						drawHall(map, x, y+1, x, y+buffer/2+1);
                        drawHall(map, x, y+buffer/2+1, rooms[a]->x-buffer/2-2, y+buffer/2+1);
                        drawHall(map, rooms[a]->x-buffer/2-2, y+buffer/2+1, rooms[a]->x-buffer/2-1, midY);
                        checkLR(rooms[a]->x-buffer/2-2, &left, &right);
                    }
                    
                    break;
                case 'e':
                    //east
                    drawHall(map, x+1, y, x+buffer/2+1, y);
                    drawHall(map, x+buffer/2+1, y, x+buffer/2+1, midY);
                        
                    checkLR(x+buffer/2+1, &left, &right);
                    break;
                case 'w':
                    //west
                    drawHall(map, x-1, y, x-buffer/2-1, y);
					drawHall(map, x-buffer/2-1, y, x-buffer/2-1, midY);
					
                    checkLR(x-buffer/2-1, &left, &right);
                    break;
            }
            
            b++;
        }
        
    }
    //draw the connecting hall
    drawHall(map, left, midY, right, midY);
}

void checkLR(int x, int* left, int* right)
{
	//if its further left then the left marker, set new marker
    if (x < *left)
    {
        *left = x;
    }
    //same as above but for right
    else if (x > *right)
    {
        *right = x;
    }
}

void drawHall(char** map, int x1, int y1, int x2, int y2)
{
	//check for horizontal change
    if (x1-x2 != 0)
    {
    	//get the direction
        int dX = (x2-x1)/abs(x2-x1);    
        //if its negative, flip the x1 and x2 to make it positive
        if (dX < 0)
            swap(&x1,&x2);
    	//draw the hall from from p1 to p2
        for (int x = x1; x <= x2; x++)
        {
            map[x][y1] = '#';
        }
    }
    //check for vertical change
    if (y1-y2 != 0)
    {
    	//get direction
        int dY = (y2-y1)/abs(y2-y1); 
        //if negtive, swap y1 and y2 to make positive
        if(dY < 0)
            swap(&y1,&y2);
        //draw the hall from p1 to p2
        for (int y = y1; y <= y2; y++)
        {
            map[x1][y] = '#';
        }
    }
}

int abs(int num)
{
	//return the absolute of the number
    if(num < 0)
    {
        num*=-1;
    }
    return num;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void addRoom(Room* myRoom, char** map, Hero* atGuy, int rX, int rY, int roomNum)
{
     //draw the background
    for (int w = 0; w < myRoom->width; w++)
    {
        for(int h = 0; h < myRoom->height; h++)
        {
            map[w+rX][h+rY] = '.';
        }
    }
    //draw the walls
    //loop through left/right
    for(int h = 0; h < myRoom->height; h++)
    {
        map[0+rX][h+rY] = '|';

        map[myRoom->width+rX-1][h+rY] = '|';
    }
    //loop through top/btm
    for (int w = 0; w < myRoom->width; w++)
    {
        map[w+rX][0+rY] = '-';
        
        map[w+rX][myRoom->height+rY-1] = '-';
    }
    
    //Display objects
    int b = 0;
    //loop while there is items
    while(myRoom->items[b] != NULL)
    {
        
        char displayChar = '?';
        switch (myRoom->items[b]->type)
        {
            //stairs down
            case 'z':
                displayChar = '<';
                break;
            //stairs going up
            case 'a':
                displayChar = '>';
                break;
            //small gold
            case 'g': 
                displayChar = '*';
                break;
            //big gold
            case 'G':
                displayChar = '8';
                break;
            //common weapon
            case 'w':
                displayChar = ')';
                break;
            //Rare weapon
            case 'W':
                displayChar = '(';
                break;
            //Equipment
            case 'e':
                displayChar = ']';
                break;
            //potion
            case 'p':
                displayChar = '!';
                break;
            default:
                displayChar = myRoom->items[b]->type;
                break;
        }
        //add the item on to the map
        map[myRoom->items[b]->x + rX+1][myRoom->items[b]->y + rY+1] = displayChar;
        //adjust the cordinates of the items relative to the map
        myRoom->items[b]->x += rX+1;
        myRoom->items[b]->y += rY+1;
        b++;
    }

    b=0;
    //adjust the cordinates of the monsters relative to the map
    while (myRoom->monsters[b] != NULL)
    {
        myRoom->monsters[b]->x += rX+1;
        myRoom->monsters[b]->y += rY+1;
        b++;
    }
    
    //DisplayDoor
    b=0;
    //loop while there is doors
    while (myRoom->doors[b] != NULL)
    {
    	//add the door to the map and adjust its cordinates relative to the map
        map[myRoom->doors[b]->x + rX][myRoom->doors[b]->y + rY] = '+';
        myRoom->doors[b]->x += rX;
        myRoom->doors[b]->y += rY;
        b++;
    }
    
    //display hero
    if (atGuy->roomNum == roomNum)
    {
    	//adjust cor
        atGuy->x += rX+1;
        atGuy->y += rY+1;
    }
    
    //adjust cor
    myRoom->x = rX+1;
    myRoom->y = rY+1;
}
