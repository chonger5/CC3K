#include "gold.h"
#include "item.h"
#include "floor.h"

using namespace std;

DragonHoard::DragonHoard(int row, int col, string type, string hoardType, int worth, Floor *theFloor): 
   Item(row, col, type, theFloor), hoardType{hoardType}, worth{worth} {}

int Gold::getWorth() {
   return worth;
}

string Gold::getHoardType() {
	return hoardType;
}

