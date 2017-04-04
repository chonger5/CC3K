#include "enemy.h"
#include "halfling.h"
#include "hero.h"
#include <memory>
#include <iostream>

using namespace std;

Halfling::Halfling(int row, int col, Floor *theFloor): 
   Enemy{row, col, "L", theFloor, 100, 15, 20, 0} {}

