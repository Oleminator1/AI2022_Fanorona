#include "AiPlayer.h"

AiPlayer::AiPlayer(int p_id, FanoronaGame& p_game) : GamePlayer(p_id, p_game) {

}

void AiPlayer::turnStarted() {
    std::cout << "It's the AI's turn!" << std::endl;
}

json AiPlayer::status() {
    return {
        {"id", id},
        {"type", "ai"}
    };
}