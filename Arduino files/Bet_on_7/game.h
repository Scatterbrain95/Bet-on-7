#ifndef GAME_H
#define GAME_H

enum GameStates{
  MAIN_MENU,
  GAME,
  PAUSE,
  GAME_OVER
};

extern GameStates state;
extern long money;
extern long debt;
extern float debtMultiplier;
extern float multiplierMultiplier;

typedef struct {
  const char* name;
  int id;
  int power;
  bool active;
} Item;

typedef struct {
  Item items;
  int amount;
}Slot;

extern Item allItems[10];
extern Slot items[10];

void gameInit();
void gameLoop();
void updateDebt();

#endif