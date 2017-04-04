#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "square.h"
#include <string>

class Floor;

class Character: public Square {
   int hp;
   int atk;
   int def;
 public:
   Character(int row, int col, std::string type, Floor *theFloor, int hp, int atk, int def);
   bool canBeInRoom() override;
	bool validDestination() override;
	int calculateDamage(double defenderDef, double attackerAtk);
   int getHp();
	int getAtk();
	int getDef();
   std::shared_ptr<Square> previousTenant;
	void setHp(int newHp);
	void setAtk(int newAtk);
	void setDef(int newDef);
};

#endif

