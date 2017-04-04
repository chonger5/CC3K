#include "vampire.h"
#include "hero.h"
#include "floor.h"
#include "enemy.h"
#include "tile.h"
#include "dwarf.h"
#include <iostream>

using namespace std;

Vampire::Vampire(int row, int col, Floor *theFloor): 
   Hero{row, col, "v", theFloor, 50, 25, 25} {}

void Vampire::strikeEnemy(shared_ptr<Enemy> e) {
   int enemyRow = e->getRow();
   int enemyCol = e->getCol();
   int enemyHp = e->getHp();
   int enemyDef = e->getDef();
   int myAtk = getAtk();
   int myHp = getHp();
   int damage = calculateDamage(enemyDef, myAtk);
   e->setHp(enemyHp - damage);
   if (dynamic_pointer_cast<Dwarf>(e)) setHp(myHp - 5);
   else setHp(myHp + 5);
   
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

void Vampire::pickUpPotion(shared_ptr<Potion> p) {
	potionInventory.push_back(p);
	const int heroHp = getHp();
	const int heroAtk = getAtk();
	const int heroDef = getDef();
	int newHp = heroHp + p->hp;
	int newAtk = (heroAtk + p->atk) < 0 ? 0 : heroAtk + p->atk;
	int newDef = (heroDef + p->def) < 0 ? 0 : heroDef + p->def;
   setHp(newHp);
   setAtk(newAtk);
   setDef(newDef);
	addToLastAction("PC picked up " + p->potionType);
}

void Vampire::useStoredPotion() {
   if (storedPotionInventory.size() == 0) {
      addToLastAction("Your potion inventory is empty");
      return;
   }
   auto p = storedPotionInventory.back();
   storedPotionInventory.pop_back();
	const int heroHp = getHp();
	const int heroAtk = getAtk();
	const int heroDef = getDef();
	int newHp = heroHp + p->hp;
	int newAtk = (heroAtk + p->atk) < 0 ? 0 : heroAtk + p->atk;
	int newDef = (heroDef + p->def) < 0 ? 0 : heroDef + p->def;
   setHp(newHp);
   setAtk(newAtk);
   setDef(newDef);
	addToLastAction("PC used stored potion " + p->potionType + ". ");
}

