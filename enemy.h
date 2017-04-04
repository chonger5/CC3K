#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "square.h"
#include "character.h"
#include "hero.h"
#include <string>

class Floor;

class Enemy: public std::enable_shared_from_this<Enemy>, public Character {
   int worth;
 protected:
   bool isValidDestination(int r,int c);
   int getNewRow(int i);
   int getNewCol(int c);
   virtual bool inAttackRange(std::shared_ptr<Hero> h);
 public:
   Enemy(int row, int col, std::string type, Floor *theFloor, int hp, int atk, int def, int worth);
	bool canBeAttacked() override;
   int getWorth();
   virtual void attack(std::shared_ptr<Hero> h);
   virtual void move(std::shared_ptr<Hero> h);
};

#endif

