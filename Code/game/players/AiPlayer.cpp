#include "AiPlayer.h"

AiPlayer::AiPlayer(int p_id, FanoronaGame& p_game) : GamePlayer(p_id, p_game) {

}

/*
Maximizing Player: AiPlayer.id
Minimizing Player: other

Score für non-strong: +/-10
Score für strong: 15
*/

int AiPlayer::evaluate() {
    int score = 0;
    for(int row = 0; row < 5; row++) {
        for(int col = 0; col < 9; col++) {
            // Get the grid value of the current position
            int at = game->grid[row][col];
            // Skip if it's empty
            if(at == 0) continue;
            // Score is 10 for non-strong and 15 for strong position
            int s = game->isStrongPosition(row, col) ? 15 : 10;
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

void AiPlayer::minimax() {
    FanoronaGame copiedGame = FanoronaGame(*game);
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
    std::cout << "Evaluation: " << evaluate() << std::endl;
    game->endMove();
}

bool AiPlayer::isAi() { return true; }
json AiPlayer::status() {
    return {
        {"id", id},
        {"type", "ai"}
    };
}