#ifndef ITEM_H
#define ITEM_H
typedef struct {
  const char* name;
  int id;
  int power;
  const char* description;
  bool active;
} Item;



extern Item allItems[10];
extern Item playerItems[4];

void initAllItems();

void addPlayerItem(int id);

void sellItem(int id);

float computeItemMultiplier();
#endif