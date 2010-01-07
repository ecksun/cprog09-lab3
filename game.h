#ifndef DA_GAME_GAME_H
#define DA_GAME_GAME_H

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
            static void removeActor(Actor &);

        private:
            static std::vector<Actor *> * actors;
            static std::vector<Environment *> * envs;
            void run();
            bool playerIsAlive();
            Terminal terminal;
            GameCommands * commands;
            static Player * player;
    };

}

#endif // DA_GAME_GAME_H
