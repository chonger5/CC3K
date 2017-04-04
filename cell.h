#ifndef _CELL_H_
#define _CELL_H_

#include "square.h"
#include <string>

class Floor;

class Cell: public Square {
 public:
    Cell(int row, int col, std::string type, Floor *theFloor);
    bool canBeInRoom() override;
};

#endif
