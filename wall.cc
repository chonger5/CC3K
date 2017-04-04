#include "cell.h"
#include "wall.h"
#include "square.h"
#include <string>

using namespace std;

Wall::Wall(int row, int col, string type, Floor *theFloor): Cell(row, col, type, theFloor) {}

bool Wall::validDestination() {
   return false;
}

