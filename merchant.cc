#include "enemy.h"
#include "merchant.h"
#include "hero.h"
#include "tile.h"
#include "floor.h"
#include <memory>
#include <iostream>

using namespace std;

Merchant::Merchant(int row, int col, Floor *theFloor): 
   Enemy{row, col, "M", theFloor, 30, 70, 5, 4} {}

void Merchant::move(shared_ptr<Hero> h) {
   int currRow = getRow();
   int currCol = getCol();
   if (inAttackRange(h) && h->hasAttackedMerchant()) {
      attack(h);
      return;
   }

   bool moved = false;
   srand(time(nullptr));
   while (!moved) {
      int randNum = rand() % 8 + 1;
      int newRow = getNewRow(randNum);
      int newCol = getNewCol(randNum);

      if (isValidDestination(newRow, newCol)) {
         auto newTile = make_shared<Tile>(currRow, currCol, ".", theFloor);
         theFloor->setSquare(currRow, currCol, newTile);
         setRow(newRow);
         setCol(newCol);
         theFloor->setSquare(newRow, newCol, shared_from_this());
         moved = true;
      }
   }
}

