#ifndef _POTION_H_
#define _POTION_H_

#include <string>
#include "item.h"

class Floor;

class Potion: public Item {
 public:
   Potion(int row, int col, std::string type, std::string potionType, bool shouldReveal, bool isTmpEft, int hp, int atk, int def, Floor *theFloor);
	bool isTmpEft;
	bool shouldReveal;
	int hp;
	int atk;
	int def;
	std::string getPotionType();
  	std::string potionType;
};
#endif

