#include <U8glib.h>
#include <math.h> 
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "game.h"
#include "item.h"
#include "ui.h"
#include "slot.h"
#include "image.h"

using namespace std;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A6));
  uiInit();
  initAllItems();
  innitSlot();
  gameInit();
}


void loop() {
  gameLoop();
}
