#ifndef _GOLD_H_
#define _GOLD_H_

#include <string>
#include "item.h"

class Floor;

class Gold: public Item {
   int worth;
   std::string hoardType;
   int dragonRow;
   int dragonCol;
 public:
   Gold(int row, int col, std::string type, std::string hoardType, int worth, Floor *theFloor, int dragonRow = 0, int dragonCol = 0);
   bool isDragonAlive();
   int getDragonRow();
   int getDragonCol();
   int getWorth();
   std::string getHoardType();
   void setDragonLocation(int row, int col);
};

#endif

