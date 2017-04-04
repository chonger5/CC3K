#include "character.h"
#include "floor.h"
#include <string>
#include <cmath>
using namespace std;

Character::Character(int row, int col, string type, Floor *theFloor,
      int hp, int atk, int def): 
   Square(row, col, type, theFloor), hp{hp}, atk{atk}, def{def}, 
   previousTenant{nullptr} {}

int Character::getHp() {
   return hp;
}

void Character::setHp(int newHp) {
   hp = newHp;
}

int Character::getAtk() {
   return atk;
}

void Character::setAtk(int newAtk) {
   atk = newAtk;
}

int Character::getDef() {
   return def;
}

void Character::setDef(int newDef) {
   def = newDef;
}

bool Character::validDestination() {
   return false;
}

bool Character::canBeInRoom() {
   return true;
}

int Character::calculateDamage(double defenderDef, double attackerAtk) {
   double damage = ceil(100 / (100 + defenderDef)) * attackerAtk;
   return damage;
}
