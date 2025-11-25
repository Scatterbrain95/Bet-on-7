#include "ui.h"
#include "image.h"
MCUFRIEND_kbv tft;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

const int WIDTH = tft.width();
const int HEIGHT = tft.height();
uint16_t ID;

void uiInit(){
  Serial.begin(9600);
  ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  Serial.println(WIDTH);
  Serial.println(HEIGHT);
}

void clearTextArea(int x, int y, int w, int h, uint16_t color) {
    tft.fillRect(x, y, w, h, color);
}

void uiClear(uint16_t color){
  tft.fillScreen(color);
}
void uiDrawImage(int x, int y, const uint8_t* bitmap, int w, int h, uint16_t color){
  tft.drawBitmap(x, y, bitmap, w, h, color);
}

void textAnimation(const char* text, int y, int size, uint16_t color){
  int16_t x1, y1;
  uint16_t w, h;
  int len = strlen(text);
  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  
  tft.setCursor((HEIGHT - h)/2, y);
  for(size_t i = 0 ;i < len;i++){
    if (text[i] == '\n') {
          y += 12*size;
          tft.setCursor((HEIGHT - h)/2, y);
          continue;
    }
    tft.print(text[i]);
    delay(40);
  }
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
}

