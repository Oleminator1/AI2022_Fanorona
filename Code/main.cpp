#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_INTERNAL_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include <set>
#include "game/FanoronaGame.h"
#include "game/players/HumanPlayer.h"
#include "game/players/AiPlayer.h"
#include "game/util/Structs.h"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

#define KEY_COMMAND "command"
#define CMD_ERROR "error"
#define CMD_SELECT "select"
#define CMD_MOVE "move"
#define CMD_STATUS "status"
#define CMD_START "start"
#define CMD_MOVEMENTS "movements"

#define SERVER_PORT 9002

#define AI_DEPTH 2

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

// Create a server endpoint
server echo_server;
std::set<websocketpp::connection_hdl,std::owner_less<websocketpp::connection_hdl>> connections;

FanoronaGame game;
std::map<int, std::shared_ptr<GamePlayer>> players;

json jsonError(std::string error) {
    return {
        {KEY_COMMAND, CMD_ERROR},
        {"message", error}
    };
}
json jsonStatus() {
    return {
        {KEY_COMMAND, CMD_STATUS},
        {"board", game.grid},
        {"player", players[game.currentPlayer()]->status()}
    };
}
/*json jsonMovements(std::vector<Movement> const& movements) {
    std::vector<json> movementsJson;
    for(auto const& movement : movements) {
        movementsJson.push_back({ 
            {"to", { {"row", movement.to.row}, {"col", movement.to.col} }}
        });
    }
    return {
        {KEY_COMMAND, CMD_MOVEMENTS},
        {"movements", movementsJson}
    };
}*/

json processCommand(json& message) {
    if(!message.contains(KEY_COMMAND)){
        // no command, no bueno
        return jsonError("Missing command in message");
    }
    std::string cmd = message[KEY_COMMAND].get<std::string>();
    if(cmd == CMD_START) {
        // Clear existing players
        players.clear();
        // Get player types from start command
        int playerId = 1;
        for(auto playerType : message["players"]) {
            // Ignore by the third player (only two allowed)
            if(playerId == 3) break;
            // Get the player type string from JSON (human or ai)
            std::string type = playerType.get<std::string>();
            // Add player by type
            std::shared_ptr<GamePlayer> player;
            if(type == "human") {
                player = std::make_shared<HumanPlayer>(playerId, game);
            } else if(type == "ai") {
                player = std::make_shared<AiPlayer>(playerId, game, AI_DEPTH);
            } else {
                throw std::runtime_error("Invalid player type");
            }
            players[playerId] = player;
            playerId++;
        }
        // Start the game
        game.startGame();
        // Trigger turnStarted of first player
        players[game.currentPlayer()]->turnStarted();
        // Return a status message
        return jsonStatus();
    } else if (cmd == CMD_SELECT) {
        // Convert the JSON values into more practical structs
        Position p = { message["position"]["row"].get<int>(), message["position"]["col"].get<int>() };
        // Save the currently active player
        int previousPlayer = game.currentPlayer();
        // Pass the selection to the player
        try{
            players[game.currentPlayer()]->stoneSelected(p);
        }catch(const std::runtime_error& e) {
            return jsonError(e.what());
        }
        // If the player changed, trigger the turnStarted of the new player
        if(game.currentPlayer() != previousPlayer) {
            players[game.currentPlayer()]->turnStarted();
        }
        // Winner functionality
        int winner = game.winner();
        if(winner == IN_PROGRESS) {
            std::cout << "GAME IN PROGRESS" << std::endl;
        } else {
            std::cout << "WINNER: " << (winner == PLAYER_WHITE ? "White" : "Black/Draw") << std::endl;
            throw std::runtime_error("Winner");
        }
        // Return a status message
        return jsonStatus();
    }
    return jsonError("Not a recognized command");
}

void onTimer(websocketpp::lib::error_code const & ec) {
    players[game.currentPlayer()]->turnStarted();
    for(auto const& hdl : connections) {
        echo_server.send(hdl, jsonStatus().dump(), websocketpp::frame::opcode::text);
    }
    if(game.winner() == IN_PROGRESS) {
        echo_server.set_timer(1000, bind(&onTimer, ::_1));
    }
}

void onOpen(websocketpp::connection_hdl hdl) {
    connections.insert(hdl);
}

void onClose(websocketpp::connection_hdl hdl) {
    connections.erase(hdl);
}
// Define a callback to handle incoming messages
void onMessage(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;
    
    // Parse command as JSON and process
    auto message = json::parse(msg->get_payload());
    std::string resp = processCommand(message).dump();

    // Special Case: AI vs AI, skip all the callback stuff in that case
    if(players.size() > 0 && players[PLAYER_WHITE]->isAi() && players[PLAYER_BLACK]->isAi()) {
        std::cout << "Both players are AI, starting timer" << std::endl;
        echo_server.set_timer(1000, bind(&onTimer, ::_1));
    }

    try {
        s->send(hdl, resp, msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << "Response failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }
}

int main() {
    try {
        // Set logging settings
        //echo_server.set_access_channels(websocketpp::log::alevel::all);
        //echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);
        echo_server.clear_access_channels(websocketpp::log::alevel::all);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&onMessage,&echo_server,::_1,::_2));
        echo_server.set_open_handler(bind(&onOpen,_1));
        echo_server.set_close_handler(bind(&onClose,_1));

        // Listen on port 9002
        echo_server.listen(SERVER_PORT);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        std::cout << "Server is ready at ws://127.0.0.1:" << std::to_string(SERVER_PORT) << std::endl;
        echo_server.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
    
}