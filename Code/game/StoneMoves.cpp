
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

bool isStrongPosition(int X, int Y)
{
    // Check if stone has a strong or weak position
    return true;
}

bool emptyNeighbours(int X, int Y, bool strongPosition)
{
    // Check if stone has empty neighbours
    return false;
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
            if (emptyNeighbours(row, column, strongPosition) == false)
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
   
}
