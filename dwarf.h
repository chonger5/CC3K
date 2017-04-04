#ifndef _DWARF_H_
#define _DWARF_H_

#include "enemy.h"

class Floor;
class Hero;

class Dwarf: public Enemy {
 public:
   Dwarf(int row, int col, Floor *theFloor);
};

#endif

