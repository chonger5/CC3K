#ifndef _HALFLING_H_
#define _HALFLING_H_

#include "enemy.h"

class Floor;
class Hero;

class Halfling: public Enemy {
 public:
   Halfling(int row, int col, Floor *theFloor);
};

#endif

