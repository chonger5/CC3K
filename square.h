#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <memory>

class Floor;

class Square {
   bool roomSet;
   int row;
   int col;
   int room;
   std::string type;
 public:
   Floor *theFloor;
   Square(int row, int col, std::string type, Floor *theFloor);
   bool isRoomSet();                      // if the square has been assigned a room
   int getRow();                          
   int getCol();
   int getRoom();
   std::string getType();
	void setRow(int r);
   void setCol(int c);   
   void setRoom(int r);
   void setRoomSet();                     // sets roomSet to true
   virtual bool canBeAttacked();          // if the square can be attacked by the hero
   virtual bool canBeInRoom();            // if the square can be in a room
	virtual bool isHero();                 
   virtual bool validDestination();       // if the hero can move to the square
   virtual bool validEnemyDestination();  // if an enemy can be move to the square
   virtual bool validSpawnDestination();  // if an item can be spawned at the square
   virtual bool pickUpItem(std::shared_ptr<Square> s);   // 
   virtual void moveEnemy();
   virtual void setDragonLocation(int row, int col);
};

#endif

