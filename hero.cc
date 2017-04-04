#include "character.h"
#include "floor.h"
#include "tile.h"
#include "merchant.h"
#include "halfling.h"
#include "dragon.h"
#include "stairway.h"
#include "enemy.h"
#include "square.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>

using namespace std;

Hero::Hero(int row, int col, string heroType, Floor *theFloor, int hp, int atk, int def): 
   Character{row, col, "@", theFloor, hp, atk, def}, attackedMerchant{false}, 
   originalHp{hp}, originalAtk{atk}, originalDef{def}, gold{0}, heroType{heroType}, 
   onStairway{false}, lastAction{""}
{}

int Hero::getGold() {
   return gold;
}

void Hero::addGold(int newGold) {
   gold += newGold;
}

int Hero::getNSCoordinate(string direction) {
   char c = direction[0];
   int currRow = getRow();
   if (c == 'n') return currRow-1;
   else if (c == 's') return currRow+1;
   else return currRow;
}

int Hero::getEWCoordinate(string direction) {
   char c = direction[1];
   int currCol = getCol();
   if (c == 'w' || direction == "we") return currCol-1;
   else if (c == 'e'|| direction == "ea") return currCol+1;
   else return currCol;
}

void Hero::reset() {
   setHp(originalHp);
   setAtk(originalAtk);
   setDef(originalDef);
}

void Hero::move(string direction) {
   try {
      int currRow = getRow();
      int currCol = getCol();
      int newRow = getNSCoordinate(direction);
      int newCol = getEWCoordinate(direction);
      bool isValidDestination = theFloor->theFloor[newRow][newCol]->validDestination();
      if (isValidDestination) {
         if (dynamic_pointer_cast<Stairway>(theFloor->theFloor[newRow][newCol])) {
            onStairway = true;
            return;
         }
         if (previousTenant) theFloor->setSquare(currRow, currCol, previousTenant);	// for initial hero move
         else {
            auto newTile = make_shared<Tile>(currRow, currCol, ".", this->theFloor);
            theFloor->setSquare(currRow, currCol, newTile);
         }
         if (pickUpItem(theFloor->theFloor[newRow][newCol])) {
            auto newTile = make_shared<Tile>(newCol, newCol, ".", this->theFloor);
			   previousTenant = newTile;
	      } else {
         	previousTenant = theFloor->theFloor[newRow][newCol];
         }
		   theFloor->setHero(newRow, newCol);
      } else throw out_of_range("");
   } catch (out_of_range ex) {
      addToLastAction("That is not a valid move");
   }
}

void Hero::removeEnemy(int row, int col) {
   for (int i = 0; i < theFloor->enemies.size(); ++i) {
      if (theFloor->enemies[i]->getRow() == row && theFloor->enemies[i]->getCol() == col) {
         theFloor->enemies.erase(theFloor->enemies.begin() + i);
      }
   }
}

