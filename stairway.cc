#include "cell.h"
#include "stairway.h"
#include "square.h"
#include <string>

using namespace std;

Stairway::Stairway(int row, int col, string type, Floor *theFloor): Cell(row, col, type, theFloor) {}

bool Stairway::validDestination() {
   return true;
}

bool Stairway::canBeInRoom() {
   return true;
}

