#ifndef AI2022_FANORONA_HUMAN_PLAYER_H
#define AI2022_FANORONA_HUMAN_PLAYER_H

#include <vector>
#include <iostream>
#include "json.hpp"
#include "GamePlayer.h"
#include "../FanoronaGame.h"
#include "../util/Structs.h"

using json = nlohmann::json;

class HumanPlayer : public GamePlayer {
    private:
        bool isStoneSelected = false;
        Position selectedStone;
        std::vector<Movement> possibleMovements;
    public:
        HumanPlayer(int p_id, FanoronaGame& p_game);
        void stoneSelected(Position const& p);
        json status();
};

#endif //AI2022_FANORONA_HUMAN_PLAYER_H
