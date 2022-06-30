#include "AiPlayer.h"

AiPlayer::AiPlayer(int p_id, FanoronaGame& p_game, int p_height = 4) : GamePlayer(p_id, p_game) {
    height = p_height;
}

/*
Maximizing Player: AiPlayer.id
Minimizing Player: other

Score für non-strong: +/-10
Score für strong: 15
*/

int AiPlayer::evaluate(FanoronaGame& state) {
    int score = 0;
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 9; col++) {
            // Get the grid value of the current position
            int at = state.grid[row][col];
            // Skip if it's empty
            if(at == 0) continue;
            // Score is 10 for non-strong and 15 for strong position
            int s = state.isStrongPosition(row, col) ? 15 : 10;
            // Negate the score if it's the opponents piece (minimizing player)
            if(at != id) {
                s *= -1;
            }
            // Add to the total score
            score += s;
        }
    }
    return score;
}

int AiPlayer::minimax(FanoronaGame state, int player, int depth = 0, int alpha = INT_MIN, int beta = INT_MAX) {
    //FanoronaGame copiedGame = FanoronaGame(*game);
    // If we're at maximum depth, return from values
    if(depth == height) {
        return evaluate(state);
    }

    int opponentId = player == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE;

    if(player == id){
        // Player playing for maximum (this player)
        int max = INT_MIN;
        // Iterate through all the children
        for(int i = 0; i < height - 1; i++){
            //if(node_index*K+i > 30-1) continue;
            //std::cout << "max" << " ";
            int result = minimax(state, opponentId, depth + 1, alpha, beta/*height, depth + 1, !max_player, alpha, beta*/);
            max = std::max(max, result);
            alpha = std::max(alpha, result);
            if(beta <= alpha) break;
        }
        return max;
    }else{
        // Player playing for minimum
        int min = INT_MAX;
        // Iterate through all the children
        for(int i = 0; i < height - 1; i++){
            //if(node_index*K+i > 30-1) continue;
            //std::cout << "min" << " ";
            int result = minimax(state, opponentId, depth + 1, alpha, beta/*height, depth + 1, node_index * K + i, !max_player, alpha, beta*/);
            min = std::min(min, result);
            beta = std::min(beta, result);
            if(beta <= alpha) break;
        }
        return min;
    }
}

void AiPlayer::turnStarted() {
    std::vector<Move> moves;
    game->generateMoves(id, moves);
    std::cout << "===== NEW AI MOVE (" << (id == PLAYER_WHITE ? "White" : "Black") << ") (" << moves[0].movements.size() <<" movements) =====" << std::endl;
    for(auto const& movement : moves[0].movements){
        game->executeMovement(movement);
    }
    game->endMove();
}

bool AiPlayer::isAi() { return true; }
json AiPlayer::status() {
    return {
        {"id", id},
        {"type", "ai"}
    };
}