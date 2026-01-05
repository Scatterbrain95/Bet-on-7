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
long deposit;
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
bool canDeposit = true;
int menuIndx = -1;
int lastIndx = -1;

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
    rState = gState = yState = bState = 0;

    played = false;
    currentRound = 1;
    turns = 5;
    state = MAIN_MENU;

    tokens = 0;
    tickets = 5;
    money = 7;
    deposit = 0;

    debtMultiplier = 1;
    multiplierMultiplier = 1.5;
    debt = 20;
}

void gameLoop(){

  int condition = gameCondition();
  if(condition != 0){
    state = GAME_OVER;
  }
  if(deposit >= debt){
    nextRound();
  }
  if(tickets == 0 && nextTurn){
    nextTurn = false;
    turns -=1;
    canDeposit = (tickets >= 3);
  }
  if (tickets == 0 && !nextTurn) {
    nextTurn = true;
  }
  ledControl(select);
  u8g.firstPage();
  do {
    drawOled(state, select, menuIndx);
  } while (u8g.nextPage());

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
    case INVENTORY_MENU:
      inventoryUpdate();
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
  multiplierMultiplier *= 1.1;
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
    menuIndx = -1;
    lastState = currentState;
  }
  static int lastGState = HIGH;
  static int lastYState = HIGH;
  static int lastBState = HIGH;
  switch (currentState) {

    case MAIN_MENU:
      if (bState == LOW) {
        uiClear(BLACK);
        delay(200);
        currentState = TUTORIAL;
      }
      lastGState = gState;
      lastYState = yState;
      lastBState = bState;
      break;


    case TUTORIAL:
      if (gState == LOW) {
        uiClear(BLACK);
        delay(200);
        currentState = GAME_SLOT;
      }
      lastGState = gState;
      lastYState = yState;
      lastBState = bState;
      break;


    case GAME_SLOT:
      if (bState == LOW && gState != LOW && event && !(*event)) {
        uiClear(BLACK);
        delay(200);
        currentState = GAME_PAYING;
      }

      if (gState == LOW && event && tickets > 0  ) {
        *event = true;
        Ledstate = SPIN;
      }
      if (gState == LOW && event && tickets <= 0  ) {
        Ledstate = REJECT;
      }
      lastGState = gState;
      lastYState = yState;
      lastBState = bState;
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

      if (gState == LOW && select && !(*select) && lastGState == HIGH) {
        *select = true;
        lastGState = LOW;
        Ledstate = SELECTED;
        delay(500);
      }

      if (rState == LOW && select && (*select)) {
        *select = false;
        Ledstate = OFF;
        delay(500);
      }

      if (select && (*select)) {

        if (gState == LOW && money > 0 && lastGState == HIGH && canDeposit) {
          money -= 1;
          deposit += 1;
          clearData(3, "deposit: ", deposit);
          Ledstate = SUCCESSFUL;
          delay(500);
        }else if (!canDeposit){
          Ledstate = REJECT;
          delay(500);
        }

        if (yState == LOW && money > 4 && lastYState == HIGH && canDeposit) {
          money -= 5;
          deposit += 5;
          clearData(3, "deposit: ", deposit);
          Ledstate = SUCCESSFUL;
          delay(500);
        }else if (!canDeposit){
          Ledstate = REJECT;
          delay(500);
        }

        if (bState == LOW && money > 0 && lastBState == HIGH && tickets < 10) {
          money -= 1;
          tickets += 1;
          clearData(4, "Tickets: ", tickets);
          Ledstate = SUCCESSFUL;
          if (tickets >= 3) {
            canDeposit = true;
          }
          delay(500);
        } else if(bState == LOW && lastBState == HIGH  && (money <= 0 || tickets >= 10)){
          Ledstate = REJECT;
          delay(500);
        }
      }
      lastGState = gState;
      lastYState = yState;
      lastBState = bState;
      break;


    case SHOP_MENU:

      if (yState == LOW && select && !(*select)) {
        menuIndx = -1;
        lastIndx = -1;
        *select = false;
        uiClear(BLACK);
        delay(200);
        currentState = GAME_PAYING;
      }

      if (bState == LOW && select && !(*select)) {
        menuIndx = -1;
        lastIndx = -1;
        *select = false;
        uiClear(BLACK);
        delay(200);
        currentState = INVENTORY_MENU;
      }

      if (gState == LOW && select && !(*select) && lastGState == HIGH) {
        *select = true;
        lastGState = LOW;
        Ledstate = SELECTED;
        menuIndx = 0;
        delay(500);
      }

      if (rState == LOW && select && (*select)) {
        *select = false;
        menuIndx = -1;
        Ledstate = OFF;
        lastIndx = -1;
        delay(500);
      }

      if (select && (*select)) {
        if (gState == LOW && lastGState == HIGH && *select) {
          bool success = buyItem(menuIndx);

          if (success) {
            Ledstate = SUCCESSFUL;
            *event = true;
            if (menuIndx >= shopItemCount) menuIndx = shopItemCount - 1;
            lastIndx = -1;
          } else {
            Ledstate = REJECT;  
          }
        }

        if (bState == LOW && menuIndx < shopItemCount && lastBState == HIGH) {
          lastIndx = menuIndx;
          menuIndx++;
          delay(500);
        }
        if(yState == LOW && menuIndx && menuIndx > 0 && lastYState == HIGH){
          lastIndx = menuIndx;
          menuIndx--;
          delay(500);
        }
      }

      lastGState = gState;
      lastYState = yState;
      lastBState = bState;
      break;

    
    case INVENTORY_MENU:

      if (yState == LOW && select && !(*select)) {
        menuIndx = -1;
        lastIndx = -1;
        *select = false;
        uiClear(BLACK);
        delay(200);
        currentState = SHOP_MENU;
      }

      if (gState == LOW && select && !(*select)&& lastGState == HIGH) {
        *select = true;
        lastGState = LOW;
        Ledstate = SELECTED;
        menuIndx = 0;
        delay(500);
      }
      

      if (rState == LOW && select && (*select)) {
        *select = false;
        Ledstate = OFF;
        menuIndx = -1;
        lastIndx = -1;
        delay(500);
      }

      if (select && (*select)) {

        if (gState == LOW && lastGState == HIGH && *select) {
          bool success = sellItem(menuIndx);

          if (success) {
            Ledstate = SUCCESSFUL;
            *event = true;
            if (menuIndx >= itemExist) menuIndx = itemExist - 1;
            lastIndx = -1;
          } else {
            Ledstate = REJECT;  
          }
        }

        if (bState == LOW && menuIndx < itemExist && lastBState == HIGH) {
          lastIndx = menuIndx;
          menuIndx++;
          delay(500);
        }
        if(yState == LOW && menuIndx && menuIndx > 0 && lastYState == HIGH){
          lastIndx = menuIndx;
          menuIndx--;
          delay(500);
        }
      }
      lastGState = gState;
      lastYState = yState;
      lastBState = bState;
      break;

    case GAME_OVER:
      if (gState == LOW) {
        uiClear(BLACK);
        delay(200);
        startNewGame();
      }
      lastGState = gState;
      lastYState = yState;
      lastBState = bState;
      break;

    default:
      uiClear(BLACK);
      break;
  }
}

int gameCondition() {

  if (currentRound == 5 && deposit >= debt && turns > 0) {
    return 1;
  }

  if (money == 0 && deposit < debt && turns <= 0) {

    if (findPlayerItemIndex(5) >= 0) {
      activateAngela();
      return 0; 
    }

    return 2; // lose
  }

  return 0;
}


void nextRound(){
  currentRound += 1;
  updateDebt();
  clearData(1, "TURNS: ", turns);
  clearData(2, "Debt: ", debt);
  tokens += turns;
  turns = 5 + (itemAbility(6) != 1 ? itemAbility(6) : 0);
  shopReset();
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
  uiShop(menuIndx, lastIndx, event);
  handleInput(state,&event,&select);
}

void inventoryUpdate(){
  uiInventory(menuIndx, lastIndx, event);
  handleInput(state,&event,&select);
}

void gameOverUpdate(int condition){
  if (condition == 1){
    uiGameOver(true);
  }
  if(condition == 2){
    uiGameOver(false);
  }
  handleInput(state);
}

void startNewGame() {
  gameInit();
  shopInit();
  innitSlot();
  compReset();
}