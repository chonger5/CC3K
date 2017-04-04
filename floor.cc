#include "floor.h"
#include "square.h"
#include <vector>
#include "square.h"
#include "character.h"
#include "hero.h"
#include "enemy.h"
#include "item.h"
#include "gold.h"
#include "potion.h"
#include "cell.h"
#include "tile.h"
#include "door.h"
#include "wall.h"
#include "stairway.h"
#include "path.h"
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"
#include "orc.h"
#include "drow.h"
#include "shade.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "coordinate.h"
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>

using namespace std;

Floor::Floor(string file, int floorNum, string newHeroType, bool isDefault): hero{nullptr} {
   ifstream f{file};
   int endingRowIndex = 25 * (floorNum - 1);
   string s;
   for (int i = 0; i < endingRowIndex; ++i) getline(f, s); // getline buffer
   for (int i = 0; i < 25; ++i) {
      getline(f, s);
      vector<shared_ptr<Square>> row;
      for (int j = 0; j < 79; ++j) {
         string charAsString(1, s[j]);
         if (charAsString == "@") {
            if (newHeroType == "s") {
               auto newShade = make_shared<Shade>(i, j, this);
               row.push_back(newShade);
               hero = newShade;
            } else if (newHeroType == "d") {
               auto newDrow = make_shared<Drow>(i, j, this);
               row.push_back(newDrow);
               hero = newDrow;
            } else if (newHeroType == "v") {
               auto newVampire = make_shared<Vampire>(i, j, this);
               row.push_back(newVampire);
               hero = newVampire;
            } else if (newHeroType == "g") {
               auto newGoblin = make_shared<Goblin>(i, j, this);
               row.push_back(newGoblin);
               hero = newGoblin;
            } else if (newHeroType == "t") {
               auto newTroll = make_shared<Troll>(i, j, this);
               row.push_back(newTroll);
               hero = newTroll;
            }

         } else if (charAsString == "H") {
            auto newHuman = make_shared<Human>(i, j, this);
            row.push_back(newHuman);
            enemies.push_back(newHuman);
         } else if(charAsString == "W") {
            auto newDwarf = make_shared<Dwarf>(i, j, this);
            row.push_back(newDwarf);
            enemies.push_back(newDwarf);
         } else if(charAsString == "E") {
            auto newElf = make_shared<Elf>(i, j, this);
            row.push_back(newElf);
            enemies.push_back(newElf);
         } else if(charAsString == "O") {
            auto newOrc = make_shared<Orc>(i, j, this);
            row.push_back(newOrc);
            enemies.push_back(newOrc);
         } else if(charAsString == "D") {
            auto newDragon = make_shared<Dragon>(i, j, this);
            row.push_back(newDragon);
            enemies.push_back(newDragon);
            dragons.push_back(newDragon);
         } else if(charAsString == "M") {
            auto newMerchant = make_shared<Merchant>(i, j, this);
            row.push_back(newMerchant);
            enemies.push_back(newMerchant);
         } else if(charAsString == "L") {
           auto newHalfling = make_shared<Halfling>(i, j, this);
            row.push_back(newHalfling);
            enemies.push_back(newHalfling);
         } else if(charAsString == "0") {
			   const string restoreHealth = "RH";
			   bool shouldReveal = false;
			   bool isTmpEft = false;
            auto newPotion = make_shared<Potion>(i, j, "P", restoreHealth, shouldReveal, isTmpEft, 10, 0, 0, this);
            row.push_back(newPotion);
         } else if (charAsString == "1") {
			   const string boostAtk = "BA";
			   bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", boostAtk, shouldReveal, isTmpEft, 0, 5, 0, this);
            row.push_back(newPotion);
         } else if(charAsString == "2") {
			   const string boostDef = "BD";
		   	bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", boostDef, shouldReveal, isTmpEft, 0, 0, 5, this);
            row.push_back(newPotion);
         } else if (charAsString == "3") {
			   const string poisonHealth = "PH";
			   bool shouldReveal = false;
			   bool isTmpEft = false;
            auto newPotion = make_shared<Potion>(i, j, "P", poisonHealth, shouldReveal, isTmpEft, -10, 0, 0, this);
            row.push_back(newPotion);
         } else if(charAsString == "4") {
			   const string woundAtk = "WA";
			   bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", woundAtk, shouldReveal, isTmpEft, 0, -5, 0, this);
            row.push_back(newPotion);
         } else if (charAsString == "5") {
			   const string woundDef = "WD";
			   bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", woundDef, shouldReveal, isTmpEft, 0, 0, -5, this);
            row.push_back(newPotion);
         } else if(charAsString == "6") {
			   const string hoardType = "small hoard";
   			const int smallHoard = 1;	
            auto newGold = make_shared<Gold>(i, j, "G", hoardType, smallHoard, this);
            row.push_back(newGold);
         } else if (charAsString == "7") {
		   	const string hoardType = "normal hoard";
	   		const int normalHoard = 2;
			   auto newGold = make_shared<Gold>(i, j, "G", hoardType, normalHoard, this);
            row.push_back(newGold);
         } else if(charAsString == "8") {
			   const string hoardType = "merchant hoard";
		   	const int merchantHoard = 4;
			   auto newGold = make_shared<Gold>(i, j, "G", hoardType, merchantHoard, this);
            row.push_back(newGold);
         } else if (charAsString == "9") {
   			const string hoardType = "dragon hoard";	
	   		const int dragonHoard = 6;
		   	auto newGold = make_shared<Gold>(i, j, "G", hoardType, dragonHoard, this);
            row.push_back(newGold);
         } else if(charAsString == "|") {
            auto newWall = make_shared<Wall>(i, j, charAsString, this);
            row.push_back(newWall);
         } else if(charAsString == "-") {
            auto newWall = make_shared<Wall>(i, j, charAsString, this);
            row.push_back(newWall);
         } else if(charAsString == ".") {
            auto newTile = make_shared<Tile>(i, j, charAsString, this);
            row.push_back(newTile);
         } else if(charAsString == "#") {
            auto newPath = make_shared<Path>(i, j, charAsString, this);
            row.push_back(newPath);
         } else if(charAsString == "+") {
            auto newDoor = make_shared<Door>(i, j, charAsString, this);
            row.push_back(newDoor);
         } else if(charAsString == "\\") {
            auto newStairway = make_shared<Stairway>(i, j, charAsString, this);
            row.push_back(newStairway);
         } else {
            auto newSquare = make_shared<Square>(i, j, charAsString, this);
            row.push_back(newSquare);
         }
      }
      theFloor.push_back(row);
   }
   setRooms();
   if (isDefault) generateFloor(newHeroType, nullptr);
   else pairDragons();
}

