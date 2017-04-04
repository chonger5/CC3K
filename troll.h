#ifndef _TROLL_H_
#define _TROLL_H_

#include "hero.h"

class Troll: public Hero {
 public:
    Troll(int row, int col, Floor *theFloor);
};

#endif

