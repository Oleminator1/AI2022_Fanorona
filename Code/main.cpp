#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_INTERNAL_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>
#include "game/fanorona-game.h"

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

#define KEY_COMMAND "command"
#define CMD_ERROR "error"
#define CMD_MOVE "move"
#define CMD_BOARD "board"
#define CMD_START "start"

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

struct position { int x; int y; };

int board_start[9][5] = {{2,2,2,1,1},{2,2,1,1,1},{2,2,2,1,1},{2,2,1,1,1},{2,2,0,1,1}, {2,2,2,1,1},{2,2,1,1,1},{2,2,2,1,1},{2,2,1,1,1}};;
int test_board[9][5];

FanoronaGame game;
json json_error(std::string error) {
    return {
        {KEY_COMMAND, CMD_ERROR},
        {"message", error}
    };
}
json json_board() {
    return {
        {KEY_COMMAND, CMD_BOARD},
        {"board", test_board}
    };
}

json process_command(json& message) {
    if(!message.contains(KEY_COMMAND)){
        // no command, no bueno
        return json_error("Missing command in message");
    }
    std::string cmd = message[KEY_COMMAND].get<std::string>();
    if(cmd == CMD_START) {
        std::copy(&board_start[0][0], &board_start[0][0]+9*5,&test_board[0][0]);
        return json_board();
    } else if (cmd == CMD_MOVE) {
        position from = { message["from"]["x"].get<int>(), message["from"]["y"].get<int>() };
        position to = { message["to"]["x"].get<int>(), message["to"]["y"].get<int>() };
        test_board[to.x][to.y] = test_board[from.x][from.y];
        test_board[from.x][from.y] = 0;
        return json_board();
    }
    return json_error("Not a recognized command");
}
// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;
    
    // Parse command as JSON and process
    auto message = json::parse(msg->get_payload());
    std::string resp = process_command(message).dump();

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
        echo_server.set_message_handler(bind(&on_message,&echo_server,::_1,::_2));

        // Listen on port 9002
        echo_server.listen(9002);

        // Start the server accept loop
        echo_server.start_accept();

        // Start the ASIO io_service run loop
        echo_server.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
    
}