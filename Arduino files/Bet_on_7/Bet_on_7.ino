#include <math.h> 
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "game.h"
#include "item.h"
#include "shop.h"
#include "ui.h"
#include "slot.h"
#include "image.h"
#include "components.h"
using namespace std;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A6));
  uiInit();
  compInit();
  startNewGame();
}


void loop() {
  gameLoop();
}
