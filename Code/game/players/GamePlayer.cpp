#include "GamePlayer.h"

GamePlayer::GamePlayer(int p_id, FanoronaGame& p_game) {
    id = p_id;
    game = &p_game;
}
void GamePlayer::stoneSelected(Position const& p) { }
void GamePlayer::turnStarted() { }
json GamePlayer::status() {
    return {
        {"id", id}
    };
}