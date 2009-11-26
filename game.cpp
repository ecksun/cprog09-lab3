#include "game.h"
int main() {
    da_game::Game game;
}

namespace da_game {
    Game::Game() {
        run();
    }

    void Game::run() {
        std::vector<Actor *>::iterator it;
        it = actors.begin();

        for (; it != actors.end(); ++it) {
            (*it)->run();
        }
    }
}
