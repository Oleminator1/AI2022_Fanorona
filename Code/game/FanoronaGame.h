#ifndef AI2022_FANORONA_FANORONA_GAME_H
#define AI2022_FANORONA_FANORONA_GAME_H

#include "BoardGameAI/BoardGame.h"
#include "json.hpp"
#include "StoneMoves.h"

using json = nlohmann::json;

enum Direction { UpperRight = 1, Right = 2, LowerRight = 3, Bottom = 4, LowerLeft = 5, Left = 6, UpperLeft = 7, Top = 8, Invalid = -1 };

class FanoronaGame : BoardGame<FanoronaGame> {
    private:
        static int STARTING_GRID[5][9];
    public:
        // The Game Board
        int grid[5][9];

        // Game Functions
        void initializeGrid();
        void moveStone(int x1, int y1, int x2, int y2);
        Direction getDirection(int x1, int y1, int x2, int y2);
        void clearDiagonal(int direction, int row_2, int col_2, int player);
        void clearHorizontal(int direction, int row_2, int col_2, int player);
        void clearVertical(int direction, int row_2, int col_2, int player);

        // AI Functions
        bool hasWon_impl() const;
        bool isGameOver_impl() const;
        void makeMove_impl(Move n);
        void undoMove_impl();
        MoveGenerator moveGenerator_impl() const;

        // Debug & Helper Functions
        void printGrid();
};

#endif //AI2022_FANORONA_FANORONA_GAME_H
