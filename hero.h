#ifndef _HERO_H_
#define _HERO_H_

#include "square.h"
#include "character.h"
#include "potion.h"
#include "gold.h"
#include <string>
#include <vector>
#include <memory>

class Floor;
class Enemy;

class Hero: public std::enable_shared_from_this<Hero>, public Character {
	bool attackedMerchant;
	bool onStairway;
	bool validMove(std::string direction);
	int gold;
	std::string heroType;
 protected:
	int originalHp;                              // hp when hero spawned on floor
	int originalAtk;                             // atk when hero spawned on floor
	int originalDef;                             // def when hero spawned on floor
	std::string lastAction;                      // last action of the hero
 public:
   Hero(int row, int col, std::string heroType, Floor *theFloor, int hp, int atk, int def);

	bool hasAttackedMerchant();
	bool isHero() override;
	bool isOnStairway();                         // if the hero is standing on a stairway
	bool pickUpGold(std::shared_ptr<Gold> g);    // adds gold to heros worth
	bool pickUpItem(std::shared_ptr<Square> s);  // picks up and item

	int getGold();
	int getNSCoordinate(std::string direction);  // returns row reflective of direction 
	int getEWCoordinate(std::string direction);  // returns col reflective of direction

	std::string getHeroType();                   
	std::string getLastAction();
	std::string printHeroType();

	std::vector<std::shared_ptr<Potion>> potionInventory;       // potions that hero has used
   std::vector<std::shared_ptr<Potion>> storedPotionInventory; // potions that hero has picked up
	
   void addGold(int newGold);                   // adds gold to heros worth
	void attack(std::string direction);          // attacks enemy in the direction
	void addToLastAction(std::string newLastAction);   // used for printing the last action
	void move(std::string direction);            // moves hero in the given direction
	void removeEnemy(int row, int col);          // removes enemy from enemies vector
	void reset();
	void resetLastAction();
	void resetOnStairway();
	void setFloor(Floor *newFloor);
	void setHeroType(std::string type);
	void setOgAtk();
	void setOgDef();
	void usePotion(std::string direction);       // use the potion in the given direction
   void storePotion(std::string direction);     // pick up and store the potion in the given directions
   
   virtual void useStoredPotion();              // uses the last potion added in storedPotionnInventory
	virtual void pickUpPotion(std::shared_ptr<Potion> p); // adds potions effects to hero's stats
	virtual void printScore();
	virtual void strikeEnemy(std::shared_ptr<Enemy> e);   // attacks the enemy
};

#endif

