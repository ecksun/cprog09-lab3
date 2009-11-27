#ifndef DA_GAME_GAME_H
#define  DA_GAME_GAME_H

#include <vector>

#include "actor.h"
#include "terminal.h"

namespace da_game {
    class Game {
        public:
            Game();        
            ~Game();        
            void initialize();

        private:
            std::vector<Actor *> actors;
            void run();
            Terminal terminal;
    };
}

#endif // DA_GAME_GAME_H
