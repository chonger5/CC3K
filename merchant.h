#ifndef _MERCHANT_H_
#define _MERCHANT_H_

#include "enemy.h"

class Floor;
class Hero;

class Merchant: public Enemy {
 public:
   Merchant(int row, int col, Floor *theFloor);
   void move(std::shared_ptr<Hero> h) override;
};

#endif

