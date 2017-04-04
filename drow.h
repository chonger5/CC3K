#ifndef _DROW_H_
#define _DROW_H_

#include "hero.h"

class Potion;

class Drow: public Hero {
 public:
   Drow(int row, int col, Floor *theFloor);
   void pickUpPotion(std::shared_ptr<Potion> p) override;
   void useStoredPotion() override;
};

#endif

