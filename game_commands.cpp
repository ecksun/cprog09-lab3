#include "game_commands.h"

namespace da_game {
    GameCommands::GameCommands() {
        Terminal::add_function(std::string("exit"), &GameCommands::exit);
    }
    int GameCommands::exit(std::string) {
        return 1;
    }
}
