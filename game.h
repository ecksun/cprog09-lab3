#ifndef DA_GAME_GAME_H
#define  DA_GAME_GAME_H

#include <vector>

#include "actor.h"
#include "terminal.h"
#include "game_commands.h"

namespace da_game {
    class Game {
        public:
            Game();        
            void initialize();

        private:
            std::vector<Actor *> actors;
            void run();
            Terminal terminal;
            GameCommands commands;
    };
}

#endif // DA_GAME_GAME_H
