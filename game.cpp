#include "game.h"
#include "troll.h"
#include "terminal.h"

namespace da_game {
    Game::Game() {
        initialize();
        while (true) {
            terminal.run();
            run();
            sleep(1);
        }
    }

    /*
     * Create the map and all objects
     */
    void Game::initialize() {
        Actor * t = new Troll(1000, 88);
        actors.push_back(t);
    }

    void Game::run() {
        std::vector<Actor *>::iterator it;
        it = actors.begin();

        for (; it != actors.end(); ++it) {
            (*it)->run();
        }
    }
}

int main() {
    da_game::Game game;
}

