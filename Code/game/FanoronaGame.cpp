#include "FanoronaGame.h"

int FanoronaGame::STARTING_GRID[5][9] = {{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                         { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                         { 1, 2, 1, 2, 0, 1, 2, 1, 2 },
                                         { 2, 2, 2, 2, 2, 2, 2, 2, 2 },
                                         { 2, 2, 2, 2, 2, 2, 2, 2, 2 }};

void FanoronaGame::initializeGrid() {
    std::copy(&FanoronaGame::STARTING_GRID[0][0], &FanoronaGame::STARTING_GRID[0][0]+5*9, &grid[0][0]);
}
void FanoronaGame::moveStone(int x1, int y1, int x2, int y2)
{
    // x1, y1 are the old and x2, y2 the new position
    grid[x2][y2] = grid[x1][y1];
    grid[x1][y1] = 0;
    int dir = getDirection(x1, y1, x2, y2);
    if ((dir % 2) != 0) {
        clearDiagonal(dir, x2, y2, grid[x2][y2]);
    }
    else {
        if ((dir % 4) == 0) {
            clearVertical(dir, x2, y2, grid[x2][y2]);
        }
        else {
            clearHorizontal(dir, x2, y2, grid[x2][y2]);
        }
    }
}
Direction FanoronaGame::getDirection(int x1, int y1, int x2, int y2)
{
    // return direction of movement
    // upper right
    if (x2 < x1 && y2 > y1) { return Direction::UpperRight; }
    // right
    if (x2 == x1 && y2 > y1) { return Direction::Right; }
    // lower right
    if (x2 > x1 && y2 > y1) { return Direction::LowerRight; }
    // bottom
    if (x2 > x1 && y2 == y1) { return Direction::Bottom; }
    // lower left
    if (x2 > x1 && y2 < y1) { return Direction::LowerLeft; }
    // left
    if (x2 == x1 && y2 < y1) { return Direction::Left; }
    // upper left
    if (x2 < x1 && y2 < y1) { return Direction::UpperLeft; }
    // top
    if (x2 < x1 && y2 == y1) { return Direction::Top; }
    // default case
    return Direction::Invalid;
}

void FanoronaGame::clearDiagonal(int direction, bool attackType, int row_2, int col_2, int player)
{   
    if (attackType == false) {
        if ((direction == 1) || (direction == 3)) {
            direction += 4;
        } else {
            direction -= 4;
        }
    }
    if (direction == 1) {
        while (1) {
            row_2 -= 1;
            col_2 += 1;
            if ((row_2 == -1) || (col_2 == 9)) {
                break;
            }
            if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
                grid[row_2][col_2] = 0;
            }
            else {
                break;
            }

        }
    }
    if (direction == 3) {
        while (1) {
            row_2 += 1;
            col_2 += 1;
            if ((row_2 == 5) || (col_2 == 9)) {
                break;
            }
            if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
                grid[row_2][col_2] = 0;
            }
            else {
                break;
            }
        }
    }
    if (direction == 5) {
        while (1) {
            row_2 += 1;
            col_2 -= 1;
            if ((row_2 == 5) || (col_2 == -1)) {
                break;
            }
            if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
                grid[row_2][col_2] = 0;
            }
            else {
                break;
            }
        }
    }
    if (direction == 7) {
        while (1) {
        row_2 -= 1;
        col_2 -= 1;
        if ((row_2 == -1) || (col_2 == -1)) {
            break;
        }
        if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
            grid[row_2][col_2] = 0;
        }
        else {
            break;
        }
        }
    }
    return;
}

void FanoronaGame::clearHorizontal(int direction, bool attackType, int row_2, int col_2, int player)
{   
    if (attackType == false) {
        if (direction == 2) {
            direction += 4;
        }
        else {
            direction -= 4;
        }
    }
    if (direction == 2) {
        while (1) {
            col_2 += 1;
            if (col_2 == 9) {
                break;
            }
            if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
                grid[row_2][col_2] = 0;
            }
            else {
                break;
            }
        }
    }
    if (direction == 6) {
        while (1) {
            col_2 -= 1;
            if (col_2 == -1) {
                break;
            }
            if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
                grid[row_2][col_2] = 0;
            }
            else {
                break;
            }
        }
    }
    return;
}

void FanoronaGame::clearVertical(int direction, bool attackType=true, int row_2, int col_2, int player)
{
    if (attackType == false) {
        if (direction == 4) {
            direction += 4;
        }
        else {
            direction -= 4;
        }
    } 
    if (direction == 4) {
        while (1) {
            row_2 += 1;
            if (row_2 == 5) {
                break;
            }
            if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
                grid[row_2][col_2] = 0;
            }
            else {
                break;
            }
        }
    }
    if (direction == 8) {
        while (1) {
            row_2 -= 1;
            if (row_2 == -1) {
                break;
            }
            if ((grid[row_2][col_2] != 0) && (grid[row_2][col_2] != player)) {
                grid[row_2][col_2] = 0;
            }
            else {
                break;
            }
        }
    }
    return;
}

bool FanoronaGame::hasWon_impl() const {
    return false;
}
bool FanoronaGame::isGameOver_impl() const {
    return false;
}
void FanoronaGame::makeMove_impl(Move n) {

}
void FanoronaGame::undoMove_impl() {

}
MoveGenerator FanoronaGame::moveGenerator_impl() const {
    return MoveGenerator(this);
}

void FanoronaGame::printGrid() {
    // Print the grid in the console
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 9; column++) {
            cout << grid[row][column];
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
