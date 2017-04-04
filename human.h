#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "enemy.h"

class Floor;
class Hero;

class Human: public Enemy {
 public:
   Human(int row, int col, Floor *theFloor);
};

#endif

