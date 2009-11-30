#ifndef DA_GAME_GAME_COMMANDS_H
#define DA_GAME_GAME_COMMANDS_H
#include "terminal.h"
#include "player.h"
#include <string>
namespace da_game {
    class GameCommands {
        public:
            GameCommands(Player *);
            static int exit(std::string);
            static int go(std::string);
            static int fight(std::string);
            static int pick_up(std::string);
            static int drop(std::string);
            static int talk_to(std::string);
            static int help(std::string);
        private:
            static Player * player;
            static int stringToInt(std::string);
    };
}
#endif
