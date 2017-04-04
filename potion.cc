#include "potion.h"
#include "item.h"
#include "floor.h"

using namespace std;

Potion::Potion(int row, int col, string type, string potionType, bool shouldReveal, bool isTmpEft, int hp, int atk, int def, Floor *theFloor):
	Item(row, col, type, theFloor),
	potionType{potionType}, shouldReveal{shouldReveal}, isTmpEft{isTmpEft},
	hp{hp}, atk{atk}, def{def} {}

string Potion::getPotionType() {
	return potionType;
}

