#include "enemy.h"
#include "dragon.h"
#include "hero.h"
#include "tile.h"
#include "floor.h"
#include <memory>
#include <iostream>
#include <time.h>

using namespace std;

Dragon::Dragon(int row, int col, Floor *theFloor, int hoardRow, int hoardCol): 
   Enemy{row, col, "D", theFloor, 150, 20, 20, 6}, hoardRow{hoardRow}, hoardCol{hoardCol}, isAlive{true} {}

bool Dragon::inAttackRange(std::shared_ptr<Hero> h) {
	const int heroRow = h->getRow();
	const int heroCol = h->getCol();
	const int rowDifference = getRow() - heroRow;
	const int colDifference = getCol() - heroCol;
	const int goldRowDifference = hoardRow - heroRow;
	const int goldColDifference = hoardCol - heroCol;
	return ((rowDifference >= -1 && rowDifference <= 1 &&
				colDifference >= -1 && colDifference <= 1) ||
			  (goldRowDifference >= -1 && goldRowDifference <= 1 &&
				goldColDifference >= -1 && goldColDifference <= 1));
}

void Dragon::setGoldCoord(int y, int x) {
   hoardRow = y;
   hoardCol = x;
}

int Dragon::getHoardRow() {
   return hoardRow;
}

int Dragon::getHoardCol() {
   return hoardCol;
}

void Dragon::attack(shared_ptr<Hero> h) {
   const int heroHp = h->getHp();
   const int heroDef = h->getDef();
   const int myAtk = getAtk();
   h->setHp(heroHp - myAtk);
   string atkAsString = to_string(getAtk());
   string heroHpAsString = to_string(h->getHp());
   string newLastAction = getType() + " deals " + atkAsString + " damage to PC " + "(" + heroHpAsString + "). ";
   h->addToLastAction(newLastAction);
}

void Dragon::move(shared_ptr<Hero> h) {
	if (inAttackRange(h)) attack(h);
}

bool Dragon::isDragonAlive() {
	return isAlive;
}

