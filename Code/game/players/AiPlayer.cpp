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
    // Get possible movements for all movable stones
    std::vector<std::vector<Movement>> initialMovements;
    bool haveCapturing = false;
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 9; col++) {
            // If it's not our stone, we can skip it
            if(game->at({ row, col }) != id) continue;
            // Generate possible movements
            auto movements = game->generateMovements(row, col, id);
            // If there's 0 movements available for this stone, skip it
            if(movements.size() == 0) continue;
            // If we aren't already in "capturing moves only" mode, check for any
            if(!haveCapturing){
                for(auto const& m : movements) {
                    if(m.isCapturing){ haveCapturing = true; break; }
                }
            }
            // Add to initialMovements
            initialMovements.push_back(movements);
        }
    }
    // If we're in "capturing moves only" mode, remove anything that has non-capturing movements
    if(haveCapturing){
        std::vector<std::vector<Movement>>::iterator it = initialMovements.begin();
        while(it != initialMovements.end()) {
            if(!it->at(0).isCapturing) {
                std::cout << "is capturing " << std::endl;
                it = initialMovements.erase(it);
            }else{
                std::cout << it->at(0).from.row << ", " << it->at(0).from.col << " -> " << it->at(0).to.row << ", " << it->at(0).to.col << " " << (it->at(0).attackType ? "Withdraw" : "Approach") << std::endl;
                ++it;
            }
        }
    }
    // We now have all the stones we can initially move and the possible movements for them, the basis for the minmax tree
    std::cout << initialMovements.size() << " initial movable stones" << std::endl;
    
    game->executeMovement(initialMovements[0][0]);
    std::cout << "Evaluation: " << evaluate(*game) << std::endl;
    game->endMove();
}

bool AiPlayer::isAi() { return true; }
json AiPlayer::status() {
    return {
        {"id", id},
        {"type", "ai"}
    };
}