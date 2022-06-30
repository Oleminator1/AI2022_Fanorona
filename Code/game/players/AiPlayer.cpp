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

int AiPlayer::minimax(FanoronaGame state, int player, Move executedMove, int depth = 0, int alpha = INT_MIN, int beta = INT_MAX) {
    //FanoronaGame copiedGame = FanoronaGame(*game);
    // If we're at maximum depth, return from values
    if(depth == height) {
        return evaluate(state);
    }

    // ID of the opponent player (minimizing player)
    int opponentId = player == PLAYER_WHITE ? PLAYER_BLACK : PLAYER_WHITE;

    // Generate all possible moves from this state
    std::vector<Move> moves = game->generateMoves(id, moves);
    //std::cout << "Moves: " << moves.size() << std::endl;

    if(player == id){
        // Player playing for maximum (this player)
        int max = INT_MIN;
        // Iterate through all the possible moves (children)
        for(Move m : moves){
            // Execute the move in a copy of the game state
            FanoronaGame moveState(state);
            for(Movement m : m.movements){ moveState.executeMovement(m); }
            // Are you, are you, coming to the tree?
            int result = minimax(moveState, opponentId, m, depth + 1, alpha, beta/*height, depth + 1, !max_player, alpha, beta*/);
            max = std::max(max, result);
            if(result > max) {
                max = result;
                bestMove = m;
            }
            alpha = std::max(alpha, result);
            if(beta <= alpha) break;
        }
        return max;
    }else{
        // Player playing for minimum
        int min = INT_MAX;
        // Iterate through all the possible moves (children)
        for(Move m : moves){
            // Execute the move in a copy of the game state
            FanoronaGame moveState(state);
            for(Movement m : m.movements){ moveState.executeMovement(m); }
            // They strung up a man, they said he murdered three
            int result = minimax(moveState, opponentId, m, depth + 1, alpha, beta/*height, depth + 1, node_index * K + i, !max_player, alpha, beta*/);
            if(result < min) {
                min = result;
                bestMove = m;
            }
            beta = std::min(beta, result);
            if(beta <= alpha) break;
        }
        return min;
    }
}

void AiPlayer::turnStarted() {
    std::cout << "===== NEW AI MOVE (" << (id == PLAYER_WHITE ? "White" : "Black") << ") =====" << std::endl;
    int result = minimax(*game, id, {});
    std::cout << "Score: " << result << std::endl;
    std::cout << bestMove.movements.size() << " movements" << std::endl;
    for(auto const& m : bestMove.movements){
        std::cout << "Movement: (" << m.from.row << "," << m.from.col << ") => (" << m.to.row << "," << m.to.col << ") | Capturing: " << (m.isCapturing ? "Yes" : "No") << " | AttackType: " << (m.attackType ? "Withdraw" : "Attack") << std::endl;
        game->executeMovement(m);
    }
    game->endMove();

    /*std::cout << "AI MOVE, calculating..." << std::endl;
    MoveScore we = minimax(*game, id);
    std::cout << "Winning Move: "<
    std::vector<Move> moves = game->generateMoves(id, moves);
    std::cout << "===== NEW AI MOVE (" << (id == PLAYER_WHITE ? "White" : "Black") << ") (" << moves[0].movements.size() <<" movements) =====" << std::endl;
    std::cout << moves.size() << " moves available" << std::endl;
    for(auto const& m : moves[0].movements){
        std::cout << "Movement: (" << m.from.row << "," << m.from.col << ") => (" << m.to.row << "," << m.to.col << ") | Capturing: " << (m.isCapturing ? "Yes" : "No") << " | AttackType: " << (m.attackType ? "Withdraw" : "Attack") << std::endl;
        game->executeMovement(m);
    }
    game->endMove();*/
}

bool AiPlayer::isAi() { return true; }
json AiPlayer::status() {
    return {
        {"id", id},
        {"type", "ai"}
    };
}