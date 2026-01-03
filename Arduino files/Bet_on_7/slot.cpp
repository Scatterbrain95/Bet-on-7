#include "slot.h";


const Symbols allSymbols[6] = {{1,CHERRY},{1,LEMON},{3,CLOVER},{3,BELL},{5,DIAMOND},{7,SEVEN}};
Symbols allSlots[3][3];
int x[3] ={};

void innitSlot(){
  Serial.begin(9600);
  randomSeed(analogRead(A6));
  for(unsigned int i = 0; i < 3; i++){
    int num = random(0,5);
    x[i] = num;
    for(unsigned int l = 0; l < 3; l++){
      allSlots[i][l]=allSymbols[((num+l)%6)];
    }
  }
}
void resetSlot(){}

int startSpin(){
  int target[3];
  for (int r = 0; r < 3; r++) {
    target[r] = random(6);
  }

  int spins = random(20, 40);

  for (int s = 0; s < spins; s++) {
    for (int r = 0; r < 3; r++) {
      x[r] = (x[r] + 1) % 6;
      for (int row = 0; row < 3; row++) {
        allSlots[r][row] = allSymbols[(x[r] + row) % 6];
      }
    }
    delay(30);
  }

  for (int r = 0; r < 3; r++) {
    while (x[r] != target[r]) {
      x[r] = (x[r] + 1) % 6;
      for (int row = 0; row < 3; row++) {
        allSlots[r][row] = allSymbols[(x[r] + row) % 6];
      }
      delay(60 + r * 40);
    }
  }

  int amount = patternRecognition();
  return amount;
}


int patternRecognition(){
  int sum = 0;
  if (allSlots[0][1].symbol == allSlots[1][1].symbol && allSlots[1][1].symbol == allSlots[2][1].symbol) {
    sum += allSlots[0][1].value * 3;
  } 
  else if (allSlots[1][1].symbol == allSlots[2][1].symbol || allSlots[0][1].symbol == allSlots[1][1].symbol)
  {
    sum += allSlots[1][1].value;
  } 
  else if (allSlots[0][1].symbol == allSlots[1][0].symbol && allSlots[1][0].symbol == allSlots[2][1].symbol)
  {
    sum += allSlots[0][1].value + allSlots[1][1].value;
  }

  if (allSlots[0][0].symbol == allSlots[1][1].symbol &&
      allSlots[1][1].symbol == allSlots[2][2].symbol) {
    sum += allSlots[1][1].value * 3;
  }


  if (allSlots[0][2].symbol == allSlots[1][1].symbol &&
      allSlots[1][1].symbol == allSlots[2][0].symbol) {
    sum += allSlots[1][1].value * 3;
  }


  if (allSlots[0][0].symbol == allSlots[2][0].symbol 
  && allSlots[0][2].symbol == allSlots[1][1].symbol) {
    sum += allSlots[0][0].value + allSlots[1][2].value;
  }

  return sum;
}