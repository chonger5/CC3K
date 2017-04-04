#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <memory>

class Square;
class Hero;
class Enemy;
class Floor;

class Controller {
	bool heroWon;                       
   bool isDefault;                  // if the default board is used
	bool isFrozen;                   // if enemies are froze
   int floor;                       // current floor
	std::shared_ptr<Hero> hero;      // hero user is using
	std::shared_ptr<Floor> theFloor; // current floor
	std::string importFile;          // name of file if command line argument given
	void moveEnemies();              // calls move() on all enemies
   bool potionInventoryActivated;   // if the potion inventory bonus is activated
 public:
   Controller(std::string file, bool isDefault);
   ~Controller();
	bool checkIfGameOver(); 
   int getFloorNumber();
   std::string getLastAction();
   void changeFloors();
   void playGame();
   void print();
   void printDetails();             // prints info at the end of the board
   void setFloor();
   void setHero(std::shared_ptr<Hero>& hero);
};

#endif

