#include "square.h"
#include "floor.h"
#include <string>
#include <iostream>
#include <memory>

using namespace std;

Square::Square(int row, int col, string type, Floor *theFloor): 
   row{row}, col{col}, type{type}, theFloor(theFloor), roomSet(false), room{0} {}

int Square::getRow() {
   return row;
}

int Square::getCol() {
   return col;
}

void Square::setRow(int r) {
   row = r;
}

void Square::setCol(int c) {
   col = c;
}

string Square::getType() {
   return type;
}

bool Square::isHero() {
   return false;
}

bool Square::validDestination() {
   return false;
}

bool Square::canBeInRoom() {
   return false;
}

void Square::setRoom(int r) {
   room = r;
}

void Square::setRoomSet() {
   roomSet = true;
}

int Square::getRoom() {
   return room;
}

bool Square::isRoomSet() {
   return roomSet;
}

bool Square::validEnemyDestination() {
   return false;
}

void Square::moveEnemy() {}

bool Square::pickUpItem(shared_ptr<Square> s) {}

bool Square::canBeAttacked() {
   return false;
}

bool Square::validSpawnDestination() {
   return false;
}

void Square::setDragonLocation(int row, int col) {}

