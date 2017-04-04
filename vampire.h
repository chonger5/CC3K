#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_

#include "hero.h"

class Potion;
class Enemy;

class Vampire: public Hero {
 public:
   Vampire(int row, int col, Floor *theFloor);
   void pickUpPotion(std::shared_ptr<Potion> p);
   void strikeEnemy(std::shared_ptr<Enemy> e) override;
   void useStoredPotion() override;
};

#endif

