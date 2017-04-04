#ifndef _GOBLIN_H_
#define _GOBLIN_H_

#include "hero.h"

class Enemy;
class Goblin: public Hero {
 public:
   Goblin(int row, int col, Floor *theFloor);
   void strikeEnemy(std::shared_ptr<Enemy> e) override;
 };

#endif

