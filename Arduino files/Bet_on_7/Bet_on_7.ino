#include <U8glib.h>
#include <math.h> 
#include "Adafruit_GFX.h"
#include <MCUFRIEND_kbv.h>
#include "game.h"
#include "item.h"
#include "ui.h"
#include "slot.h"
#include "image.h"

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>

using namespace std;

void setup() {
  Serial.begin(9600);
  uiInit();
  initAllItems();
  gameInit();
}


void loop() {
  gameLoop();
}
