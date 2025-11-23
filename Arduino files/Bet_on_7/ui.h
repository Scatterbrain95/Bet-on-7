#ifndef UI_H
#define UI_H
  #include <MCUFRIEND_kbv.h>
  #include <Adafruit_GFX.h>
  #include <U8glib.h>

  extern U8GLIB_SSD1306_128X64 u8g;
  #define BLACK       0x0000
  #define NAVY        0x000F
  #define DARKGREEN   0x03E0
  #define DARKCYAN    0x03EF
  #define MAROON      0x7800
  #define PURPLE      0x780F
  #define OLIVE       0x7BE0
  #define LIGHTGREY   0xC618
  #define DARKGREY    0x7BEF
  #define BLUE        0x001F
  #define GREEN       0x07E0
  #define CYAN        0x07FF
  #define RED         0xF800
  #define MAGENTA     0xF81F
  #define YELLOW      0xFFE0
  #define WHITE       0xFFFF
  #define ORANGE      0xFD20
  #define GREENYELLOW 0xAFE5
  #define PINK        0xF81F
  
  extern MCUFRIEND_kbv tft;

  extern const int WIDTH;
  extern const int HEIGHT; 

  void uiInit();
  void uiClear(uint16_t color);

  void uiSelect(int x, int y, int w, int h);
  void uiDrawCenteredText(const char* text, int y, int size, uint16_t color);
  void uiDrawSlot(int x, int y, int w, int h, uint16_t color);

  void uiMainMenu();
  void uiSlotMachine();
  void uiInventory();
  void uiShop();
  void uiPaying();
  void uiPauseMenu();
  void uiGameOver();
  void spinAnimation();
  

#endif