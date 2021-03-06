#ifndef AI2022_FANORONA_AI_PLAYER_H
#define AI2022_FANORONA_AI_PLAYER_H

#include <vector>
#include <iostream>
#include "GamePlayer.h"
#include "../FanoronaGame.h"
#include "../util/Structs.h"

using json = nlohmann::json;

/*struct MoveScore {
    Move move;
    int score;
};*/

class AiPlayer : public GamePlayer {
    private:
        int height;
        Move bestMove;

        int evaluate(FanoronaGame& state);
        int minimax(FanoronaGame state, int player, Move executedMove, int depth, int alpha, int beta);
    public:
        AiPlayer(int p_id, FanoronaGame& p_game, int p_height);
        void turnStarted() override;
        json status();
        bool isAi() override;
};

#endif //AI2022_FANORONA_AI_PLAYER_H
