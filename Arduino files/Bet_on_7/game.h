#ifndef GAME_H
#define GAME_H
#include "image.h"

enum GameStates{
  MAIN_MENU = 0,
  SHOP_MENU = 1,
  INVENTORY_MENU= 2,
  GAME_SLOT = 3,
  SPINNING = 4,
  GAME_PAYING = 5,
  PAUSE = 6,
  GAME_OVER = 7,
  TUTORIAL = 8
};

extern const short R_PIN;
extern const short G_PIN;
extern const short Y_PIN;
extern const short B_PIN;
extern int rState, gState, yState, bStatel;
extern int currentRound;
extern int turns;
extern int amountSpins;
extern GameStates state;

extern int tickets;
extern long money;
extern long debt;
extern float debtMultiplier;
extern float multiplierMultiplier;


void gameInit();
void gameLoop();
void handleInput(GameStates &currentState);
void updateDebt();

void mainUpdate();
void tutorialUpdate();
void slotUpdate();
void shopUpdate();
void inventoryUpdate();
void spinUpdate(); 
void payinGUpdate();
void pauseUpdate();
void gameOverUpdate();

#endif