#include <iostream>
#include <string>
#include <sstream>
#include "controller.h"

using namespace std;

int main(int argc, char* argv[]) { 
   cin.exceptions(ios::failbit|ios::eofbit);
   try {
      if (argc == 2) {
         Controller c{argv[1], false};
         c.playGame();
      } else {
         Controller c{"defaultFloor.txt", true};
         c.playGame();
      }
   } 
   catch (int i) {}
   catch (ios::failure) {}
}   

