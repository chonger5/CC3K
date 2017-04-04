#ifndef _SHADE_H_
#define _SHADE_H_

#include "hero.h"

class Shade: public Hero {
 public:
	Shade(int row, int col, Floor *theFloor);
	void printScore() override;
};

#endif

