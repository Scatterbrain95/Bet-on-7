#include "game.h"
#include "item.h"
#include "ui.h"
#include "slot.h"


GameStates state;

const short R_PIN = 31;
const short G_PIN = 33;
const short Y_PIN = 35;
const short B_PIN = 37;

int rState, gState, yState, bState;

int tickets;
long money;
long debt;
float debtMultiplier;
float multiplierMultiplier;
int currentRound;
int turns;
int amountSpins;
bool played;

void gameInit() {
    Serial.begin(9600);
    for(size_t i = R_PIN; i <= 37; i += 2){
      pinMode(i, INPUT_PULLUP);
    }
    rState, gState, yState, bState = 0;
    played = false;
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
      break;

    case TUTORIAL:
      tutorialUpdate();
      break;
    case GAME_SLOT:
      slotUpdate();
      break;
    default:
      break;
  }
}

void updateDebt(){

}

void handleInput(GameStates &currentState){
  rState = digitalRead(R_PIN);
  gState = digitalRead(G_PIN);
  yState = digitalRead(Y_PIN);
  bState = digitalRead(B_PIN);

  switch(currentState){
    case MAIN_MENU:
      if(bState == LOW){
        uiClear(BLACK);
        delay(200);
        state = GAME_SLOT;
      }
      break;

    case TUTORIAL:
      if(gState== LOW){
        uiClear(BLACK);
        delay(200);
        state = GAME_SLOT;
      }
      break;

    case GAME_SLOT:
      break;

    default:
      uiClear(BLACK);
      break;
  }
}

void mainUpdate(){
  uiMainMenu();
  handleInput(state);
}

void tutorialUpdate(){
  uiTutorial(played);
  handleInput(state);
}

void slotUpdate(){
  uiSlotMachine();
  handleInput(state);
}