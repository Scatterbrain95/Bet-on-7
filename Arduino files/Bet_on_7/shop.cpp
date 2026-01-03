#include "shop.h"

void shopInit(){
  randomSeed(analogRead(A6));
  shopReset();
}

bool shopHasItem(int id, int count){
  for (int i = 0; i < count; i++) {
    if (shopItems[i].id == id) {
      return true;
    }
  }
  return false;
}


bool shopHasItem(int id){
  for (int i = 0; i < 3; i++) {
    if (shopItems[i].id == id) {
      return true;
    }
  }
  return false;
}

void buyItem(){}


void shopReset(){
  for(int i = 0; i < 3; i++){
    int index;
    do{
      index = random(0,ITEMS_AMOUNT);
    }while (shopHasItem(allItems[index].id, i) || findPlayerItemIndex(allItems[index].id) >= 0);
    shopItems[i] = allItems[index];
  }
}