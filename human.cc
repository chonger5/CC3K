#include "enemy.h"
#include "human.h"
#include "hero.h"
#include <memory>
#include <iostream>

using namespace std;

Human::Human(int row, int col, Floor *theFloor): 
   Enemy{row, col, "H", theFloor, 140, 20, 20, 0} {}