Floor::Floor(string file, int floorNum, shared_ptr<Hero> previousHero, bool isDefault): hero{nullptr} {
   ifstream f{file};
   int endingRowIndex = 25 * (floorNum - 1);
   string s;
   for (int i = 0; i < endingRowIndex; ++i) getline(f, s);  // getline buffer
   for (int i = 0; i < 25; ++i) {
      getline(f, s);
      vector<shared_ptr<Square>> row;
      for (int j = 0; j < 79; ++j) {
         string charAsString(1, s[j]);
         if (charAsString == "@") {
            row.push_back(previousHero);
            hero = previousHero;
            hero->setRow(i);
            hero->setCol(j);
            hero->setFloor(this);
         } else if (charAsString == "H") {
            auto newHuman = make_shared<Human>(i, j, this);
            row.push_back(newHuman);
            enemies.push_back(newHuman);
         } else if(charAsString == "W") {
            auto newDwarf = make_shared<Dwarf>(i, j, this);
            row.push_back(newDwarf);
            enemies.push_back(newDwarf);
         } else if(charAsString == "E") {
            auto newElf = make_shared<Elf>(i, j, this);
            row.push_back(newElf);
            enemies.push_back(newElf);
         } else if(charAsString == "O") {
            auto newOrc = make_shared<Orc>(i, j, this);
            row.push_back(newOrc);
            enemies.push_back(newOrc);
         } else if(charAsString == "D") {
            auto newDragon = make_shared<Dragon>(i, j, this);
            row.push_back(newDragon);
            enemies.push_back(newDragon);
            dragons.push_back(newDragon);
         } else if(charAsString == "M") {
            auto newMerchant = make_shared<Merchant>(i, j, this);
            row.push_back(newMerchant);
            enemies.push_back(newMerchant);
         } else if(charAsString == "L") {
           auto newHalfling = make_shared<Halfling>(i, j, this);
            row.push_back(newHalfling);
            enemies.push_back(newHalfling);
         } else if(charAsString == "0") {
			   const string restoreHealth = "RH";
			   bool shouldReveal = false;
			   bool isTmpEft = false;
            auto newPotion = make_shared<Potion>(i, j, "P", restoreHealth, shouldReveal, isTmpEft, 10, 0, 0, this);
            row.push_back(newPotion);
         } else if (charAsString == "1") {
			   const string boostAtk = "BA";
			   bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", boostAtk, shouldReveal, isTmpEft, 0, 5, 0, this);
            row.push_back(newPotion);
         } else if(charAsString == "2") {
			   const string boostDef = "BD";
		   	bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", boostDef, shouldReveal, isTmpEft, 0, 0, 5, this);
            row.push_back(newPotion);
         } else if (charAsString == "3") {
			   const string poisonHealth = "PH";
			   bool shouldReveal = false;
			   bool isTmpEft = false;
            auto newPotion = make_shared<Potion>(i, j, "P", poisonHealth, shouldReveal, isTmpEft, -10, 0, 0, this);
            row.push_back(newPotion);
         } else if(charAsString == "4") {
			   const string woundAtk = "WA";
			   bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", woundAtk, shouldReveal, isTmpEft, 0, -5, 0, this);
            row.push_back(newPotion);
         } else if (charAsString == "5") {
			   const string woundDef = "WD";
			   bool shouldReveal = false;
			   bool isTmpEft = true;
            auto newPotion = make_shared<Potion>(i, j, "P", woundDef, shouldReveal, isTmpEft, 0, 0, -5, this);
            row.push_back(newPotion);
         } else if(charAsString == "6") {
	   		const string hoardType = "small hoard";
   			const int smallHoard = 1;	
            auto newGold = make_shared<Gold>(i, j, "G", hoardType, smallHoard, this);
            row.push_back(newGold);
         } else if (charAsString == "7") {
		   	const string hoardType = "normal hoard";
	   		const int normalHoard = 2;
			   auto newGold = make_shared<Gold>(i, j, "G", hoardType, normalHoard, this);
            row.push_back(newGold);
         } else if(charAsString == "8") {
			   const string hoardType = "merchant hoard";
		   	const int merchantHoard = 4;
		   	auto newGold = make_shared<Gold>(i, j, "G", hoardType, merchantHoard, this);
            row.push_back(newGold);
         } else if (charAsString == "9") {
			   const string hoardType = "dragon hoard";	
			   const int dragonHoard = 6;
			   auto newGold = make_shared<Gold>(i, j, "G", hoardType, dragonHoard, this);
            row.push_back(newGold);
         } else if(charAsString == "|") {
            auto newWall = make_shared<Wall>(i, j, charAsString, this);
            row.push_back(newWall);
         } else if(charAsString == "-") {
            auto newWall = make_shared<Wall>(i, j, charAsString, this);
            row.push_back(newWall);
         } else if(charAsString == ".") {
            auto newTile = make_shared<Tile>(i, j, charAsString, this);
            row.push_back(newTile);
         } else if(charAsString == "#") {
            auto newPath = make_shared<Path>(i, j, charAsString, this);
            row.push_back(newPath);
         } else if(charAsString == "+") {
            auto newDoor = make_shared<Door>(i, j, charAsString, this);
            row.push_back(newDoor);
         } else if(charAsString == "\\") {
            auto newStairway = make_shared<Stairway>(i, j, charAsString, this);
            row.push_back(newStairway);
         } else {
            auto newSquare = make_shared<Square>(i, j, charAsString, this);
            row.push_back(newSquare);
         }
      }
      theFloor.push_back(row);
   }
   setRooms();
   if (isDefault) generateFloor("", previousHero);
   else pairDragons();

}

