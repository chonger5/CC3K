#include "cell.h"
#include "tile.h"
#include "square.h"
#include <string>

using namespace std;

Tile::Tile(int row, int col, string type, Floor *theFloor): Cell(row, col, type, theFloor) {}

bool Tile::validDestination() {
   return true;
}

bool Tile::canBeInRoom() {
   return true;
}

bool Tile::validEnemyDestination() {
   return true;
}

bool Tile::validSpawnDestination() {
   return true;
}


