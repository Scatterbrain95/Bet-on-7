#ifndef COMPONENTS_H
#define COMPONENTS_H
 #include "item.h"
 #include "shop.h"
 #include <U8glib.h>
 #include "game.h"
  extern U8GLIB_SSD1306_128X64 u8g;
  extern const int bluePin;
  extern const int greenPin;
  extern const int redPin;
  enum LedStates{OFF=0,SPIN=1,REJECT=2,SUCCESSFUL=3,SELECTED=4};
  extern LedStates Ledstate;
  void compInit();
  void compReset();
  void ledControl(bool select);

  void drawOled(int state, bool select, int menuIndx);
  void updateLedFromSelect(bool select);
  void setRGB(int r, int g, int b);
#endif