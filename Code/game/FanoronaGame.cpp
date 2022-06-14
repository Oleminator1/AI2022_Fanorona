#include "FanoronaGame.h"

json FanoronaGame::as_json() {
    json j;
    j["board"] = board;
    return j;
}