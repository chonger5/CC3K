#include "enemy.h"
#include "elf.h"
#include "hero.h"
#include "drow.h"
#include <memory>
#include <iostream>

using namespace std;

Elf::Elf(int row, int col, Floor *theFloor): 
   Enemy{row, col, "E", theFloor, 140, 30, 10, 0} {}

void Elf::attack(shared_ptr<Hero> h) {
   srand(time(nullptr));
   int randNum = rand() % 2 + 1;
   if (randNum == 1) {
      int heroHp = h->getHp();
      int heroDef = h->getDef();
      int myAtk = getAtk();
      int damage = calculateDamage(heroDef, myAtk);
      h->setHp(heroHp - damage);
      if (dynamic_pointer_cast<Drow>(h)) h->setHp(heroHp - myAtk);
      else h->setHp(heroHp - (2 * myAtk));
      string atkAsString = to_string(getAtk());
      string heroHpAsString = to_string(h->getHp());
      string newLastAction = getType() + " deals " + atkAsString + " damage to PC " + "(" + heroHpAsString + "). ";
      h->addToLastAction(newLastAction);
   }
}

