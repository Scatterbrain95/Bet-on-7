#ifndef SLOT_H
#define SLOT_H

  #include <Arduino.h>

  enum enumSymbols{
    CHERRY=0,
    LEMON=1,
    CLOVER=2,
    BELL=3,
    DIAMOND=4,
    SEVEN=5,
  };

  typedef struct{
    short value;
    enumSymbols symbol;
  } Symbols;

  extern const Symbols allSymbols[6];
  extern Symbols allSlots[3][3];

  void innitSlot();
  void resetSlot();
  int startSpin();
  int patternRecognition();
  
#endif