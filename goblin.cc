#include "goblin.h"
#include "hero.h"
#include "floor.h"
#include "enemy.h"
#include "tile.h"
#include <iostream>

using namespace std;

Goblin::Goblin(int row, int col, Floor *theFloor): 
   Hero{row, col, "g", theFloor, 110, 15, 20} {}

void Goblin::strikeEnemy(shared_ptr<Enemy> e) {
   int enemyRow = e->getRow();
   int enemyCol = e->getCol();
   int enemyHp = e->getHp();
   int enemyDef = e->getDef();
   int myAtk = getAtk();
   int myHp = getHp();
   int damage = calculateDamage(enemyDef, myAtk);
   e->setHp(enemyHp - damage);
   int newEnemyHp = e->getHp();
   if (newEnemyHp <= 0) {
      auto newTile = make_shared<Tile>(enemyRow, enemyCol, ".", this->theFloor);
      theFloor->setSquare(enemyRow, enemyCol, newTile);
      removeEnemy(enemyRow, enemyCol);
      int enemyWorth = e->getWorth() + 5;
      string enemyType = e->getType();
      if (enemyType == "H") {
         auto newGold = make_shared<Gold>(enemyRow, enemyCol, "G", "2 normal hoards", 4, theFloor);
         theFloor->setSquare(enemyRow, enemyCol, newGold);
      } else if (enemyType == "M") {
         auto newGold = make_shared<Gold>(enemyRow, enemyCol, "G", "merchant hoard", 4, theFloor);
         theFloor->setSquare(enemyRow, enemyCol, newGold);
      } else addGold(enemyWorth);
      string newLastAction = "PC has slayed " + e->getType();
      addToLastAction(newLastAction);
   } else {
      string atkAsString = to_string(getAtk());
      string enemyHpAsString = to_string(newEnemyHp);
      string newLastAction = "PC deals " + atkAsString + " damage to " + e->getType() + " (" + enemyHpAsString + "). ";
      addToLastAction(newLastAction);
   }   
}

