#include "cell.h"
#include "path.h"
#include "square.h"
#include <string>

using namespace std;

Path::Path(int row, int col, string type, Floor *theFloor): Cell(row, col, type, theFloor) {}

bool Path::validDestination() {
   return true;
}

