#ifndef AI2022_FANORONA_FANORONA_GAME_H
#define AI2022_FANORONA_FANORONA_GAME_H

#include "BoardGameAI/BoardGame.h"
#include "json.hpp"
using json = nlohmann::json;

class FanoronaGame : BoardGame<FanoronaGame> {
    public:
        int board[9][5];
        json as_json();

        bool hasWon_impl() const;
        bool isGameOver_impl() const;
        void makeMove_impl(Move n);
        void undoMove_impl();

        class MoveGenerator
        {
            private:
                int index;
                //static constexpr std::array<Move, 7> orderedMoves = { { 4,3,5,2,6,1,7 } };
            public:
                MoveGenerator();
                Move nextMove();
        };
        MoveGenerator moveGenerator_impl() const;
};


#endif //AI2022_FANORONA_FANORONA_GAME_H
