#include "StoneMoves.h"
#include <iostream>
#include <vector>

using namespace std;

MoveGenerator::MoveGenerator(const FanoronaGame* game) {

}
Move MoveGenerator::nextMove() {
    return AI_INFINITE;
}

bool MoveGenerator::isStrongPosition(int row, int col)
// Check if stone has a strong or weak position
{
    if ((row % 2) == 0) {
        if ((col % 2) == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if ((col % 2) == 0) {
            return false;
        }
        else {
            return true;
        }
    }
}

bool MoveGenerator::emptyNeighbours(int grid[5][9], int row, int col, bool strongPosition)
{
    int count = 0;
    if (strongPosition) {
        //check 3x3 Nhood
        for (int i = row - 1; i < row + 2; i++) {
            if ((i < 0) || (i > 8)) {
                //Out of bounds
                continue;
            }
            for (int j = col - 1; j < col + 2; j++) {
                if ((j < 0) || (j > 4)) {
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
        if ((row - 1 >= 0) && (grid[row - 1][col] == 0)) {
            count += 1;
        }

        if ((col - 1 >= 0) && (grid[row][col - 1] == 0)) {
            count += 1;
        }

        if ((col + 1 <= 8) && (grid[row][col + 1] == 0)) {
            count += 1;
        }

        if ((row + 1 <= 4) && (grid[row + 1][col] == 0)) {
            count += 1;
        }
    }


    if (count > 0) {
        return true;
    }
    else {
        return false;
    }
}

void MoveGenerator::capturingMoves(int X, int Y, bool strongPosition, vector<vector<int>> captureList, vector<vector<int>> moveList)
{
    // Store capturing and simple movements in lists
}

void MoveGenerator::showPossibleStones(vector<vector<int>> possibleMoves)
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


void MoveGenerator::evaluatePlayerStones(int player, int grid[5][9])
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

/*int main()
{
    int grid[5][9];
    int player = 2;

    // Fill the empty grid with stones
    initializeGrid(grid);

    // Print the grid in the console
    printGrid(grid);

    // Evaluate all possibilites for the player
    EvaluatePlayerStones(player, grid);

    // Move stone from former to new position
    moveStone(3, 5, 2, 4, grid);

    // Print the grid in the console
    printGrid(grid);

    // Get direction of movement
    cout << getDirection(1, 1, 2, 2);
}*/
