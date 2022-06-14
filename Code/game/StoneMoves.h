#ifndef _STONEMOVES_H
#define _STONEMOVES_H

#include <iostream>
#include <vector>

using namespace std;


class MoveGenerator {
  private:
    /*Board ? ->  Any global constants*/
    int test = 0;
    //int grid[5][9] = 0;
    //MoverGenerator::grid as function arg?  
  
  public:
    /*Getter for Board?*/
  
    /*Constructor, Destructor required?*/

    void initializeGrid(int grid[5][9]);

    void printGrid(int grid_[5][9]);

    bool isStrongPosition(int row, int col);

    bool emptyNeighbours(int grid[5][9], int row, int col, bool strongPosition);

    void capturingMoves(int X, int Y, bool strongPosition, vector<vector<int>> captureList, vector<vector<int>> moveList);

    void showPossibleStones(vector<vector<int>> possibleMoves);

    void evaluatePlayerStones(int player, int grid[5][9]); 

    void moveStone(int x1, int y1, int x2, int y2, int grid[5][9]);

    int getDirection(int x1, int y1, int x2, int y2);
    
    void clear_diagonal(int grid[5][9], int direction, int row_2, int col_2, int player);
    
    void clear_horizontal(int grid[5][9], int direction, int row_2, int col_2, int player);
  
    void clear_vertical(int grid[5][9], int direction, int row_2, int col_2, int player);
  
    /*Extend list as sson as function is implemented!*/
  
};

#endif
