#ifndef AI2022_FANORONA_FANORONA_GAME_H
#define AI2022_FANORONA_FANORONA_GAME_H

#include "BoardGameAI/BoardGame.h"
#include "json.hpp"
#include "StoneMoves.h"
#include <stdexcept>

#define PLAYER_WHITE 1
#define PLAYER_BLACK 2

#define ATTACK_WITHDRAW true
#define ATTACK_APPROACH false

using json = nlohmann::json;

enum Direction { UpperRight = 1, Right = 2, LowerRight = 3, Bottom = 4, LowerLeft = 5, Left = 6, UpperLeft = 7, Top = 8, Invalid = -1 };

struct Position { int row; int col; };

struct Movement {
    Position from;
    Position to;
    bool isCapturing;
    bool attackType;
};
struct Move {
    int player;
    std::vector<Movement> movements;
};

class FanoronaGame : BoardGame<FanoronaGame> {
    private:
        static int STARTING_GRID[5][9];
        int currentPlayer;
        Move currentMove;
    public:
        // The Game Board
        int grid[5][9];

        // Game Functions
        void startGame();
        std::vector<Movement> FanoronaGame::selectStone(Position pos);
        void moveStone(Movement m);
        Direction getDirection(Position from, Position to);
        void clearDiagonal(int direction, bool attackType, int row_2, int col_2, int player);
        void clearHorizontal(int direction, bool attackType, int row_2, int col_2, int player);
        void clearVertical(int direction, bool attackType, int row_2, int col_2, int player);
        bool isStrongPosition(int row, int col);
        Movement generateMovement(int row, int col, int deltaRow, int deltaCol, int player);
        std::vector<Movement> generateMovements(int row, int col, int player);

        // AI Functions
        bool hasWon_impl() const;
        bool isGameOver_impl() const;
        void makeMove_impl(Move n);
        void undoMove_impl();
        MoveGenerator moveGenerator_impl() const;

        // Debug & Helper Functions
        int at(Position p);
        void printGrid();
};

#endif //AI2022_FANORONA_FANORONA_GAME_H
