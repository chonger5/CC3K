#ifndef _TILE_H_
#define _TILE_H_

#include "cell.h"

class Tile: public Cell {
 public:
    Tile(int row, int col, std::string type, Floor *theFloor);
    bool canBeInRoom() override;
    bool validDestination() override;
    bool validEnemyDestination() override;
    bool validSpawnDestination() override;
};

#endif

