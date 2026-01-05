#include "shop.h"

Item shopItems[3];
int shopItemCount = 3;
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


bool buyItem(int index){
  if (shopItemCount <= 0) return false;             
  if (index < 0 || index >= shopItemCount) return false;
  if (tokens < shopItems[index].value) return false;  
  if (itemExist >= PLAYER_ITEM_AMOUNT) return false;  

  addPlayerItem(shopItems[index].id);
  tokens -= shopItems[index].value;

  for (unsigned i = index; i < shopItemCount - 1; i++) {
    shopItems[i] = shopItems[i + 1];
  }
  shopItemCount--;

  return true; 
}


void shopReset(){
  for(int i = 0; i < 3; i++){
    int index;
    do{
      index = random(0,ITEMS_AMOUNT);
    }while (shopHasItem(allItems[index].id, i) || findPlayerItemIndex(allItems[index].id) >= 0);
    shopItems[i] = allItems[index];
  }
  shopItemCount=3;
}