#ifndef _PATH_H_
#define _PATH_H_

#include "cell.h"

class Path: public Cell {
 public:
    Path(int row, int col, std::string type, Floor *theFloor);
    bool validDestination() override;
};

#endif

