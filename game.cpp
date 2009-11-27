#include "game.h"
#include "troll.h"
#include "terminal.h"
#include "bag.h"

namespace da_game {

    Game::Game() {
        bool running = true;
        initialize();
        while (running) {
            switch (terminal.run()) {
                case 1:
                    running = false;
                    break;
                default:
                    run();
                    break;
            }
        }
    }

    /*
     * Create the map and all objects
     */
    void Game::initialize() {
        Actor * t = new Troll(1000, 88);
        actors.push_back(t);

        Bag bag;
    }

    void Game::run() {
        std::vector<Actor *>::iterator it;

        for (it = actors.begin(); it != actors.end(); ++it) {
            (*it)->run();
        }
    }

}

int main() {
    da_game::Game game;

}

