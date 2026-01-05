#include "item.h"
#include "game.h"

const Item allItems[ITEMS_AMOUNT]{
  {"Double Crosser",1,1.5,"Diagonal matches will give 1.5x of the coin./",2},
  {"Four eyes", 2, 2,"Two slot matches is doubled",4},
  {"Up and Down", 3, 1.5, "Arrow matches will give 1.5x of the coin.",2},
  {"One and only", 4, 1.0 ,"If you got no matches, gain coin of first slot",5},
  {"Angela",5, 3 ,"Saves you once from losing with 3 turns. (gets used)",6},
  {"\"I'll pay you tomorrow\"",6, 2,"Gets two extra turn.(must be in inventory)",6},
  {"JACKPOT",7, 3,"One jackpot and you'll be rich. Jackpot's coin will be tripled.",7},
  {"All rounder", 8, 1.25, "All of the matches will be multiplied 1.25x.",10}
};
Item playerItems[PLAYER_ITEM_AMOUNT]{};
unsigned itemExist = 0;

void addPlayerItem(int id) {
  if (itemExist >= PLAYER_ITEM_AMOUNT) return;

  for (unsigned i = 0; i < ITEMS_AMOUNT; i++) {
    if (id == allItems[i].id) {
      playerItems[itemExist] = allItems[i];
      itemExist++;
      return;
    }
  }
  
}

float itemAbility(int id){
  int index = findPlayerItemIndex(id);
  if (index < 0) return 1;
  return playerItems[index].power;
}

bool sellItem(int index){
  if (index < 0 || index >= itemExist) return false;

  tokens += playerItems[index].value;
  takeAwayItem(playerItems[index].id);
  return true;
}

void takeAwayItem(int id){
  if (itemExist <= 0) return;
  int index = findPlayerItemIndex(id);
  if (index < 0) return;

  for (unsigned i = index; i < itemExist - 1; i++) {
    playerItems[i] = playerItems[i + 1];
  }

  itemExist--;
}

int findPlayerItemIndex(int id) {
  for (unsigned i = 0; i < itemExist; i++) {
    if (playerItems[i].id == id) {
      return i;
    }
  }
  return -1; 
}

void activateAngela() {
  turns = itemAbility(5);
  float extra = itemAbility(6);
  if (extra != 1) {
    turns += (int)extra;
  }
  takeAwayItem(5);
}

