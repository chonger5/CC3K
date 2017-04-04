#include "shade.h"
#include "floor.h"
#include "hero.h"
#include <iostream>

using namespace std;

Shade::Shade(int row, int col, Floor *theFloor): 
   Hero{row, col, "s", theFloor,125, 25, 25} {}

void Shade::printScore() {
	cout << "Score: " << static_cast<double>(getGold()) * 1.5 << endl;
}

