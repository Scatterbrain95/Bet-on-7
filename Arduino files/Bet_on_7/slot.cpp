#include "slot.h";
#include <Arduino.h>

const Symbols allSymbols[6] = {{1,CHERRY},{1,LEMON},{3,CLOVER},{3,BELL},{5,DIAMOND},{7,SEVEN}};
Symbols allSlots[3][3];
int x[3] ={};

void innitSlot(){
  Serial.begin(9600);
  for(unsigned int i = 0; i < 3; i++){
    int num = random(0,5);
    x[i] = num;
    for(unsigned int l = 0; l < 3; l++){
      allSlots[i][l]=allSymbols[((num+l)%6)];
    }
  }
}
void resetSlot(){}

void startSpin(bool& start){
  while(start){
    for(unsigned int i = 0; i < 3; i++){
      int buff = 0;
      for(unsigned int l = 0; l < 3; l++){
        buff = x[i]+l%6;
        allSlots[i][l]=allSymbols[(x[i]+l%6)];
        delay(10);
      }
      x[i] = buff;
    }
  }
}

int patternRecognition(){return 1;}