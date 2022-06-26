/*#include "StoneMoves.h"
#include <iostream>
#include <vector>

using namespace std;

MoveGenerator::MoveGenerator(const FanoronaGame* p_game) {
    game = p_game;
}
Move MoveGenerator::nextMove() {
    return AI_INFINITE;
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
            if (game->isStrongPosition(row, column) == true) {
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
}*/

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
