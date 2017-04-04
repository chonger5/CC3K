#include "item.h"
#include "square.h"
#include "floor.h"
#include <string>

using namespace std;

Item::Item(int row, int col, string type, Floor *theFloor): Square(row, col, type, theFloor) {}

bool Item::validDestination() {
   return true;
}

bool Item::canBeInRoom() {
   return true;;
}

