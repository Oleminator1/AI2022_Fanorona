#include "AiPlayer.h"

AiPlayer::AiPlayer(int p_id, FanoronaGame& p_game) : GamePlayer(p_id, p_game) {

}
json AiPlayer::status() {
    return {
        {"id", id}
    };
}