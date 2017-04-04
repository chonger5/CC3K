#include "controller.h"
#include "square.h"
#include "character.h"
#include "hero.h"
#include "enemy.h"
#include "item.h"
#include "gold.h"
#include "potion.h"
#include "cell.h"
#include "floor.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <exception>
#include <memory>
using namespace std;


Controller::Controller(string file, bool isDefault): floor{1}, hero{nullptr}, 
   isFrozen{false}, importFile{file}, heroWon{false}, isDefault{isDefault} {
   cout << "Would you like to activate potion inventory? (yes/no)" << endl;
   string answer;
   while (true) {
      cin >> answer;
      if (answer == "yes") {
         potionInventoryActivated = true;
         break;
      } else if (answer == "no") {
         potionInventoryActivated = false;
         break;
      } else if (answer == "q") throw 0;
      else cout << "Please choose yes/no" << endl;
   }

   cout << "Which race would you like your hero to be? (s, d, v, t, g)" << endl;
   string newCharacterType;
   while (true) {
      string s;
      cin >> s;
      if (s == "s" || s == "d" || s == "v" || s == "t" || s == "g") {
         newCharacterType = s;
         break;
      } 
      if (s == "q") throw 0;
      else cout << "Please choose valid race" << endl;
   }
   theFloor = make_shared<Floor>(file, floor, newCharacterType, isDefault);
   hero = theFloor->getHero();
   hero->addToLastAction("Player character has spawned");
}

Controller::~Controller() {}

void Controller::setHero(shared_ptr<Hero>& newHero) {
   hero = newHero;
}

bool Controller::checkIfGameOver() {
   if (hero->getHp() < 1) {
      print();
      cout << "You have been slayed! Game over." << endl;
		hero->printScore();
      return true;
   } else if (heroWon) {
      cout << "You made it to floor 5. Congratulations, you WON!" << endl;
      return true;
   }
   return false;
}

void Controller::playGame() {
   cin.exceptions(ios::failbit|ios::eofbit);
   while (!checkIfGameOver()) {
      try {
         print();
         hero->resetLastAction(); 
         cout << endl << "Enter your next move/command" << endl;
         string cmd;
         cin >> cmd;
         if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || 
               cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw") {
            hero->move(cmd);
            if (hero->isOnStairway()) changeFloors();
            else if (!hero->isOnStairway() && !isFrozen) moveEnemies();
         } else if (cmd == "u") {
            string direction;
            cin >> direction;
            hero->usePotion(direction);
            if (!hero->isOnStairway() && !isFrozen) moveEnemies();
         } else if (cmd == "p" && potionInventoryActivated) {
            string direction;
            cin >> direction;
            hero->storePotion(direction);
            if (!hero->isOnStairway() && !isFrozen) moveEnemies();
         } else if (cmd == "g" && potionInventoryActivated) {   //grab stored potion
            hero->useStoredPotion();
            if (!hero->isOnStairway() && !isFrozen) moveEnemies();
         } else if (cmd == "a") {
            string direction;
            cin >> direction;
            hero->attack(direction);
            if (!hero->isOnStairway() && !isFrozen) moveEnemies();
         } else if (cmd == "f") {
            isFrozen = !isFrozen;
            if (!hero->isOnStairway() && !isFrozen) moveEnemies();
            if (isFrozen) hero->addToLastAction("PC froze enemy's");
         } else if (cmd == "r") {
            cout << "Which race would you like your hero to be? (s, d, v, t, g)" << endl;
            string newCharacterType;
            while (true) {
               string s;
               cin >> s;
                  if (s == "s" || s == "d" || s == "v" || s == "t" || s == "g") {
                     newCharacterType = s;
                     break;
                  } 
                  if (s == "q") throw 0;
                  else cout << "Please choose valid race" << endl;
            }  
            theFloor = make_shared<Floor>(importFile, 1, newCharacterType, isDefault);
            hero = theFloor->getHero();
            hero->addToLastAction("Player character has spawned");
         } else if (cmd == "q") {
            break;
         } else if (cmd == "s" || cmd == "d" || cmd == "v" || cmd == "g" ||
               cmd == "t") {
            cout << "Race cannot be changed during game play" << endl;
		   } else {
            cout << endl << "Please enter a valid move/command" << endl;
            continue;
         }
      } catch (ios::failure) { }
   }
}

void Controller::print() {
   theFloor->printFloor();
   printDetails();
}

void Controller::moveEnemies() {
   for (int i = 0; i < theFloor->enemies.size(); ++i) {
      theFloor->enemies[i]->move(hero);
   }
}

void Controller::printDetails() {
   cout << "Race: " << hero->printHeroType() << " Gold: " << hero->getGold();
   cout << "\t\t\t\t\t\t" << "Floor: " << getFloorNumber() << endl;
   cout << "HP: " << hero->getHp() << endl;
   cout << "Atk: " << hero->getAtk() << endl;
   cout << "Def: " << hero->getDef() << endl;
   cout << "Action: " << hero->getLastAction() << endl;
}

int Controller::getFloorNumber() {
   return floor;
}

void Controller::changeFloors() {
   if (floor == 5) {
      heroWon = true;
      return;
   }
   ++floor;
   theFloor = make_shared<Floor>(importFile, floor, hero, isDefault);
   hero->resetOnStairway();
	hero->setOgAtk();
	hero->setOgDef();
}
