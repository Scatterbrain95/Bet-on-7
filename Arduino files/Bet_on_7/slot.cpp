#include "slot.h";
#include <Arduino.h>

const Symbols allSymbols[6] = {{1,CHERRY},{1,LEMON},{3,CLOVER},{3,BELL},{5,DIAMOND},{7,SEVEN}};
Symbols allSlots[3][3];

void innitSlot(){
  for(unsigned int i = 0; i < 3; i++){
    int num = random(0,5);
    for(unsigned int l = 0; l < 3; l++){
      allSlots[i][l]=allSymbols[(num+l)%6)];
    }
  }
}
void resetSlot(){}
void startSpin(bool& stop){}
int patternRecognition(){return 1;}