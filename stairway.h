#ifndef _STAIRWAY_H_
#define _STAIRWAY_H_

#include "cell.h"

class Stairway: public Cell {
 public:
    Stairway(int row, int col, std::string type, Floor *theFloor);
    bool canBeInRoom() override;
    bool validDestination() override;
};

#endif

