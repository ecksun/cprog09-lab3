#include "bag.h"
#include "game.h"
#include "troll.h"
#include "wizard.h"
#include "terminal.h"
#include "bag.h"

namespace da_game {

    Game::Game() {
        initialize();
        while (true) {
            terminal.run();
            run();
            sleep(1);
        }
    }

    Game::~Game() {
        actors.clear();
    }

    /*
     * Create the map and all objects
     */
    void Game::initialize() {
        Troll * t = new Troll(1000, 88);
        actors.push_back(t);

        Wizard * w = new Wizard(true, 100, 10);
        actors.push_back(w);

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

