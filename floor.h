#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <vector>
#include <string>
#include <memory>
#include <utility>

class Square;
class Hero;
class Enemy;
class Coordinate;
class Dragon;

class Floor {
	int numOfRooms;
   std::shared_ptr<Hero> hero;
	std::vector<std::shared_ptr<Dragon>> dragons;   // all dragons in on the floor
   std::vector<std::vector<std::shared_ptr<Coordinate>>> roomCoordinates;     
   // rooms and all coordinates that are in that room
	void addCoordinate(int row, int col);
 public:
   Floor(std::string file, int floorNum, std::string newCharacterType, bool isDefault);
   Floor(std::string file, int floorNum, std::shared_ptr<Hero> previousHero, bool isDefault);
   //Floor();
   ~Floor();
   int generateRandomNum(int range);            // generates random number from 1 - range
	std::string getHeroType();                   // gets the race of the hero
	std::shared_ptr<Hero>& getHero();            // returns the hero
	std::vector<std::shared_ptr<Enemy>> enemies; // all enemies on the floor
	std::vector<std::shared_ptr<Enemy>>& getEnemies(); 
   std::vector<std::vector<std::shared_ptr<Square>>> theFloor; // the layout of the floor
   void generateEnemies();                      // randomly spawns enemies
   void generateFloor(std::string heroType, std::shared_ptr<Hero> currHero); // generates a random floor
   void generateGold();                         // randomly spawns gold
   void generateHero(std::string newHeroType, std::shared_ptr<Hero> currHero);   // randomly spawns hero
   void generatePotions();                      // randomly spawns potions
   void generateStairway();                     // randomly spawns a stairway
	void pairDragons();                          // pairs dragons with their corresponding dragon hoard
   void printFloor();                           // prints the floor
	void setHero(int row, int col);              // sets the hero at coordinate row, col
   void setDragon(int hoardRow, int hoardCol, int room);
   void setSquare(int row, int col, std::shared_ptr<Square> newSquare); // places newSquare at index row, col
	void setRooms();                             // sets the room of each index
};

#endif

