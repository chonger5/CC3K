#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "enemy.h"

class Floor;
class Hero;

class Dragon: public Enemy {
	int hoardRow;
	int hoardCol;
	bool isAlive;
	bool inAttackRange(std::shared_ptr<Hero> h);
 public:
   Dragon(int row, int col, Floor *theFloor, int hoardRow = 0, int hoardCol = 0);
	bool isDragonAlive();
   int getHoardRow();
   int getHoardCol();
   void attack(std::shared_ptr<Hero> h) override;
   void move(std::shared_ptr<Hero> h) override;
   void setGoldCoord(int x, int y);
};

#endif


