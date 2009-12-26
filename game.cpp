#include <cstdlib>
#include <ctime>
#include "bag.h"
#include "game.h"
#include "troll.h"
#include "wizard.h"
#include "terminal.h"
#include "bag.h"
#include "room.h"

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

    Game::~Game() {
        actors.clear();
    }

    /*
     * Create the map and all objects
     */
    void Game::initialize() {
        Environment * r1 = new Room(0, 0, 0, 0);
        Environment * r2 = new Room(r1, 0, 0, 0);
        r1->add_neighbor("west", r2);

        Object * b1 = new Bag();
        Object * b2 = new Bag();
        Object * b3 = new Bag();
        Object * b4 = new Food(47);
        r1->drop(b1);
        r1->drop(b2);
        r1->drop(b3);

        r2->drop(b4);

        envs.push_back(r1);
        envs.push_back(r2);

        player = new Player(r1);
        commands = new GameCommands(player);

        // Initialize actors

        Troll * t = new Troll(r2, 1000, 88);
        r2->enter(*t);
        actors.push_back(t);
        
//        Wizard * w = new Wizard(true, 100, 10);
//        actors.push_back(w);

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
    std::srand(std::time(0));
    da_game::Game game;

}

