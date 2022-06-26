#include "FanoronaGame.h"

int FanoronaGame::STARTING_GRID[5][9] = {{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                         { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                         { 1, 2, 1, 2, 0, 1, 2, 1, 2 },
                                         { 2, 2, 2, 2, 2, 2, 2, 2, 2 },
                                         { 2, 2, 2, 2, 2, 2, 2, 2, 2 }};

void FanoronaGame::startGame() {
    // set the board to the starting configuration
    std::copy(&FanoronaGame::STARTING_GRID[0][0], &FanoronaGame::STARTING_GRID[0][0]+5*9, &grid[0][0]);
    // player 1 starts
    currentPlayer = PLAYER_WHITE;
}
std::vector<Movement> FanoronaGame::selectStone(Position pos) {
    // Verify the stone is of the current player
    if(at(pos) != currentPlayer) throw std::runtime_error("Cannot select an empty stone or stone of the non-current player");
    // Verify the stone is moveable
    auto movements = generateMovements(pos.row, pos.col, currentPlayer);
    if(movements.size() == 0) throw std::runtime_error("Cannot select a stone with no possible movements");
    // Return the list of possible movements straight away, while we have it
    return movements;
}
void FanoronaGame::moveStone(Movement m)
{
    // Verify the stone at position 1 is of the current player
    if(grid[m.from.row][m.from.col] != currentPlayer) throw std::runtime_error("Cannot move a piece of the non-current player");
    // Verify we're moving exactly one position
    if(abs(m.from.row - m.to.row) + abs(m.from.col - m.to.col) != 1) throw std::runtime_error("Pieces must be moved exactly one position");
    // row1, col1 are the old and row2, col2 the new position
    // assign the new positions
    grid[m.to.row][m.to.col] = grid[m.from.row][m.from.col];
    grid[m.from.row][m.from.col] = 0;
    int dir = getDirection(m.from, m.to);
    if ((dir % 2) != 0) {
        clearDiagonal(dir, m.attackType, m.to.row, m.to.col, currentPlayer);
    }
    else {
        if ((dir % 4) == 0) {
            clearVertical(dir, m.attackType, m.to.row, m.to.col, currentPlayer);
        }
        else {
            clearHorizontal(dir, m.attackType, m.to.row, m.to.col, currentPlayer);
        }
    }
}
Direction FanoronaGame::getDirection(Position from, Position to)
{
    // return direction of movement
    // upper right
    if (to.row < from.row && to.col > from.col) { return Direction::UpperRight; }
    // right
    if (to.row == from.row && to.col > from.col) { return Direction::Right; }
    // lower right
    if (to.row > from.row && to.col > from.col) { return Direction::LowerRight; }
    // bottom
    if (to.row > from.row && to.col == from.col) { return Direction::Bottom; }
    // lower left
    if (to.row > from.row && to.col < from.col) { return Direction::LowerLeft; }
    // left
    if (to.row == from.row && to.col < from.col) { return Direction::Left; }
    // upper left
    if (to.row < from.row && to.col < from.col) { return Direction::UpperLeft; }
    // top
    if (to.row < from.row && to.col == from.col) { return Direction::Top; }
    // default case
    return Direction::Invalid;
}

void FanoronaGame::clearDiagonal(int direction, bool attackType, int row_2, int col_2, int player)
{   
    if (attackType == ATTACK_APPROACH) {
        if ((direction == Direction::UpperRight) || (direction == Direction::LowerRight)) {
            direction += 4;
        } else {
            direction -= 4;
        }
    }
    if (direction == Direction::UpperRight) {
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
    if (direction == Direction::LowerRight) {
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
    if (direction == Direction::LowerLeft) {
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
    if (direction == Direction::UpperLeft) {
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
    if (attackType == ATTACK_APPROACH) {
        if (direction == Direction::Right) {
            direction += 4;
        }
        else {
            direction -= 4;
        }
    }
    if (direction == Direction::Right) {
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
    if (direction == Direction::Left) {
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

void FanoronaGame::clearVertical(int direction, bool attackType, int row_2, int col_2, int player)
{
    if (attackType == ATTACK_APPROACH) {
        if (direction == Direction::Bottom) {
            direction += 4;
        }
        else {
            direction -= 4;
        }
    } 
    if (direction == Direction::Bottom) {
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

Movement FanoronaGame::generateMovement(int row, int col, int deltaRow, int deltaCol, int player)
{
    // Check for approaching move
    if ((grid[row + deltaRow * 2][col + deltaCol * 2] != player) && (grid[row + deltaRow * 2][col + deltaCol * 2] != 0)) {
        return { {row, col}, {row+deltaRow, col+deltaCol}, true, ATTACK_APPROACH };
    }
    // Check for withdrawal move
    else if ((grid[row + (deltaRow * -1)][col + (deltaCol * -1)] != player) && (grid[row + (deltaRow * -1)][col + (deltaCol * -1)] != 0)) {
        return { {row, col}, {row+deltaRow, col+deltaCol}, true, ATTACK_WITHDRAW };
    }
    // Only simple move possible
    else {
        return { {row, col}, {row+deltaRow, col+deltaCol}, false, false };
    }
}

std::vector<Movement> FanoronaGame::generateMovements(int row, int col, int player)
{
    int count = 0;
    bool strongPosition = isStrongPosition(row, col);
    std::vector<Movement> captureList;
    std::vector<Movement> moveList;
    // First 4 values for cross Nhood, last four for diagonals
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
            // Generate the movement if the neighbor is empty (e.g. a move is possible)
            count += 1;
            Movement m = generateMovement(row, col, row_neighbours[i], col_neighbours[i], player);
            if (m.isCapturing) {
                captureList.push_back(m);
                // Stop the loop if one entrance was done?
            }
            else {
                moveList.push_back(m);
                // Only one entrance?
            }
        }
    }
    return captureList.size() > 0 ? captureList : moveList;
}

bool FanoronaGame::isStrongPosition(int row, int col)
{
    // Check if stone has a strong or weak position
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

/*void FanoronaGame::printGrid() {
    // Print the grid in the console
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 9; column++) {
            std::cout << grid[row][column];
            if (column < 8) {
                std::cout << " - ";
            }
            if (column == 8) {
                std::cout << std::endl;
                if (row == 0 || row == 2) {
                    std::cout << "| \\ | / | \\ | / | \\ | / | \\ | / |" << std::endl;
                }
                else if (row == 1 || row == 3) {
                    std::cout << "| / | \\ | / | \\ | / | \\ | / | \\ |" << std::endl;
                }
            }
        }
    }
}*/
int FanoronaGame::at(Position p) {
    return grid[p.row][p.col];
}
