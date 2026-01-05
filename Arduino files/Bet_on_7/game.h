#ifndef GAME_H
#define GAME_H

#include "item.h"
#include "ui.h"
#include "slot.h"
#include "shop.h"
#include "image.h"
#include "components.h"
#include <SoftwareSerial.h>

extern SoftwareSerial peripheralSerial;

enum GameStates{
  MAIN_MENU = 0,
  TUTORIAL = 1,
  GAME_SLOT = 2,
  GAME_PAYING = 3,
  SHOP_MENU = 4,
  INVENTORY_MENU= 5,
  GAME_OVER = 6
};

extern const short R_PIN;
extern const short G_PIN;
extern const short Y_PIN;
extern const short B_PIN;
extern int rState, gState, yState, bState;
extern int currentRound;
extern int turns;
extern int amountSpins;
extern GameStates state;

extern int tokens;
extern int tickets;
extern long money;
extern long debt;
extern long deposit;
extern float debtMultiplier;
extern float multiplierMultiplier;


void mainUpdate();
void tutorialUpdate();
void slotUpdate();
void shopUpdate();
void inventoryUpdate();
void payingUpdate();
void gameOverUpdate(int condition);

void nextRound();
int gameCondition();
void gameInit();
void gameLoop();
void handleInput(GameStates &currentState, bool* event = nullptr, bool* select = nullptr);
void updateDebt();
void startNewGame();
#endif