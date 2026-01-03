#ifndef IMAGE_H
#define IMAGE_H

#include "item.h"
#include "game.h"
#include <Arduino.h>
Item shopItems[3];
bool shopHasItem();
void buyItem();
void shopReset();
void shopInit();

#endif