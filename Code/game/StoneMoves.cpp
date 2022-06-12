#include "StoneMoves.h"
#include <iostream>
#include <vector>

using namespace std;

void initializeGrid(int grid[5][9])
{
    // Fill the empty grid with stones
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 9; column++) {
            if (row == 0 || row == 1) {
                grid[row][column] = 1;
            }
            else if (row == 2) {
                if ((column % 2 == 1 && column < 5) || (column % 2 == 0 && column > 5)) {
                    grid[row][column] = 1;
                }
                else if (column != 4) {
                    grid[row][column] = 2;
                }
                else {
                    grid[row][column] = 0;
                }
            }
            else if (row == 3 || row == 4) {
                grid[row][column] = 2;
            }
        }
    }
}

void printGrid(int grid_[5][9])
{
    // Print the grid in the console
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 9; column++) {
            cout << grid_[row][column];
            if (column < 8) {
                cout << " - ";
            }
            if (column == 8) {
                cout << endl;
                if (row == 0 || row == 2) {
                    cout << "| \\ | / | \\ | / | \\ | / | \\ | / |" << endl;
                }
                else if (row == 1 || row == 3) {
                    cout << "| / | \\ | / | \\ | / | \\ | / | \\ |" << endl;
                }
            }
        }
    }
}

bool isStrongPosition(int row, int col)
// Check if stone has a strong or weak position
{
    if ((row%2) == 0) {
        if ((col%2) == 0) {
            return true;
        }
        else {
            return false;
        }        
    }
    else {
        if ((col%2) == 0) {
            return false;
        }
        else {
            return true;
        }       
    }
}

bool emptyNeighbours(int grid[5][9], int row, int col, bool strongPosition)
{
    int count = 0;
    if (strongPosition) {
        //check 3x3 Nhood
        for (int i = row-1; i < row+2; i++) {
            if ((i < 0) or (i > 8)) {
                //Out of bounds
                continue;
            }
            for (int j = col-1; j < col+2; j++) {
                if ((j < 0) or (j > 4)) {
                    //Out of bounds
                    continue;
                }
                if (grid[i][j] == 0) {
                    count += 1;   
                }
            }
        }
    }
                    
    else {
        //Check cross Nhood
        if (row-1 < 0) {
            //Out of bounds
            continue;
        }
        else {
            if (grid[row-1][col] == 0) {
                    count += 1;   
            }
        }
        if (col-1 < 0) {
            //Out of bounds
            continue;
        }
        else {
            if (grid[row][col-1] == 0) {
                    count += 1;   
            }
        }
        if (col+1 > 8) {
            //Out of bounds
            continue;
        }
        else {
            if (grid[row][col+1] == 0) {
                    count += 1;   
            }
        }
        if (row+1 > 4) {
            //Out of bounds
            continue;
        }
        else {
            if (grid[row+1][col] == 0) {
                    count += 1;   
            }
        }
        
    }
    if (count > 0) {
        return true;
    }
    else {
        return false;
    }
}

void capturingMoves(int X, int Y, bool strongPosition, vector<vector<int>> captureList, vector<vector<int>> moveList)
{
    // Store capturing and simple movements in lists
}

void showPossibleStones(vector<vector<int>> possibleMoves)
{
    // Print either all stones that can perform capturing or simple moves on the console
    cout << "Select your next stone" << endl;
    for (int i = 0; i < possibleMoves.size(); i++) {
        for (int j = 0; j < possibleMoves[i].size(); j++) {
            cout << "[" << possibleMoves[i][j] << "]";
        }
        cout << endl;
    }
}


void evaluatePlayerStones(int player, int grid[5][9])
{
    // Evaluate all possibilites for the player
    bool strongPosition;
    vector<vector<int>> captureList;
    vector<vector<int>> moveList;

    // Evaluate possibilites for each stone
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 9; column++) {
            // Check if stone and player value are equal
            if (grid[row][column] != player) {
                continue;
            }
            // Check if stone has a strong or weak position
            if (isStrongPosition(row, column) == true) {
                strongPosition = true;
            }
            else {
                strongPosition = false;
            }
            // Check if stone has empty neighbours
            if (emptyNeighbours(grid, row, column, strongPosition) == false)
            {
                continue;
            }
            // Store capturing and simple movements in lists
            capturingMoves(row, column, strongPosition, captureList, moveList);
        }
    }
    // Vector experiments
    vector<int> v1;
    vector<int> v2;
    int num1 = 4, num2 = 8;
    v1.push_back(num1);
    v1.push_back(num2);
    captureList.push_back(v1);

    // Print either all stones that can perform capturing or simple moves on the console
    if (captureList.empty() == false) {
        showPossibleStones(captureList);
    }
    else {
        showPossibleStones(moveList);
    }
}
      
                    
void moveStone(int x1, int y1, int x2, int y2, int grid[5][9])
{
    // x1, y1 are the old and x2, y2 the new position
    grid[x2][y2] = grid[x1][y1];
    grid[x1][y1] = 0;
}


int getDirection(int x1, int y1, int x2, int y2)
{
    // return direction of movement
    // upper right
    if (x2 < x1 && y2 > y1) { return 1; }
    // right
    if (x2 == x1 && y2 > y1) { return 2; }
    // lower right
    if (x2 > x1 && y2 > y1) { return 3; }
    // bottom
    if (x2 > x1 && y2 == y1) { return 4; }
    // lower left
    if (x2 > x1 && y2 < y1) { return 5; }
    // left
    if (x2 == x1 && y2 < y1) { return 6; }
    // upper left
    if (x2 < x1 && y2 < y1) { return 7; }
    // top
    if (x2 < x1 && y2 == y1) { return 8; }
}

void clear_horizontal(int grid[5][9], int direction, int row_2, int col_2, int player) 
{
    if (direction == 2) {
        while ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
            grid[row_2][col_2] = 0;
            col_2 += 1;
            if (col_2 == 9) {
                break;
            }
        }
    }
    if (direction == 6) {
        while ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
            grid[row_2][col_2] = 0;
            col_2 -= 1;
            if (col_2 == -1) {
                break;
            }
        }
    }
    return;
}
                
void clear_vertical(int grid[5][9], int direction, int row_2, int col_2, int player) 
{
    if (direction == 4) {
        while ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
            grid[row_2][col_2] = 0;
            row_2 += 1;
            if (row_2 == 5) {
                break;
            }
        }
    }
    if (direction == 8) {
        while ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
            grid[row_2][col_2] = 0;
            row_2 -= 1;
            if (row_2 == -1) {
                break;
            }
        }
    }
    return;
}

                    
int main()
{
    int grid[5][9];
    int player = 1;

    // Fill the empty grid with stones
    initializeGrid(grid);

    // Print the grid in the console
    printGrid(grid);

    // Evaluate all possibilites for the player
    EvaluatePlayerStones(player, grid);
    
    // Move stone from former to new position
    moveStone(1, 1, 2, 2, grid);

    // Print the grid in the console
    printGrid(grid);

    // Get direction of movement
    cout << getDirection(1, 1, 2, 2);
   
}
