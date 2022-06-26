/*#ifndef _STONEMOVES_H
#define _STONEMOVES_H

#include <iostream>
#include <vector>

#include "BoardGameAI/BoardGame.h"

using namespace std;

// Forward declaration
class FanoronaGame;

class MoveGenerator {
  private:
    //Board ? ->  Any global constants
    int index;
    int test = 0;
    const FanoronaGame* game;
    //int grid[5][9] = 0;
    //MoverGenerator::grid as function arg?  
  
  public:
    //Getter for Board?
  
    //Constructor, Destructor required?
    MoveGenerator(const FanoronaGame* p_game);

    Move nextMove();

    //void evaluatePlayerStones(int player, int grid[5][9]); 
  
    //Extend list as sson as function is implemented!
  
};

#endif
*/