#ifndef SHOP_H
#define SHOP_H

#include "game.h"
#include "item.h"

#include <Arduino.h>
extern Item shopItems[3];
extern int shopItemCount; 
bool shopHasItem(int id, int count);
bool buyItem(int index);
void shopReset();
void shopInit();

#endif