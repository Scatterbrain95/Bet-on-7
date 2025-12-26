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
int tokens;
long money;
long deposite;
long debt;
float debtMultiplier;
float multiplierMultiplier;
int currentRound;
int turns;
int amountSpins;
bool played;
bool event = false;
bool select = false;

void gameInit() {
    Serial.begin(9600);
    for(size_t i = R_PIN; i <= 37; i += 2){
      pinMode(i, INPUT_PULLUP);
    }
    rState, gState, yState, bState = 0;

    played = false;
    state = 0;
    currentRound = 1;
    turns = 3;
    state = MAIN_MENU;

    tokens = 0;
    tickets = 2;
    money = 7;
    deposite = 0;

    debtMultiplier = 1;
    multiplierMultiplier = 1.5;
    debt = 30;
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

    case GAME_PAYING:
      payingUpdate();
      break; 


    default:
      break;
  }
}

void updateDebt(){
  debtMultiplier *= multiplierMultiplier;
  multiplierMultiplier *= (multiplierMultiplier - 0.25);
  debt *= debtMultiplier;
}

void handleInput(GameStates &currentState, bool* event = nullptr, bool* select = nullptr){


  rState = digitalRead(R_PIN);
  gState = digitalRead(G_PIN);
  yState = digitalRead(Y_PIN);
  bState = digitalRead(B_PIN);

  switch(currentState){
    case MAIN_MENU:
      if(bState == LOW){
        uiClear(BLACK);
        delay(200);
        currentState = GAME_SLOT;
      }
      break;

    case TUTORIAL:
      if(gState== LOW){
        uiClear(BLACK);
        delay(200);
        currentState = GAME_SLOT;
      }
      break;

    case GAME_SLOT:
      *event = false;
      if(bState== LOW && gState != LOW && !(*event)){
        *event = false;
        uiClear(BLACK);
        delay(200);
        currentState = GAME_PAYING;
      }
      if(gState == LOW && !(*event)){
        *event = true;
      }
      break;

    case GAME_PAYING:
      if(yState == LOW && !(*select)){
        *event = false;
        *select = false;
        uiClear(BLACK);
        delay(200);
        currentState = GAME_SLOT;
      }

      if(gState == LOW && !(*select)){
        *select = true;
        delay(1500);
      }

      if(rState == LOW && (*select)){
        *select = false;
        delay(1500);
      }

      if(gState == LOW && (*select)){
        if(money >= 4){
          money -= 1;
          deposite += 1;
          clearData(3,"Deposite: ",deposite);
          delay(500);
        }
      }

      if(yState == LOW && (*select)){
        if(money >= 9){
          money -= 5;
          deposite += 5;
          clearData(3,"Deposite: ",deposite);
          delay(500);
        }
      }

      if(bState == LOW && (*select)){
        if(money >= 4){
          money -= 1;
          tokens += 1;
          clearData(4,"Tokens: ", tokens);
          delay(500);
        }
      }
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
  uiSlotMachine(event);
  if (event) {
    int amount = startSpin();
    money += amount;
    Serial.println(money);
    event = false;
  }
  handleInput(state,&event);
}

void payingUpdate(){
  uiPaying();
  handleInput(state,&event,&select);
}