Floor::~Floor() {}


void Floor::printFloor() {
   for (int i = 0; i < 25; ++i) {
      for (int j = 0; j < 79;++j) {
         cout << theFloor[i][j]->getType();
      }
      cout << endl;
   }
   cout << endl;
}

void Floor::setSquare(int row, int col, shared_ptr<Square> newSquare) {
   theFloor[row][col] = newSquare;
}

shared_ptr<Hero>& Floor::getHero() {
   return hero;
}

void Floor::setHero(int row, int col) {
   theFloor[row][col] = hero;
   hero->setRow(row);
   hero->setCol(col);
}

vector<shared_ptr<Enemy>>& Floor::getEnemies() {
   return enemies;
}

void Floor::setRooms() {
   int currRoom = 1;
   for (int i = 0; i < 25; ++i) {
      for (int j = 0; j < 79; ++j) {
         if (theFloor[i][j]->canBeInRoom()) {
            bool neighborInRoom = false;
            if (i != 0) {
               if (theFloor[i-1][j]->isRoomSet()) {
                  int neighborsRoom = theFloor[i-1][j]->getRoom();
                  theFloor[i][j]->setRoom(neighborsRoom);
                  theFloor[i][j]->setRoomSet();
                  neighborInRoom = true;
               }
            } 
            if (i != 24) {
               if (theFloor[i+1][j]->isRoomSet()) {
                  int neighborsRoom = theFloor[i+1][j]->getRoom();
                  theFloor[i][j]->setRoom(neighborsRoom);
                  theFloor[i][j]->setRoomSet();
                  neighborInRoom = true;
               }
            }
            if (j != 0) {
               if (theFloor[i][j-1]->isRoomSet()) {
                  int neighborsRoom = theFloor[i][j-1]->getRoom();
                  theFloor[i][j]->setRoom(neighborsRoom);
                  theFloor[i][j]->setRoomSet();
                  neighborInRoom = true;
               }
            }
            if (j != 78) {
               if (theFloor[i][j+1]->isRoomSet()) {
                  int neighborsRoom = theFloor[i][j+1]->getRoom();
                  theFloor[i][j]->setRoom(neighborsRoom);
                  theFloor[i][j]->setRoomSet();
                  neighborInRoom = true;
               }
            }
            if (!neighborInRoom) {
               bool changeRooms = true;
               int colToRight = j+1;
               while (theFloor[i][colToRight]->canBeInRoom()) {
                  if (theFloor[i-1][colToRight]->isRoomSet()) {
                     int neighborsRoom = theFloor[i-1][colToRight]->getRoom();
                     theFloor[i][j]->setRoom(neighborsRoom);
                     theFloor[i][j]->setRoomSet();
                     changeRooms = false;
                  }
                  ++colToRight;
               }
               if (changeRooms) {
                  theFloor[i][j]->setRoomSet();
                  theFloor[i][j]->setRoom(currRoom);
                  ++currRoom;
               }
            }
            addCoordinate(i, j);
         }
      }
   }
   numOfRooms = currRoom - 1;
   /*cout << "numOfRooms = " << numOfRooms << endl;
   for (int i = 0; i < roomCoordinates.size(); ++i) {
      cout << "There are " << roomCoordinates[i].size() << "squares in room " << i + 1 << endl;
      for (int j = 0; j < roomCoordinates[i].size(); ++j) {
         cout << "(" << roomCoordinates[i][j]->row << ", " << roomCoordinates[i][j]->col << ")" << endl;
      }
      cout << endl;
   }*/
}

