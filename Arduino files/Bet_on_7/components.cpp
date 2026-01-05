#include "components.h"
#include "game.h"  

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
const int bluePin = 47;
const int greenPin = 45;
const int redPin = 43;
LedStates Ledstate;
void compInit(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  u8g.setFont(u8g_font_5x7); 
}
void compReset(){
  Ledstate = 0;
}
void ledControl(bool select){
  switch (Ledstate){
    case OFF:
      setRGB(0, 0, 0);
      break;
    case SPIN:
      for(unsigned i = 0; i < 5; i++){
        setRGB(255, 50, 0);
        delay(250);
        setRGB(0, 0, 0);
        delay(250);
      }
      
      break;
    case REJECT:
      setRGB(255, 0, 0);
      delay(500);
      updateLedFromSelect(select);
      break;
    case SUCCESSFUL:
      setRGB(0, 255, 0);
      delay(500);
      updateLedFromSelect(select);
      break;
    case SELECTED:
      delay(200);
      setRGB(0, 150, 255);
      break;
  }
}


void drawOled(int state, bool select, int menuIndx) {
    const int rowHeight = 12;
    const int startY = 12;
    char buf[32];

    switch (state) {
        case 0:
          u8g.drawStr(0, startY + rowHeight*0, "R: Red");
          u8g.drawStr(0, startY + rowHeight*1, "G: Green");
          u8g.drawStr(0, startY + rowHeight*2, "B: Blue");
          u8g.drawStr(0, startY + rowHeight*3, "Y: Yellow");
          break;
        case 1:
          u8g.drawStr(0, startY + rowHeight*0, "3 in row: 3x slot");
          u8g.drawStr(0, startY + rowHeight*1, "Cross: 3x slot");
          u8g.drawStr(0, startY + rowHeight*2, "2 in row: slot");
          u8g.drawStr(0, startY + rowHeight*3, "Arrows (U&D): slot1+slot2");
          break;
        case 2:
          u8g.drawStr(0, startY + rowHeight*0, "G: Spin");
          sprintf(buf, "Money:%ld", money);
          u8g.drawStr(0, 64 - rowHeight, buf);
          break;
        case 3:
            if (!select) {
                u8g.drawStr(0, startY + rowHeight*0, "G: Deposit");
                u8g.drawStr(0, startY + rowHeight*1, "B: Shop");
                u8g.drawStr(0, startY + rowHeight*2, "Y: Slot");
            } else {
                u8g.drawStr(0, startY + rowHeight*0, "G: +1");
                u8g.drawStr(0, startY + rowHeight*1, "Y: +5");
                u8g.drawStr(0, startY + rowHeight*2, "B: Ticket");
            }
            sprintf(buf, "Money:%ld", money);
            u8g.drawStr(0, 64 - rowHeight, buf);
            break;

        case 4:
            if (!select) {
                u8g.drawStr(0, startY + rowHeight*0, "G: Buy");
                u8g.drawStr(0, startY + rowHeight*1, "B: Inventory");
                u8g.drawStr(0, startY + rowHeight*2, "Y: ATM");
                sprintf(buf, "Tokens:%d", tokens);
                u8g.drawStr(0, 64 - rowHeight, buf);
            } else {
                if (menuIndx >= 0 && menuIndx < shopItemCount) {
                    const Item &item = shopItems[menuIndx];
                    u8g.drawStr(0, startY + rowHeight*0, item.name);

                    sprintf(buf, "Price: %d", item.value);
                    u8g.drawStr(0, startY + rowHeight*1, buf);

                    String desc = String(item.description);
                    int len = desc.length();
                    if (len <= 20) {
                        u8g.drawStr(0, startY + rowHeight*2, desc.c_str());
                    } else {
                        u8g.drawStr(0, startY + rowHeight*2, desc.substring(0, 20).c_str());
                        u8g.drawStr(0, startY + rowHeight*3, desc.substring(20, min(len, 40)).c_str());
                    }

                    
                }
            }
            break;

        case 5:
            if (!select) {
                u8g.drawStr(0, startY + rowHeight*0, "G: Sell");
                u8g.drawStr(0, startY + rowHeight*2, "Y: Shop");
                sprintf(buf, "Tokens:%d", tokens);
                u8g.drawStr(0, 64 - rowHeight, buf);
                
            } else {
                if (menuIndx >= 0 && menuIndx < itemExist) {
                    const Item &item = playerItems[menuIndx];
                    u8g.drawStr(0, startY + rowHeight*0, item.name);

                    sprintf(buf, "Value: %d", item.value);
                    u8g.drawStr(0, startY + rowHeight*1, buf);


                    String desc = String(item.description);
                    int len = desc.length();
                    if (len <= 20) {
                        u8g.drawStr(0, startY + rowHeight*2, desc.c_str());
                    } else {
                        u8g.drawStr(0, startY + rowHeight*2, desc.substring(0, 20).c_str());
                        u8g.drawStr(0, startY + rowHeight*3, desc.substring(20, min(len, 40)).c_str());
                    }

                    
                }
            }
            break;

        default:
            break;
    }
}



void updateLedFromSelect(bool select) {
  if (select) {
    Ledstate = SELECTED;
  } else {
    Ledstate = OFF;
  }
}

void setRGB(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}


