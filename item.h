#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include "square.h"

class Floor;

class Item: public Square {
 public:
    Item(int row, int col, std::string type, Floor *theFloor);
    bool canBeInRoom() override;
    bool validDestination() override;
};

#endif

