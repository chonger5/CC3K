#include "gold.h"
#include "item.h"
#include "floor.h"
#include "dragon.h"

using namespace std;

Gold::Gold(int row, int col, string type, string hoardType, int worth, Floor *theFloor, int dragonRow, int dragonCol): 
   Item(row, col, type, theFloor), hoardType{hoardType}, worth{worth}, dragonRow{dragonRow}, dragonCol{dragonCol} {}

int Gold::getWorth() {
   return worth;
}

string Gold::getHoardType() {
	return hoardType;
}

int Gold::getDragonRow() {
   return dragonRow;
}

int Gold::getDragonCol() {
   return dragonCol;
}

void Gold::setDragonLocation(int row, int col) {
   dragonRow = row;
   dragonCol = col;
}

bool Gold::isDragonAlive() {
   if (dynamic_pointer_cast<Dragon>(theFloor->theFloor[dragonRow][dragonCol])) {
      return true;
   }
   return false;
}

