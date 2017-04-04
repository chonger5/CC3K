#ifndef _DOOR_H_
#define _DOOR_H_

#include "cell.h"

class Door: public Cell {
 public:
    Door(int row, int col, std::string type, Floor *theFloor);
    bool validDestination() override;
};

#endif