void Floor::addCoordinate(int row, int col) {
   int room = theFloor[row][col]->getRoom();
   int numOfRoomsRegistered = roomCoordinates.size();
   auto newCoordinate = make_shared<Coordinate>(row, col);
   if (room > numOfRoomsRegistered) {
      vector<shared_ptr<Coordinate>> newRoom;         
      newRoom.push_back(newCoordinate);
      roomCoordinates.push_back(newRoom);
   } else {
      roomCoordinates[room - 1].push_back(newCoordinate);
   }
}


string Floor::getHeroType() {
   while (true) {
      string s;
      cin >> s;
      if (s == "s" || s == "d" || s == "v" || s == "g" || s == "t") return s;
      cout << "Please choose a valid race"<< endl;
   }
}

void Floor::generateFloor(string heroType, shared_ptr<Hero> currHero) {
   cout << "Generating floor..." << endl;
   generateHero(heroType, currHero);
   generateStairway();
   generatePotions();
   generateGold();
   generateEnemies();
}

void Floor::generateHero(string newHeroType, shared_ptr<Hero> currHero) {
   int room = generateRandomNum(numOfRooms);
   int numOfSquaresInRoom = roomCoordinates[room-1].size();
   int randomSquare = generateRandomNum(numOfSquaresInRoom);
   int row = roomCoordinates[room-1][randomSquare-1]->row;
   int col = roomCoordinates[room-1][randomSquare-1]->col;
   if (currHero) {
      hero = currHero;
      hero->setRow(row);
      hero->setCol(col);
      hero->setFloor(this);
   } else {
      if (newHeroType == "s") {
         auto newShade = make_shared<Shade>(row, col, this);
         hero = newShade;
      } else if (newHeroType == "d") {
         auto newDrow = make_shared<Drow>(row, col, this);
         hero = newDrow;
      } else if (newHeroType == "v") {
         auto newVampire = make_shared<Vampire>(row, col, this);
         hero = newVampire;
      } else if (newHeroType == "g") {
         auto newGoblin = make_shared<Goblin>(row, col, this);
         hero = newGoblin;
      } else if (newHeroType == "t") {
         auto newTroll = make_shared<Troll>(row, col, this);
         hero = newTroll;
      }
   }
   theFloor[row][col] = hero;
   theFloor[row][col]->setRoom(room);
   theFloor[row][col]->setRoomSet();  
}

