#include "drow.h"
#include "hero.h"
#include "floor.h"
#include <iostream>

using namespace std;

Drow::Drow(int row, int col, Floor *theFloor): 
   Hero{row, col, "d", theFloor, 150, 25, 15} {}

void Drow::pickUpPotion(shared_ptr<Potion> p) {
	potionInventory.push_back(p);
	const int heroHp = getHp();
	const int heroAtk = getAtk();
	const int heroDef = getDef();
   double drowEffect = 1.5;
	int newHp = (heroHp + p->hp) * drowEffect > originalHp ? originalHp : (heroHp + p->hp) * drowEffect;
	int newAtk = (heroAtk + p->atk) * drowEffect < 0 ? 0 : (heroAtk + p->atk) * drowEffect;
	int newDef = (heroDef + p->def) * drowEffect < 0 ? 0 : (heroDef + p->def) * drowEffect;
   setHp(newHp);
   setAtk(newAtk);
   setDef(newDef);
	addToLastAction("PC picked up " + p->potionType);
}

void Drow::useStoredPotion() {
   if (storedPotionInventory.size() == 0) {
      addToLastAction("Your potion inventory is empty");
      return;
   }
   auto p = storedPotionInventory.back();
   storedPotionInventory.pop_back();
	const int heroHp = getHp();
	const int heroAtk = getAtk();
	const int heroDef = getDef();
   double drowEffect = 1.5;
	int newHp = (heroHp + p->hp) * drowEffect > originalHp ? originalHp : (heroHp + p->hp) * drowEffect;
	int newAtk = (heroAtk + p->atk) * drowEffect < 0 ? 0 : (heroAtk + p->atk) * drowEffect;
	int newDef = (heroDef + p->def) * drowEffect < 0 ? 0 : (heroDef + p->def) * drowEffect;
   setHp(newHp);
   setAtk(newAtk);
   setDef(newDef);
	addToLastAction("PC used stored potion " + p->potionType + ". ");
}

