#include "cell.h"
#include <string>

using namespace std;

Cell::Cell(int row, int col, string type, Floor *theFloor): Square(row, col, type, theFloor) {}

bool Cell::canBeInRoom() {
   return false;
}