void Floor::generateStairway() {
   int heroRoom = hero->getRoom();
   int stairwayRoom = generateRandomNum(numOfRooms);
   while (stairwayRoom == heroRoom) stairwayRoom = generateRandomNum(numOfRooms);
   int numOfSquaresInRoom = roomCoordinates[stairwayRoom-1].size();
   int randomSquare = generateRandomNum(numOfSquaresInRoom);
   int row = roomCoordinates[stairwayRoom-1][randomSquare-1]->row;
   int col = roomCoordinates[stairwayRoom-1][randomSquare-1]->col;
   while (!theFloor[row][col]->validSpawnDestination()) {
      randomSquare = generateRandomNum(numOfSquaresInRoom);
      row = roomCoordinates[stairwayRoom-1][randomSquare-1]->row;
      col = roomCoordinates[stairwayRoom-1][randomSquare-1]->col;
   }
   auto newStairway = make_shared<Stairway>(row, col, "\\", this);
   theFloor[row][col] = newStairway;
   theFloor[row][col]->setRoom(stairwayRoom);
   theFloor[row][col]->setRoomSet();  
}



void Floor::generatePotions() {
   for (int i = 0; i < 10; ++i) {
      int potionRoom = generateRandomNum(numOfRooms);
      int numOfSquaresInRoom = roomCoordinates[potionRoom-1].size();
      int randomSquare = generateRandomNum(numOfSquaresInRoom);
      int row = roomCoordinates[potionRoom-1][randomSquare-1]->row;
      int col = roomCoordinates[potionRoom-1][randomSquare-1]->col;
      while (!theFloor[row][col]->validSpawnDestination()) {
         randomSquare = generateRandomNum(numOfSquaresInRoom);
         row = roomCoordinates[potionRoom-1][randomSquare-1]->row;
         col = roomCoordinates[potionRoom-1][randomSquare-1]->col;
      }
      int potionType = generateRandomNum(6);
      string potionName;
      bool isTemp = true;
      int hp = 0;
      int atk = 0;
      int def = 0;
      if (potionType == 1) {
         hp = 10;
         potionName = "RH";
         isTemp = false;
      } else if (potionType == 2) {
         hp = -10;
         potionName = "PH";
         isTemp = false;
      } else if (potionType == 3) {
         atk = 5;
         potionName = "BA";
      } else if (potionType == 4) {
         atk = -5;
         potionName = "WA";
      } else if (potionType == 5) {
         def = 5;
         potionName = "BD";
      } else {
         def = -5;
         potionName = "WD";
      }
      auto newPotion = make_shared<Potion>(row, col, "P", potionName, false, isTemp, hp, atk, def, this);
      theFloor[row][col] = newPotion;
      theFloor[row][col]->setRoom(potionRoom);
      theFloor[row][col]->setRoomSet();  
   }
}

