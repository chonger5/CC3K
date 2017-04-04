#include "enemy.h"
#include "dwarf.h"
#include "hero.h"
#include <memory>
#include <iostream>

using namespace std;

Dwarf::Dwarf(int row, int col, Floor *theFloor): 
   Enemy{row, col, "W", theFloor, 100, 20, 30, 0} {}

