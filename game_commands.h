#ifndef DA_GAME_GAME_COMMANDS_H
#define DA_GAME_GAME_COMMANDS_H
#include "terminal.h"
#include "player.h"
#include <string>
namespace da_game {
    class GameCommands {
        public:
            GameCommands();
            static int exit(std::string);
            static int go(std::string);
        private:
            static Player player;
    };
}
#endif