void Floor::setDragon(int hoardRow, int hoardCol, int room) {
   bool dragonSet = false;
   while (!dragonSet) {
      int dragonSquare = generateRandomNum(8);
      int row = hoardRow;
      int col = hoardCol;
      if (dragonSquare == 1) ++row;
      else if (dragonSquare == 2) {
         ++row;
         ++col;
      } else if (dragonSquare == 3) ++col;
      else if (dragonSquare == 4) {
         ++row;
         ++col;
      } else if (dragonSquare == 5) ++row;
      else if (dragonSquare == 6) {
         ++row;
         --col;
      } else if (dragonSquare == 7) --col;
      else {
         --row;
         --col;
      }
      if (theFloor[row][col]->validSpawnDestination()) {
         auto newDragon = make_shared<Dragon>(row, col, this, hoardRow, hoardCol);
         theFloor[row][col] = newDragon;
         theFloor[row][col]->setRoom(room);
         theFloor[row][col]->setRoomSet();       
         dragons.push_back(newDragon);
         theFloor[hoardRow][hoardCol]->setDragonLocation(row, col);
         dragonSet = true;
      }
   }
}

void Floor::generateGold() {
   for (int i = 0; i < 10; ++i) {
      int goldRoom = generateRandomNum(numOfRooms);
      int numOfSquaresInRoom = roomCoordinates[goldRoom-1].size();
      int randomSquare = generateRandomNum(numOfSquaresInRoom);
      int row = roomCoordinates[goldRoom-1][randomSquare-1]->row;
      int col = roomCoordinates[goldRoom-1][randomSquare-1]->col;
      while (!theFloor[row][col]->validSpawnDestination()) {
         randomSquare = generateRandomNum(numOfSquaresInRoom);
         row = roomCoordinates[goldRoom-1][randomSquare-1]->row;
         col = roomCoordinates[goldRoom-1][randomSquare-1]->col;
      }
      int goldType = generateRandomNum(8);
      int worth;
      string hoardType;
      if (goldType >= 1 && goldType <= 5) {
         worth = 2;
         hoardType = "normal hoard";
      } else if (goldType == 6) {
         worth = 6;
         hoardType = "dragon hoard";
         setDragon(row, col, goldRoom);
      } else {
         worth = 1;
         hoardType = "small hoard";
      }
      auto newGold = make_shared<Gold>(row, col, "G", hoardType, worth, this); 
      theFloor[row][col] = newGold;
      theFloor[row][col]->setRoom(goldRoom);
      theFloor[row][col]->setRoomSet();  
   }
}

