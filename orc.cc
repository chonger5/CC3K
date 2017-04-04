#include "enemy.h"
#include "orc.h"
#include "hero.h"
#include "goblin.h"
#include <memory>
#include <iostream>

using namespace std;

Orc::Orc(int row, int col, Floor *theFloor): 
   Enemy{row, col, "O", theFloor, 180, 30, 25, 0} {}

void Orc::attack(shared_ptr<Hero> h) {
   srand(time(nullptr));
   int randNum = rand() % 2 + 1;
   if (randNum == 1) {
      int heroHp = h->getHp();
      int heroDef = h->getDef();
      int myAtk = getAtk();
      int damage = calculateDamage(heroDef, myAtk);
      h->setHp(heroHp - damage);
      if (dynamic_pointer_cast<Goblin>(h)) h->setHp(heroHp - (1.5 * myAtk));
      else h->setHp(heroHp - myAtk);
      string atkAsString = to_string(getAtk());
      string heroHpAsString = to_string(h->getHp());
      string newLastAction = getType() + " deals " + atkAsString + " damage to PC " + "(" + heroHpAsString + "). ";
      h->addToLastAction(newLastAction);
   }   
}


