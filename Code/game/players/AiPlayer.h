#ifndef AI2022_FANORONA_AI_PLAYER_H
#define AI2022_FANORONA_AI_PLAYER_H

#include <vector>
#include "GamePlayer.h"
#include "../FanoronaGame.h"
#include "../util/Structs.h"

using json = nlohmann::json;

class AiPlayer : public GamePlayer {
    private:
    public:
        AiPlayer(int p_id, FanoronaGame& p_game);
        json status();
};

#endif //AI2022_FANORONA_AI_PLAYER_H
