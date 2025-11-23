#include "game.h"
#include "item.h"
#include "ui.h"
#include "slot.h"

GameStates state;


int tickets;
long money;
long debt;
float debtMultiplier;
float multiplierMultiplier;
int currentRound;
int turns;
int amountSpins;

void gameInit() {
    currentRound = 1;
    turns = 3;
    state = MAIN_MENU;
    tickets = 2;
    money = 7;
    debt = 30;
    debtMultiplier = 1.2;
    multiplierMultiplier = 1.5;

}

void gameLoop(){
  switch(state){
    case MAIN_MENU:
      mainUpdate();
      handleInput(state);
      break;
    default:
      break;
  }
}

void updateDebt(){

}

void handleInput(GameStates &currentState){
  switch(currentState){
    case MAIN_MENU:
      break;
    default:
      break;
  }
}

void mainUpdate(){
  uiMainMenu();
}