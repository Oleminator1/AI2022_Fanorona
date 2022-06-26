#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_INTERNAL_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include "game/FanoronaGame.h"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

#define KEY_COMMAND "command"
#define CMD_ERROR "error"
#define CMD_SELECT "select"
#define CMD_MOVE "move"
#define CMD_BOARD "board"
#define CMD_START "start"

#define SERVER_PORT 9002

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

FanoronaGame game;

json jsonError(std::string error) {
    return {
        {KEY_COMMAND, CMD_ERROR},
        {"message", error}
    };
}
json jsonBoard() {
    return {
        {KEY_COMMAND, CMD_BOARD},
        {"board", game.grid}
    };
}

json processCommand(json& message) {
    if(!message.contains(KEY_COMMAND)){
        // no command, no bueno
        return jsonError("Missing command in message");
    }
    std::string cmd = message[KEY_COMMAND].get<std::string>();
    if(cmd == CMD_START) {
        game.startGame();
        return jsonBoard();
    } else if (cmd == CMD_SELECT) {
        // Convert the JSON values into more practical structs
        Position p = { message["position"]["row"].get<int>(), message["position"]["col"].get<int>() };
        // Try to select the stone
        try{ game.selectStone(p); } catch(const std::runtime_error& e) { return jsonError(e.what()); }
    } else if (cmd == CMD_MOVE) {
        // Convert the JSON values into more practical structs
        Position from = { message["from"]["row"].get<int>(), message["from"]["col"].get<int>() };
        Position to = { message["to"]["row"].get<int>(), message["to"]["col"].get<int>() };
        // Try to apply the move and return the board
        try{
            //game.moveStone(from.row, from.col, to.row, to.col);
        } catch(const std::exception& e) {
            return jsonError(e.what());
        }
        
        return jsonBoard();
    }
    return jsonError("Not a recognized command");
}
// Define a callback to handle incoming messages
void onMessage(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;
    
    // Parse command as JSON and process
    auto message = json::parse(msg->get_payload());
    std::string resp = processCommand(message).dump();

    try {
        s->send(hdl, resp, msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << "Response failed because: "
                  << "(" << e.what() << ")" << std::endl;
    }
}

int main() {
    // Create a server endpoint
    server echo_server;

    try {
        // Set logging settings
        echo_server.set_access_channels(websocketpp::log::alevel::all);
        echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        echo_server.init_asio();

        // Register our message handler
        echo_server.set_message_handler(bind(&onMessage,&echo_server,::_1,::_2));

        // Listen on port 9002
        echo_server.listen(SERVER_PORT);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        std::cout << "Server is ready at ws://127.0.0.1:" << std::to_string(SERVER_PORT) << std::endl;
        echo_server.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
    
}