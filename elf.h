#ifndef _ELF_H_
#define _ELF_H_

#include "enemy.h"

class Floor;
class Hero;

class Elf: public Enemy {
 public:
   Elf(int row, int col, Floor *theFloor);
   void attack(std::shared_ptr<Hero> h) override;
};

#endif