void Hero::strikeEnemy(shared_ptr<Enemy> e) {
   int enemyRow = e->getRow();
   int enemyCol = e->getCol();
   int enemyHp = e->getHp();
   int enemyDef = e->getDef();
   int myAtk = getAtk();
   int damage = calculateDamage(enemyDef, myAtk);
   e->setHp(enemyHp - damage);
   int newEnemyHp = e->getHp();
   if (newEnemyHp <= 0) {
      auto newTile = make_shared<Tile>(enemyRow, enemyCol, ".", this->theFloor);
      theFloor->setSquare(enemyRow, enemyCol, newTile);
      removeEnemy(enemyRow, enemyCol);
      int enemyWorth = e->getWorth();
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

void Hero::attack(string direction) {
   try {
      int currRow = getRow();
      int currCol = getCol();
      int enemyRow = getNSCoordinate(direction);
      int enemyCol = getEWCoordinate(direction);
      bool canBeAttacked = theFloor->theFloor[enemyRow][enemyCol]->canBeAttacked();
      if (canBeAttacked) {
         if (dynamic_pointer_cast<Halfling>(theFloor->theFloor[enemyRow][enemyCol])) {
            srand(time(nullptr));
            int randNum = rand() % 2 + 1;
            if (randNum == 2) {
               strikeEnemy(dynamic_pointer_cast<Enemy>(theFloor->theFloor[enemyRow][enemyCol]));
            } else addToLastAction("PC missed. ");
         }
         else strikeEnemy(dynamic_pointer_cast<Enemy>(theFloor->theFloor[enemyRow][enemyCol]));
         if (dynamic_pointer_cast<Merchant>(theFloor->theFloor[enemyRow][enemyCol])) {
            attackedMerchant = true;
         }
      } else throw out_of_range("");
   } catch (out_of_range ex) {
		addToLastAction("That is not a valid move");
   }
}

bool Hero::pickUpItem(shared_ptr<Square> s) {
	if (s->getType() == "G") {
		auto gold = dynamic_pointer_cast<Gold>(s);
		if (pickUpGold(gold)) return true;
	}
	return false;
}

bool Hero::pickUpGold(shared_ptr<Gold> g) {
	if (g->getHoardType() == "dragon hoard") {
		if (g->isDragonAlive()) {
			addToLastAction("You need to slay the dragon before you can grab its gold. ");
			return false;
		}
	}
	gold += g->getWorth();
   string worth = to_string(g->getWorth());
   string newLastAction = "Picked up " + g->getHoardType() + " (" + worth + ")";
   addToLastAction(newLastAction);
   return true;
}

void Hero::storePotion(string direction) {
   int row = getNSCoordinate(direction);
   int col = getEWCoordinate(direction);
   auto p = dynamic_pointer_cast<Potion>(theFloor->theFloor[row][col]);
   if (p) {
      storedPotionInventory.push_back(p);
		auto newTile = make_shared<Tile>(row, col, ".", this->theFloor);
	   previousTenant = newTile;
		theFloor->setSquare(row, col, newTile);
		addToLastAction("PC added a new potion to inventory");
   } else {
		addToLastAction("There is no potion " + direction + " of you.");
   }
}

void Hero::useStoredPotion() {
   if (storedPotionInventory.size() == 0) {
      addToLastAction("Your potion inventory is empty");
      return;
   }
   auto p = storedPotionInventory.back();
   storedPotionInventory.pop_back();
	const int heroHp = getHp();
	const int heroAtk = getAtk();
	const int heroDef = getDef();
	int newHp = (heroHp + p->hp) > originalHp ? originalHp : heroHp + p->hp;
	int newAtk = (heroAtk + p->atk) < 0 ? 0 : heroAtk + p->atk;
	int newDef = (heroDef + p->def) < 0 ? 0 : heroDef + p->def;
   setHp(newHp);
   setAtk(newAtk);
   setDef(newDef);
	addToLastAction("PC used stored potion " + p->potionType + ". ");
}

void Hero::usePotion(string direction) {
   int row = getNSCoordinate(direction);
   int col = getEWCoordinate(direction);
   auto p = dynamic_pointer_cast<Potion>(theFloor->theFloor[row][col]);
   if (p) {
      pickUpPotion(p);
		auto newTile = make_shared<Tile>(row, col, ".", this->theFloor);
	   previousTenant = newTile;
		theFloor->setSquare(row, col, newTile);
   } else {
		addToLastAction("There is no potion " + direction + " of you.");
   }
} 
         

void Hero::pickUpPotion(shared_ptr<Potion> p) {
	potionInventory.push_back(p);
	const int heroHp = getHp();
	const int heroAtk = getAtk();
	const int heroDef = getDef();
	int newHp = (heroHp + p->hp) > originalHp ? originalHp : heroHp + p->hp;
	int newAtk = (heroAtk + p->atk) < 0 ? 0 : heroAtk + p->atk;
	int newDef = (heroDef + p->def) < 0 ? 0 : heroDef + p->def;
   setHp(newHp);
   setAtk(newAtk);
   setDef(newDef);
	addToLastAction("PC picked up " + p->potionType + ". ");
}

bool Hero::isHero() {
   return true;
}

string Hero::getHeroType() {
   return heroType;
}

void Hero::setHeroType(string type) {
   heroType = type;
}

string Hero::printHeroType() {
	if (getHeroType() == "s") return "Shade";
	if (getHeroType() == "d") return "Drow";
	if (getHeroType() == "v") return "Vampire";
	if (getHeroType() == "t") return "Troll";
	if (getHeroType() == "g") return "Goblin";
}

bool Hero::hasAttackedMerchant() {
   return attackedMerchant;
}

bool Hero::isOnStairway() {
   return onStairway;
}

void Hero::resetOnStairway() {
   onStairway = false;
}

void Hero::setFloor(Floor *newFloor) {
   theFloor = newFloor;
}

string Hero::getLastAction() {
   return lastAction;
}

void Hero::resetLastAction() {
   lastAction = "";
}

void Hero::addToLastAction(string newLastAction) {
   lastAction += newLastAction;
}

void Hero::setOgAtk() {
	setAtk(originalAtk);
}

void Hero::setOgDef() {
	setDef(originalDef);
}

void Hero:: printScore() {
	cout << "Score: " << getGold() << endl;
}

