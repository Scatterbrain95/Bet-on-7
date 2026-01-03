#include "game.h"

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
bool nextTurn = true;

enum GameResult {
  CONTINUE,
  WIN,
  LOSE
};

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
    tickets = 5;
    money = 7;
    deposite = 0;

    debtMultiplier = 1;
    multiplierMultiplier = 1.5;
    debt = 30;
}

void gameLoop(){

  int condition = (GameResult)gameCondition();
  if(condition != 0){
    state = GAME_OVER;
  }
  if(tickets <= 0 && nextTurn){
    nextTurn = false;
    turns -=1;
  }
  if(tickets >= 3){
    nextTurn = true;
  }
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

    case SHOP_MENU:
      shopUpdate();
      break;

    case GAME_OVER:
      gameOverUpdate(condition);
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

void handleInput(GameStates &currentState, bool* event = nullptr, bool* select = nullptr) {

  rState = digitalRead(R_PIN);
  gState = digitalRead(G_PIN);
  yState = digitalRead(Y_PIN);
  bState = digitalRead(B_PIN);

  static GameStates lastState = currentState;

  if (currentState != lastState) {
    if (event)  *event  = false;
    if (select) *select = false;

    lastState = currentState;
  }

  switch (currentState) {

    case MAIN_MENU:
      if (bState == LOW) {
        uiClear(BLACK);
        delay(200);
        currentState = GAME_SLOT;
      }
      break;

    case TUTORIAL:
      if (gState == LOW) {
        uiClear(BLACK);
        delay(200);
        currentState = GAME_SLOT;
      }
      break;

    case GAME_SLOT:
      if (bState == LOW && gState != LOW && event && !(*event)) {
        uiClear(BLACK);
        delay(200);
        currentState = GAME_PAYING;
      }

      if (gState == LOW && event && tickets > 0  ) {
        *event = true;
      }
      break;

    case GAME_PAYING:

      if (yState == LOW && select && !(*select)) {
        uiClear(BLACK);
        delay(200);
        currentState = GAME_SLOT;
      }

      if (bState == LOW && select && !(*select)) {
        uiClear(BLACK);
        delay(200);
        currentState = SHOP_MENU;
      }

      if (gState == LOW && select && !(*select)) {
        *select = true;
        delay(2000);
      }

      if (rState == LOW && select && (*select)) {
        *select = false;
        delay(2000);
      }

      if (select && (*select)) {

        if (gState == LOW && money >= 4) {
          money -= 1;
          deposite += 1;
          clearData(3, "Deposite: ", deposite);
          delay(500);
        }

        if (yState == LOW && money >= 9) {
          money -= 5;
          deposite += 5;
          clearData(3, "Deposite: ", deposite);
          delay(500);
        }

        if (bState == LOW && money >= 4) {
          money -= 1;
          tickets += 1;
          clearData(4, "Tickets: ", tickets);
          delay(500);
        }
      }
      break;

    case SHOP_MENU:

      if (yState == LOW && select && !(*select)) {
        uiClear(BLACK);
        delay(200);
        currentState = GAME_PAYING;
      }

      if (bState == LOW && select && !(*select)) {
        uiClear(BLACK);
        delay(200);
        currentState = INVENTORY_MENU;
      }

      if (gState == LOW && select && !(*select)) {
        *select = true;
        delay(1500);
      }

      if (rState == LOW && select && (*select)) {
        *select = false;
        delay(1500);
      }
      break;

    default:
      uiClear(BLACK);
      break;
  }
}

int gameCondition() {


  if (currentRound == 5 && deposite >= debt && turns > 0) {
    return 1;
  }


  if (money == 0 && deposite < debt && turns <= 0) {
    return 2;
  }


  return 0;
}


void nextRound(){
  currentRound += 1;
  updateDebt();
  turns = 5;
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
    tickets -= 1;
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

void shopUpdate(){
  handleInput(state,nullptr,&select);
}

void gameOverUpdate(int condition){
  if (condition == 1){
    uiGameOver(true);
  }
  if(condition == 2){
    uiGameOver(false);
  }
}