#ifndef DA_GAME_GAME_H
#define  DA_GAME_GAME_H

#include <vector>

#include "actor.h"
#include "terminal.h"
#include "game_commands.h"
#include "environment.h"

namespace da_game {
    class Game {
        public:
            Game();        
            ~Game();        
            void initialize();

        private:
            std::vector<Actor *> actors;
            std::vector<Environment *> envs;
            void run();
            Terminal terminal;
            GameCommands * commands;
            Player * player;
    };
}

#endif // DA_GAME_GAME_H
