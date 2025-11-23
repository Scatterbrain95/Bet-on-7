#ifndef ITEM_H
#define ITEM_H
typedef struct {
  const char* name;
  int id;
  int power;
  const char* description;
  bool active;
  int amount;
} Item;



extern Item allItems[10];
extern Item playerItems[10];

void initAllItems();

void addPlayerItem(int id);

void sellItem(int id);

void toggleItem(int id);

float computeItemMultiplier();
#endif