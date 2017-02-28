#ifndef __MULLINSN_STRUCT__
#define __MULLINSN_STRUCT__
#include "room.h"

/** 
 * Hero
 * -------------
 * +x : int
 * +y : int
 * +roomNum : int
 * +gold : int
 * +potions : int
 * +attack : int
 * +numItems : int
 * +Items : struct item*
 * */
typedef struct player
{
    int x;
    int y;
    int roomNum;
    
    int health;
    int gold;
    int potions;
    int attack;
    
    int numItems;
    //Using Item wasnt working
    struct item* items[5];
}Hero;

/** 
 * Monster
 * -------------
 * +x : int
 * +y : int
 * +cycle : int
 * +health : int
 * +speed : char
 * +attack : int
 * +isDead : int 1 is dead 0 isalive
 * +type : char
 * */
typedef struct monster
{
    int x;
    int y;

    int cycle;
    int health;
    int speed;
    int attack;

    int isDead;
    char type;
}Monster;

#endif
