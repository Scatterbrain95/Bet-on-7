#ifndef SHOP_H
#define SHOP_H

#include "game.h"
#include "item.h"

#include <Arduino.h>
extern Item shopItems[3];
bool shopHasItem();
void buyItem();
void shopReset();
void shopInit();

#endif