void Floor::generateEnemies() {
   for (int i = 0; i < 20; ++i) {
      int enemyRoom = generateRandomNum(numOfRooms);
      int numOfSquaresInRoom = roomCoordinates[enemyRoom-1].size();
      int randomSquare = generateRandomNum(numOfSquaresInRoom);
      int row = roomCoordinates[enemyRoom-1][randomSquare-1]->row;
      int col = roomCoordinates[enemyRoom-1][randomSquare-1]->col;
      while (!theFloor[row][col]->validSpawnDestination()) {
         randomSquare = generateRandomNum(numOfSquaresInRoom);
         row = roomCoordinates[enemyRoom-1][randomSquare-1]->row;
         col = roomCoordinates[enemyRoom-1][randomSquare-1]->col;
      }
      int enemyType = generateRandomNum(18);
      if (enemyType >= 1 && enemyType <= 4) {
         auto newHuman = make_shared<Human>(row, col, this);
         enemies.push_back(newHuman);
         theFloor[row][col] = newHuman;
         theFloor[row][col]->setRoom(enemyRoom);
         theFloor[row][col]->setRoomSet();  
      } else if(enemyType >= 5 && enemyType <= 7) {
         auto newDwarf = make_shared<Dwarf>(row, col, this);
         enemies.push_back(newDwarf);
         theFloor[row][col] = newDwarf;
         theFloor[row][col]->setRoom(enemyRoom);
         theFloor[row][col]->setRoomSet();  
      } else if (enemyType >= 8 && enemyType <= 9) {
         auto newElf = make_shared<Elf>(row, col, this);
         enemies.push_back(newElf);
         theFloor[row][col] = newElf;
         theFloor[row][col]->setRoom(enemyRoom);
         theFloor[row][col]->setRoomSet();  
      } else if(enemyType >= 10 && enemyType <= 11) {
         auto newOrc = make_shared<Orc>(row, col, this);
         enemies.push_back(newOrc);
         theFloor[row][col] = newOrc;
         theFloor[row][col]->setRoom(enemyRoom);
         theFloor[row][col]->setRoomSet();    
      } else if(enemyType >= 12 && enemyType <= 13) {
         auto newMerchant = make_shared<Merchant>(row, col, this);
         enemies.push_back(newMerchant);
         theFloor[row][col] = newMerchant;
         theFloor[row][col]->setRoom(enemyRoom);
         theFloor[row][col]->setRoomSet();  
      } else {
         auto newHalfling = make_shared<Halfling>(row, col, this);
         enemies.push_back(newHalfling);
         theFloor[row][col] = newHalfling;
         theFloor[row][col]->setRoom(enemyRoom);
         theFloor[row][col]->setRoomSet();  
      }
   }
}

int Floor::generateRandomNum(int range) {
   srand(time(nullptr));
   int randNum = rand() % range + 1;
   return randNum;
}

void Floor::pairDragons() {
   for (int i = 0; i < dragons.size(); ++i) {
      int row = dragons[i]->getRow();
      int col = dragons[i]->getCol();
      int goldRow;
      int goldCol;
      bool foundDragonHoard = false;
      while (!foundDragonHoard) {
         shared_ptr<Gold> g;
         if (dynamic_pointer_cast<Gold>(theFloor[row-1][col])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row-1][col]);
         } else if (dynamic_pointer_cast<Gold>(theFloor[row-1][col+1])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row-1][col+1]);
         } else if (dynamic_pointer_cast<Gold>(theFloor[row][col+1])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row][col+1]);
         } else if (dynamic_pointer_cast<Gold>(theFloor[row+1][col+1])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row+1][col+1]);
         } else if (dynamic_pointer_cast<Gold>(theFloor[row+1][col])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row+1][col]);
         } else if (dynamic_pointer_cast<Gold>(theFloor[row+1][col-1])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row+1][col-1]);
         } else if (dynamic_pointer_cast<Gold>(theFloor[row][col-1])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row][col-1]);
         } else if (dynamic_pointer_cast<Gold>(theFloor[row-1][col-1])) {
            g = dynamic_pointer_cast<Gold>(theFloor[row-1][col-1]);
         }
         if (g->getWorth() == 6) {
            goldRow = g->getRow();
            goldCol = g->getCol();
            g->setDragonLocation(row, col);
            foundDragonHoard = true;
         }
      }
      dragons[i]->setGoldCoord(goldRow, goldCol);
   }
}

