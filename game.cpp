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
#include "light_saber.h"

namespace da_game {
    std::vector<Actor *> * Game::actors;
    std::vector<Environment *> * Game::envs;
    Player * Game::player;

    Game::Game() {
        actors = new std::vector<Actor *>;
        envs = new std::vector<Environment *>;
        bool running = true;
        initialize();
        while (running && playerIsAlive()) {
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
        if (!playerIsAlive()) {
            std::cout << "Sry, you died! :(" << std::endl;
        }
    }

    Game::~Game() {
        actors->clear();
    }

    bool Game::playerIsAlive() {
        return player != NULL;
        // std::cout << "Game::playerIsAlive()";
        // Player * pl = dynamic_cast<Player *>(player);
        // std::cout << (pl != NULL) << std::endl;
        // return (pl != NULL);
        // std::vector<Actor *>::iterator it = actors->begin();
        // 
        // for (; it != actors->end(); ++it) {
        // Player * pl = dynamic_cast<Player *>(*it);
        // if (pl != NULL) {
        // return true;
        // }
        // }
        // return false;
    }

    /*
     * Create the map and all objects
     */
    void Game::initialize() {

        // initialize environment
        //
        Environment * r1 = new Room(0, 0, 0, 0);
        Environment * r2 = new Room(r1, 0, 0, 0);
        r1->add_neighbor("west", r2);

        Environment * evil = new EvilLair(r2, r1, 0, 0);
        VampireFactory * vamp_fac = new VampireFactory(evil, 2);
        evil->enter(*vamp_fac);
        actors->push_back(vamp_fac);

        r2->add_neighbor("west", evil);
        r1->add_neighbor("east", evil);

        envs->push_back(r1);
        envs->push_back(r2);

        // Create objects

        Object * b1 = new Bag();
        Object * b2 = new Bag();
        Object * b3 = new Bag();
        Object * b4 = new Food(47);
        r1->drop(b1);
        r1->drop(b2);
        r1->drop(b3);

        r2->drop(b4);


        Object * light_saber = new LightSaber(1000,0.95);
        evil->drop(light_saber);



        // Create the player

        player = new Player(r1);
        r1->enter(*player);
        commands = new GameCommands(player);

        actors->push_back(player);

        // Initialize actors

        Troll * t = new Troll(r2, 1000, 88);
        r2->enter(*t);
        actors->push_back(t);

        Wizard * w = new Wizard(evil, true, 100, 100);
        evil->enter(*w);
        actors->push_back(w);

        Bag bag;
    }

    void Game::run() {
        std::vector<Actor *>::iterator it;

        for (it = actors->begin(); it != actors->end(); ++it) {
                (*it)->run();
        }
    }

    void Game::removeActor(Actor & actor) {
        if (&actor == player) {
            player = 0;
        }
        std::vector<Actor *>::iterator it = actors->begin();
        for (; it != actors->end(); ++it) {
            if (&(**it) == &actor) {
                actors->erase(it);
                return;
            }
        }
    }
}

int main() {
    std::srand(std::time(0));
    da_game::Game game;

}

