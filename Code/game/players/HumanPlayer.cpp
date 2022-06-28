#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int p_id, FanoronaGame& p_game) : GamePlayer(p_id, p_game) {

}
void HumanPlayer::stoneSelected(Position const& p) {
    if(!isStoneSelected) {
        // If a stone hasn't been selected yet, first check if it's a stone of us
        std::cout << "(" << p.row << ", " << p.col << ") => " << game->at(p) << std::endl;
        if(game->at(p) != id) throw std::runtime_error("Select one of your stones");
        // Generate the possible movements of that stone. If there are none, error out
        possibleMovements = game->generateMovements(p.row, p.col, id);
        if(possibleMovements.size() == 0) throw std::runtime_error("Select a stone that can move");
        // If everything checks out, set stone as selected and save its position
        isStoneSelected = true;
        selectedStone = p;
    } else {
        // If a stone has already been selected, we should bust a move(ment)
        // Get the movement from the list of possible movements
        Movement m;
        bool movementFound = false;
        for(auto const& pm : possibleMovements) {
            if(pm.to.row == p.row && pm.to.col == p.col) {
                movementFound = true;
                m = pm;
                break;
            }
        }
        // If no movement was found, it's not a valid move, complain
        if(!movementFound) throw std::runtime_error("Not a valid movement");
        // Execute the movement
        game->executeMovement(m);
        // Advance the selected stone and generate new possible movements
        selectedStone = { m.to.row, m.to.col };
        possibleMovements = game->generateMovements(m.to.row, m.to.col, id);
        // If there are none, end the turn automatically
        if(possibleMovements.size() == 0){
            isStoneSelected = false;
            game->endMove();
        }
    }
}
json HumanPlayer::status() {
    // Get the base status message
    json s = GamePlayer::status();
    // Add a stone position and possible movements depending on whether we have it
    if(isStoneSelected) {
        // Convert the movements to JSON first
        std::vector<json> movementsJson;
        for(auto const& m : possibleMovements) {
            movementsJson.push_back({ 
                {"to", { {"row", m.to.row}, {"col", m.to.col} }}
            });
        }
        s["stone"] = {{"row", selectedStone.row},{"col", selectedStone.col}};
        s["movements"] = movementsJson;
    }else{
        s["stone"] = nullptr;
        s["movements"] = nullptr;
    }
    return s;
}