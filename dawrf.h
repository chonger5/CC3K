#ifndef _ORC_H_
#define _ORC_H_

#include "enemy.h"

class Floor;
class Hero;

class Orc: public Enemy {
 public:
   Orc(int row, int col, Floor *theFloor);
   void attack(std::shared_ptr<Hero> h) override;
};

#endif
