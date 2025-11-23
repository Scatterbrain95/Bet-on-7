#include "ui.h"

MCUFRIEND_kbv tft;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

const int WIDTH = tft.width();
const int HEIGHT = tft.height();
uint16_t ID;

void uiInit(){
  Serial.begin(9600);
  Serial.println(HEIGHT);
  ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
}

void uiCenteredText(const char* text, int y, int size, uint16_t color){
  int16_t x1, y1;
  uint16_t w, h;
  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  tft.setCursor((HEIGHT - h)/2, y);
  tft.print(text);
}


void uiMainMenu(){
  uiCenteredText("B E T  O N  7",100,3,WHITE);
  uiCenteredText("PRESS ANY BUTTON TO PLAY",250,1,WHITE);
  while(1){
    tft.fill
  }
}

