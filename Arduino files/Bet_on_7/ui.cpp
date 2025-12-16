#include "ui.h"
#include "slot.h"
#include "game.h"
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
  int xStart = (HEIGHT+140 - totalWidth) / 2;
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
  unsigned char* const imageArr[6] PROGMEM ={cherryImage,lemonImage,cloverImage,bellImage,diamondImage,sevenImage};
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




void uiSlotMachine(bool& spin){
  size_t row = 3;
  unsigned char* const imageArr[6]={cherryImage,lemonImage,cloverImage,bellImage,diamondImage,sevenImage};
  int imageColor[6] = {RED,YELLOW,GREEN,YELLOW,BLUE,RED};
  for(size_t i = 0; i < row; i++){
    uiDrawSlot(3,30+(i*80),70,70,WHITE);
  }

  for(size_t i = 0; i < 3; i++){
    for(unsigned int l = 0; l < 3; l++){
      enumSymbols currentSymbol = allSlots[i][l].symbol;
      const unsigned char* slotImg = imageArr[currentSymbol];
      uiDrawImage(130+(i*80),45+(l*80),slotImg,40,40,imageColor[currentSymbol]);
    }
  }

  tft.drawRect(105, 20, 250, 250, WHITE);
  tft.drawRect(95, 10, 270, 300, WHITE);
  tft.drawRect(365, 10, 100, 300, WHITE);
  
  tft.drawRect(45, 10, 50, 300, WHITE);
  tft.drawLine(72,55,72,185,WHITE);

  if (!spin){
    tft.fillCircle(72, 200, 15, BLACK);
    tft.fillCircle(72, 40, 15, RED);
  }else{
    for(size_t i = 0; i < 3; i++){
      for(unsigned int l = 0; l < 3; l++){
       tft.fillRect(130+(i*80),45+(l*80), 40,40, BLACK);
      }
    }
    tft.fillCircle(72, 40, 15, BLACK);
    tft.fillCircle(72, 200, 15, RED);
  }

  uiDrawImage((HEIGHT/2)+60,WIDTH+40,bananaImage,20,20,WHITE);

  
  
  String score[6] = {"2c","2c","3c","3c","5c","7c"};
  for(size_t i = 0; i < 6; i++){
    const unsigned char* img = imageArr[i];
    uiDrawImage(370, 15 + (i*50), img ,40,40, imageColor[i]);
    tft.setTextSize(2);
    tft.setTextColor(YELLOW);
    tft.setCursor(425, 30 + (i*50));
    tft.print(score[i]);
  }

}



void uiPaying(){
  tft.drawRect(105, 20, 250, 200, WHITE);
  tft.drawRect(95, 10, 270, 300, WHITE);
  tft.drawRect(130, 40, 200, 150, WHITE);
  tft.drawRect(130, 240 , 130, 50, WHITE);
  tft.drawRect(270, 240 , 20, 50, WHITE);
  tft.drawRect(275, 245 , 10, 40, WHITE);
  tft.drawRect(300, 240 , 50, 50, WHITE);

  tft.setTextSize(3);
  tft.setTextColor(YELLOW);
  tft.setCursor(320,255);
  tft.print("C");

  String datanames[4] = {"TURNS: ", "Debt: ", "Deposite: ", "Multied: x"};
  float data[4] = {turns,debt,deposit,debtMultiplier};

  for(size_t i = 0; i < 5; i++){
    tft.drawLine(140, 45 + (i*35), 320, 45 + (i*35), RED);
  }
  for(size_t i = 0; i < 4; i++){
    tft.setTextSize(2);
    tft.setTextColor(RED);
    tft.setCursor(140,60 + (i*35));
    tft.println(datanames[i]+data[i]);
  }
}
