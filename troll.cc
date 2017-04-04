#include "drow.h"
#include "hero.h"
#include "troll.h"
#include <iostream>

using namespace std;

Troll::Troll(int row, int col, Floor *theFloor): 
   Hero{row, col, "t", theFloor, 120, 25, 15} {}

