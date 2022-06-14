#ifndef _STONEMOVES_H
#define _STONEMOVES_H

#include <iostream>
#include <vector>

#include "BoardGameAI/BoardGame.h"

using namespace std;

// Forward declaration
class FanoronaGame;

class MoveGenerator {
  private:
    /*Board ? ->  Any global constants*/
    int index;
    int test = 0;
    //int grid[5][9] = 0;
    //MoverGenerator::grid as function arg?  
  
  public:
    /*Getter for Board?*/
  
    /*Constructor, Destructor required?*/
    MoveGenerator(const FanoronaGame* game);

    Move nextMove();

    bool isStrongPosition(int row, int col);

    bool emptyNeighbours(int grid[5][9], int row, int col, bool strongPosition);

    void capturingMoves(int X, int Y, bool strongPosition, vector<vector<int>> captureList, vector<vector<int>> moveList);

    void showPossibleStones(vector<vector<int>> possibleMoves);

    void evaluatePlayerStones(int player, int grid[5][9]); 
  
    /*Extend list as sson as function is implemented!*/
  
};

#endif
