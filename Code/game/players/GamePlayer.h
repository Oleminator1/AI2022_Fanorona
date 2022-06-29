#ifndef AI2022_FANORONA_GAME_PLAYER_H
#define AI2022_FANORONA_GAME_PLAYER_H

#include <vector>
#include "../FanoronaGame.h"
#include "../util/Structs.h"

using json = nlohmann::json;

class GamePlayer {
    public:
        int id;
        FanoronaGame* game;

        GamePlayer(int p_id, FanoronaGame& p_game);
        virtual void stoneSelected(Position const& p);
        virtual void turnStarted();
        virtual json status();
        virtual bool isAi() = 0;
};

#endif //AI2022_FANORONA_GAME_PLAYER_H
