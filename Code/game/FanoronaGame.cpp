#include "FanoronaGame.h"

int FanoronaGame::STARTING_GRID[5][9] = {{ 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                         { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                                         { 1, 2, 1, 2, 0, 1, 2, 1, 2 },
                                         { 2, 2, 2, 2, 2, 2, 2, 2, 2 },
                                         { 2, 2, 2, 2, 2, 2, 2, 2, 2 }};

FanoronaGame::FanoronaGame() { }
FanoronaGame::FanoronaGame(const FanoronaGame& g) {
    // Copy the vector of movements
    std::vector<Movement> movements = g.currentMove.movements;
    // Copy the struct of currentMove
    currentMove = { g.currentMove.player, movements };
    // Copy the game board over
    std::copy(&g.grid[0][0], &g.grid[0][0]+5*9, &grid[0][0]);
}

void FanoronaGame::startGame() {
    // set the board to the starting configuration
    std::copy(&FanoronaGame::STARTING_GRID[0][0], &FanoronaGame::STARTING_GRID[0][0]+5*9, &grid[0][0]);
    // player 1 starts
    std::vector<Movement> currentMovements;
    currentMove = { PLAYER_BLACK, currentMovements };
    //currentPlayer = PLAYER_WHITE;
}
void FanoronaGame::executeMovement(Movement m) {
    //std::cout << "Movement: (" << m.from.row << "," << m.from.col << ") => (" << m.to.row << "," << m.to.col << ") | Capturing: " << (m.isCapturing ? "Yes" : "No") << " | AttackType: " << (m.attackType ? "Withdraw" : "Attack") << std::endl;
    // Set the from position to empty as we're moving away from it
    grid[m.from.row][m.from.col] = 0;
    // If the move is capturing, we have to perform some more complicated stuff
    if(m.isCapturing) {
        // Get the direction of the clearing, reverse it if this is a withdraw move
        Direction d = m.attackType == ATTACK_APPROACH ? getDirection(m.from, m.to) : reverseDirection(getDirection(m.from, m.to));
        // If we're approaching we're clearing from the to-position, if we're withdrawing we're clearing from the from-position
        Position p = m.attackType == ATTACK_APPROACH ? m.to : m.from;
        // Clear the appropriate stones
        clearDirection(p, d, currentMove.player);
    }
    // Move the stone to the "to" position in any case
    grid[m.to.row][m.to.col] = currentMove.player;
    //std::cout << "Pushing into movements (" << currentMove.movements.size() << ")" << std::endl;
    // Add the movement to the current move
    currentMove.movements.push_back(m);
    //std::cout << "Movement finished" << std::endl;
}
void FanoronaGame::endMove() {
    std::vector<Movement> currentMovements;
    currentMove = { currentMove.player == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE, currentMovements };
}
int FanoronaGame::winner() {
    // Count the states of the board positions
    std::map<int, int> stateCount;
    stateCount[0] = 0; stateCount[PLAYER_WHITE] = 0; stateCount[PLAYER_BLACK] = 0;
    for(int row = 0; row < 5; row++){
        for(int col = 0; col < 9; col++) {
            stateCount[grid[row][col]]++;
        }
    }
    // White winning conditions
    if(stateCount[PLAYER_WHITE] > 0 && stateCount[PLAYER_BLACK] == 0) {
        return PLAYER_WHITE;
    }
    // Black winning conditions
    if(stateCount[PLAYER_BLACK] > 0 && stateCount[PLAYER_WHITE] == 0) {
        return PLAYER_WHITE;
    }
    // Draw conditions
    if(stateCount[PLAYER_BLACK] == 1 && stateCount[PLAYER_WHITE] == 1) {
        return DRAW;
    }
    // Otherwise, the game is still in progress
    return IN_PROGRESS;
}

Direction FanoronaGame::getDirection(Position const& from, Position const& to)
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
Direction FanoronaGame::reverseDirection(Direction d) {
    if(d <= 4){
        return (Direction)(d + 4);
    } else {
        return (Direction)(d - 4);
    }
}

void FanoronaGame::clearDirection(Position const& origin, Direction direction, int player) {
    // Copy the position from which we're going, it'll track where we're moving
    Position p = { origin.row, origin.col };
    // Move it once to the first enemy stone
    movePosition(p, direction);
    // Continue deleting stones in the direction as long as they're on the field and they're the enemy's (aka not ours and not empty)
    while(inBounds(p) && at(p) != player && at(p) != 0) {
        // Delete the stone
        grid[p.row][p.col] = 0;
        // Advance the position
        movePosition(p, direction);
    }
}


// Helper for moving a position into a direction
void FanoronaGame::movePosition(Position& p, Direction d) {
    switch(d) {
        case Direction::UpperRight: p.row -= 1; p.col += 1; break;
        case Direction::Right: p.col += 1; break;
        case Direction::LowerRight: p.row += 1; p.col += 1; break;
        case Direction::Bottom: p.row += 1; break;
        case Direction::LowerLeft: p.row += 1; p.col -= 1; break;
        case Direction::Left: p.col -=1; break;
        case Direction::UpperLeft: p.row -= 1; p.col -= 1; break;
        case Direction::Top: p.row -= 1; break;
        default: throw std::runtime_error("Cannot move position in unknown direction");
    }
}

Movement FanoronaGame::generateMovement(int row, int col, int deltaRow, int deltaCol, int player)
{
    // Check for approaching move
    Position approachPosition = { row + deltaRow * 2, col + deltaCol * 2 };
    if(inBounds(approachPosition) && at(approachPosition) != player && at(approachPosition) != 0) {
        return { {row, col}, {row+deltaRow, col+deltaCol}, true, ATTACK_APPROACH };
    }
    // Check for withdrawal move
    Position withdrawPosition = { row + (deltaRow * -1), col + (deltaCol * -1) };
    if (inBounds(withdrawPosition) && at(withdrawPosition) != player && at(withdrawPosition) != 0) {
        return { {row, col}, {row+deltaRow, col+deltaCol}, true, ATTACK_WITHDRAW };
    }
    // Otherwise, only a simple move is possible
    return { {row, col}, {row+deltaRow, col+deltaCol}, false, false };
    // Only simple move possible
}

std::vector<Movement> FanoronaGame::generateMovements(int row, int col, int player)
{
    // If the last movement wasnt capturing, we're straight-up done here
    if(currentMove.movements.size() > 0 && !currentMove.movements.back().isCapturing){
        std::vector<Movement> empty;
        return empty;
    }
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
    // If we have capture movements, we have to offer those, otherwise take the simple move list
    std::vector<Movement> movements = captureList.size() > 0 ? captureList : moveList;
    // Remove any already visited positions from the movements
    std::vector<Movement>::iterator it = movements.begin();
    while(it != movements.end()) {
        // Check if it's previously visited in the move
        bool removal = false;
        for(auto const& vm : currentMove.movements) {
            if(vm.from.row == it->to.row && vm.from.col == it->to.col) {
                removal = true; break;
            }
        }
        // Check if it's not pointing in the same direction as the last movement, if one exists
        if(currentMove.movements.size() > 0 && getDirection(currentMove.movements.back().from, currentMove.movements.back().to) == getDirection(it->from, it->to)) {
            removal = true;
        }
        // If removal is warranted, remove from the movements and point to the next element
        // Otherwise, advance the iterator
        if(removal) {
            it = movements.erase(it);
        }else{
            ++it;
        }
    }
    // Return the fruits of our labour
    return movements;
}
std::vector<Move> FanoronaGame::generateMoves(int player, std::vector<Move> moves) {
    if(moves.size() == 0){
        //std::cout << "Generating initial movements" << std::endl;
        // If this is the first run, get possible movements for all stones
        bool haveCapturing = false;
        for(int row = 0; row < 5; row++) {
            for(int col = 0; col < 9; col++) {
                // If it's not our stone, we can skip it
                if(at({ row, col }) != player) continue;
                // Generate possible movements
                auto movements = generateMovements(row, col, player);
                // If there's 0 movements available for this stone, skip it
                if(movements.size() == 0) continue;
                // If we aren't already in "capturing moves only" mode, check for any
                if(!haveCapturing){
                    for(auto const& m : movements) {
                        if(m.isCapturing){ haveCapturing = true; break; }
                    }
                }
                // Add to moves
                for(Movement movement : movements) {
                    std::vector<Movement> firstMoveMovements;
                    firstMoveMovements.push_back(movement);
                    moves.push_back({ player, firstMoveMovements });
                }
            }
        }
        // If we're in "capturing moves only" mode, remove anything that has non-capturing movements
        if(haveCapturing){
            std::vector<Move>::iterator it = moves.begin();
            while(it != moves.end()) {
                if(!it->movements[0].isCapturing) {
                    it = moves.erase(it);
                }else{
                    //std::cout << it->at(0).from.row << ", " << it->at(0).from.col << " -> " << it->at(0).to.row << ", " << it->at(0).to.col << " " << (it->at(0).attackType ? "Withdraw" : "Approach") << std::endl;
                    ++it;
                }
            }
        }
        //std::cout << moves.size() << " initial moves" << std::endl;
        // Call generateMoves on all subsequent runs
        /*std::vector<Move> resultMoves;
        for(auto move : moves) {
            //std::cout << "INITIAL MOVE" << std::endl;
            // Copy the game instance
            FanoronaGame g(*this);
            // Apply the movements
            //std::cout << move.movements.size() << " movements" << std::endl;
            for(auto movement : move.movements) { g.executeMovement(movement); }
            // Evaluate any further possible movements of this move
            std::vector<Move> moveMoves = g.generateMoves(player, moves);
            for(auto moveMove : moveMoves) { resultMoves.push_back(moveMove); }
        }*/
        return moves;
    }else{
        //std::cout << "Generating subsequent moves" << std::endl;
        // If this is a subsequent run, base all additional moves on existing ones
        /*std::vector<Move> localMoves;
        for(auto move : moves) { 
            std::vector<Movement> mm;
            for(auto movement : move.movements) { mm.push_back({ {movement.from.col, movement.from.row}, {movement.to.col, movement.to.row}, movement.isCapturing, movement.attackType }); }
            localMoves.push_back({ move.player, mm });
        }

        for(auto move : localMoves) {
            // ???
            if(move.movements.size() == 0) continue;
            // Copy se game instanz
            FanoronaGame g(*this);
            //std::cout << move.movements.size() << " movements" << std::endl;
            // Apply se movementz
            for(auto movement : move.movements) { g.executeMovement(movement); }
            // Generate new movementz based on ze last position of ze moves
            std::vector<Movement> newMovements = g.generateMovements(move.movements.back().to.row, move.movements.back().to.col, player);
            // Add new moves with all the new movements appended
            for(Movement newMovement : newMovements) {
                std::vector<Movement> ms;
                for(auto movement : move.movements) { ms.push_back({ {movement.from.col, movement.from.row}, {movement.to.col, movement.to.row}, movement.isCapturing, movement.attackType }); }
                ms.push_back(newMovement);
                moves.push_back({ player, ms });
            }
        }*/
        return moves;
    }
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

int FanoronaGame::at(Position const& p) {
    return grid[p.row][p.col];
}
bool FanoronaGame::inBounds(Position const& p) {
    return p.row >= 0 && p.row < 5 && p.col >= 0 && p.col < 9;
}
int FanoronaGame::currentPlayer() {
    return currentMove.player;
}