#include "StoneMoves.h"
#include <iostream>
#include <vector>

using namespace std;

MoveGenerator::MoveGenerator(const FanoronaGame* p_game) {
    game = p_game;
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

bool MoveGenerator::capturingMoves(int grid[5][9], int row, int col, int X, int Y, int player)
{
    // Check for capturing move
    if ((grid[row + X * 2][col + Y * 2] != player) && (grid[row + X * 2][col + Y * 2] != 0)) {
        return true;
    }
    // Check for withdrawl move
    else if ((grid[row + (X * -1)][col + (Y * -1)] != player) && (grid[row + (X * -1)][col + (Y * -1)] != 0)) {
        return true;
    }
    // Only simple move possible
    else {
        return false;
    }
}

bool MoveGenerator::emptyNeighbours(int grid[5][9], int row, int col, vector<vector<int>>& captureList, vector<vector<int>>& moveList, int player, bool strongPosition)
{
     int count = 0;
    // First 4 values for cross Nhood, last four for diagnoals
    int row_neighbours[] = { 0, 0, -1, +1, -1, -1, +1, +1 };
    int col_neighbours[] = {-1, +1, 0, 0, -1, +1, -1, +1  };

    for (int i = 0; i < 9; i++) {
        if (strongPosition == false && i > 3) {
            // Stops loop if stone is not in strong position
            break;
        }
        if (((row + row_neighbours[i]) < 0) || ((row + row_neighbours[i]) > 8)) {
        // Row is out of bounds
            continue;
        }
        else if (((col + col_neighbours[i]) < 0) || ((col + col_neighbours[i]) > 8)) {
            // Column is out of bounds
            continue;
        }
        else if (grid[row+row_neighbours[i]][col+col_neighbours[i]] == 0) {
            // Add Stone to list for possible moves
            count += 1;
            vector<int> v1;
            v1.push_back(row);
            v1.push_back(col);
            if (capturingMoves(grid, row, col, row_neighbours[i], col_neighbours[i], player) == true) {
                captureList.push_back(v1);
                // Stop the loop if one entrance was done?
            }
            else {
                moveList.push_back(v1);
                // Only one entrance?
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
