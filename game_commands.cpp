#include "game_commands.h"

namespace da_game {
    Player GameCommands::player;
    GameCommands::GameCommands() {
        Terminal::add_function(std::string("exit"), &GameCommands::exit);
        Terminal::add_function(std::string("go"), &GameCommands::go);
    }
    int GameCommands::exit(std::string) {
        return 1;
    }

    int GameCommands::go(std::string direction) {
        player.go(direction);
        return 0;
    }
}
