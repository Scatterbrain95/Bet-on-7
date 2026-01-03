#ifndef ITEM_H
#define ITEM_H
#include "game.h"

#define PLAYER_ITEM_AMOUNT 3
#define ITEMS_AMOUNT 8

typedef struct {
  const char* name;
  int id;
  float power;
  const char* description;
  int value;
} Item;



extern const Item allItems[ITEMS_AMOUNT];
extern Item playerItems[PLAYER_ITEM_AMOUNT];
extern unsigned itemExist;

int findPlayerItemIndex(int id);
void addPlayerItem(int id);
float itemAbility(int id);
void sellItem(int id);
void takeAwayItem(int id);


#endif