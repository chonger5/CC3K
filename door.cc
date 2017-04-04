#include "cell.h"
#include "door.h"
#include "square.h"
#include <string>

using namespace std;

Door::Door(int row, int col, string type, Floor *theFloor): Cell(row, col, type, theFloor) {}

bool Door::validDestination() {
   return true;
}
