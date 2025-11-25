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
  tft.setCursor((HEIGHT - h)/2, y);
  tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  tft.print(text);
}

void uiDrawSlot(int amount, int y, int w, int h, uint16_t color){
  int gap = 10;
  int totalWidth = amount * w + (amount - 1) * gap;
  int xStart = (HEIGHT+140- totalWidth) / 2;
  for(size_t i = 0; i < amount; i++){
    int x = xStart + i * (w + gap);
    tft.drawRoundRect(x,y,w,h,5,color);
  }
}





void uiMainMenu(){
  uiCenteredText("B E T  O N  7",100,3,WHITE);
  uiCenteredText("PRESS ANY BUTTON TO PLAY",250,1,WHITE);
}


void uiTutorial(bool& dialoguePlayed){
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

  if (!dialoguePlayed){
    dialoguePlayed = true;
    while (i < len){
    textAnimation(dialogues[i], 250, 1, WHITE);
    delay(3000);
    clearTextArea(0,250,640,600,BLACK);
    i++;
    }
  }
  uiCenteredText("PRESS G(REEN BUTTON) TO CONTINUE",250,1,WHITE);
}

void uiSlotMachine(bool draw){
  size_t row = 3;
  if (!draw){
    draw = true;
    for(size_t i = 0; i < row; i++){
      uiDrawSlot(3,30+(i*80),70,70,WHITE);
    }
  }
}
