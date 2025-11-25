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

void gameInit() {
    Serial.begin(9600);
    for(size_t i = R_PIN; i <= 37; i += 2){
      pinMode(i, INPUT_PULLUP);
    }
    int rState, gState, yState, bState = 0;
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
        state = TUTORIAL;
        uiClear(BLACK);
        delay(200);
      }
      break;

    case TUTORIAL:
      if(gState == LOW){
        uiClear(BLACK);
        delay(200);
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
  bool dialoguePlayed = False;
  size_t i = 0;
  const char* dialogues[19]{
    "Hello, hello ?",
    "Hey new comer.",
    "Seems you are also another \n addict join into the club.",
    "Hmm..?",
    "You just wanted to pay your \n \"debt\" ?",
    "Well dipshit,we both know \n there were many other \n ways to earn money.",
    "But you know what ? \n I prefer to get some \n money out of you.",
    "You need to use the slot machine \n to gain money and pay your debt.",
    "Your debt INCREASES more as game passes.",
    "If you don't pay your debt..",
    "You are a goner.",
    "You buy bunch of TOKENS each TURN.",
    "You can buy to 10 tokens.",
    "But you at LEAST have to \n have three tokens each turn.",
    "At the end of each round \n you have to have paid your debt.",
    "You also gain some tickets \n at the end of each turn.",
    "You can buy buffs for yourself \n with them and the coins you earned.",
    "Well good luck.",
    "Go make some profit for me."
  };
  int len = sizeof(dialogues) / sizeof(dialogues[0]);

  uiDrawImage((HEIGHT/2), (WIDTH/2)-100, telephoneImage, 160, 160, LIGHTGREY);

  if (dialoguePlayed){
    dialoguePlayed = false;
    while (i < len){
    textAnimation(dialogues[i], 250, 1, WHITE);
    delay(3000);
    clearTextArea(0,250,640,600,BLACK);
    i++;
    }
  }
  
  handleInput(state);
}