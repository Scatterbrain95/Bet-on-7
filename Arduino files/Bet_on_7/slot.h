#ifndef SLOT_H
#define SLOT_H
  #include <ctime>
  #include
  enum enumSymbols{
    CHERRY,
    LEMON,
    CLOVER,
    BELL,
    DIAMOND,
    SEVEN,
  };

  typedef struct{
    short value;
    enumSymbols symbol;
  } Symbols;

  extern Symbols allSlots[3][3];

  void innitSlot();
  void startSpin(bool& stop);
  int patternRecognition();
#endif