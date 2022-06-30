#ifndef AI2022_FANORONA_FANORONA_GAME_H
#define AI2022_FANORONA_FANORONA_GAME_H

#include "json.hpp"
#include "util/Structs.h"
#include <stdexcept>
#include <iostream>

#define IN_PROGRESS -1
#define DRAW 0
#define PLAYER_WHITE 1
#define PLAYER_BLACK 2

#define ATTACK_WITHDRAW true
#define ATTACK_APPROACH false

using json = nlohmann::json;

class FanoronaGame {
    private:
        static int STARTING_GRID[5][9];
    public:
        // The Game Board
        int grid[5][9];
        // Current Move
        Move currentMove;

        FanoronaGame();
        FanoronaGame(const FanoronaGame& g);

        // Game Functions
        void startGame();
        //std::vector<Movement> selectStone(Position pos);
        //void moveStone(Movement m);
        Direction getDirection(Position const& from, Position const& to);
        Direction reverseDirection(Direction d);
        void clearDirection(Position const& origin, Direction direction, int player);
        //void clearDiagonal(int direction, bool attackType, int row_2, int col_2, int player);
        //void clearHorizontal(int direction, bool attackType, int row_2, int col_2, int player);
        //void clearVertical(int direction, bool attackType, int row_2, int col_2, int player);
        bool isStrongPosition(int row, int col);
        Movement generateMovement(int row, int col, int deltaRow, int deltaCol, int player);
        std::vector<Movement> generateMovements(int row, int col, int player);
        void generateMoves(int player, std::vector<Move>& moves);

        void executeMovement(Movement const& m);
        void endMove();

        int winner();

        // Debug & Helper Functions
        int at(Position const& p);
        bool inBounds(Position const& p);
        void movePosition(Position& p, Direction d);
        int currentPlayer();
        //void printGrid();
};

#endif //AI2022_FANORONA_FANORONA_GAME_H
