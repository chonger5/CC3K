#include "enemy.h"
#include "character.h"
#include "floor.h"
#include "tile.h"
#include <string>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

Enemy::Enemy(int row, int col, string type, Floor *theFloor, int hp, int atk, int def, int worth): 
   Character{row, col, type, theFloor, hp, atk, def}, worth{worth} {}

void Enemy::move(shared_ptr<Hero> h) {
   int currRow = getRow();
   int currCol = getCol();
   if (inAttackRange(h)) {
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

int Enemy::getWorth() {
   return worth;
}

bool Enemy::isValidDestination(int r, int c) {
   return theFloor->theFloor[r][c]->validEnemyDestination();
}

bool Enemy::inAttackRange(shared_ptr<Hero> h) {
   int heroRow = h->getRow();
   int heroCol = h->getCol();
   int rowDifference = getRow() - heroRow;
   int colDifference = getCol() - heroCol;
   return ((rowDifference > -2 && rowDifference < 2) &&
         (colDifference > -2 && colDifference < 2));
}

int Enemy::getNewRow(int i) {
   int currRow = getRow();
   if (i == 1 || i == 7 || i == 8) return currRow - 1;
   if (i == 3 || i == 4 || i == 5) return currRow + 1;
   return currRow;
}

int Enemy::getNewCol(int i) {
   int currCol = getCol();
   if (i == 1 || i == 2 || i == 3) return currCol + 1;
   if (i == 5 || i == 6 || i == 7) return currCol - 1;
   return currCol;
}

void Enemy::attack(shared_ptr<Hero> h) {
   srand(time(nullptr));
   int randNum = rand() % 2 + 1;
   if (randNum == 1) {
      int heroHp = h->getHp();
      int heroDef = h->getDef();
      int myAtk = getAtk();
      int damage = calculateDamage(heroDef, myAtk);
      h->setHp(heroHp - damage);
      string atkAsString = to_string(getAtk());
      string heroHpAsString = to_string(h->getHp());
      string newLastAction = getType() + " deals " + atkAsString + " damage to PC " + "(" + heroHpAsString + "). ";
      h->addToLastAction(newLastAction);
   }
}

bool Enemy::canBeAttacked() {
   return true;
}

