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
            static void remove_actor(Actor &);
            static void add_actor(Actor &);

        private:
            static std::vector<Actor *> * actors;
            static std::vector<Environment *> * envs;
            void run();
            void printStory();
            bool playerIsAlive();
            bool playerIsAlone();
            Terminal terminal;
            GameCommands * commands;
            static Player * player;
    };

}

#endif // DA_GAME_GAME_H
