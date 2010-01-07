#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bag.h"
#include "game.h"
#include "troll.h"
#include "wizard.h"
#include "terminal.h"
#include "bag.h"
#include "room.h"
#include "evil_lair.h"
#include "vampire_factory.h"

namespace da_game {

    Game::Game() {
        bool running = true;
        initialize();
        while (running) {
            std::cout << player->getRoom()->description() << std::endl;
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

        // Environments
        Environment * r1 = new Room();
        Environment * r2 = new Room();

        Environment * evil = new EvilLair();
        VampireFactory * vamp_fac = new VampireFactory(evil, 2);
        evil->enter(*vamp_fac);
        actors.push_back(vamp_fac);
        
        // exits
        Exit * e1 = new Exit(r1);
        Exit * e2 = new Exit(r2);
        Exit * eevil = new Exit(evil);

        r1->add_exit("recurse", e1);
        r1->add_exit("west", e2);
        r1->add_exit("east", eevil);
        r2->add_exit("west", eevil);
        evil->add_exit("east", e2);
        evil->add_exit("west", e1);


        // Create objects
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



        // Create the player

        player = new Player(r1);
        r1->enter(*player);
        commands = new GameCommands(player);

        actors.push_back(player);

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

