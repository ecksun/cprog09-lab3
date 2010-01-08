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
        printStory();
        while (running && playerIsAlive() && !playerIsAlone()) {
            Terminal::print(player->getRoom()->description());
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
        if (playerIsAlone()) {
            std::cout << "Congratz! you won!" << std::endl;
        }
    }

    Game::~Game() {
        actors->clear();
        delete commands;
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

        // Environments
        Environment * r1 = new Room();
        Environment * r2 = new Room();

        Environment * evil = new EvilLair();
        VampireFactory * vamp_fac = new VampireFactory(evil, 2);
        evil->enter(*vamp_fac);
        actors->push_back(vamp_fac);
        
        // exits
        Exit * e1 = new Exit(r1, true, "e1", true);
        Exit * e2 = new Exit(r2);
        Exit * eevil = new Exit(evil);

        r1->add_exit("recurse", e1);
        r1->add_exit("west", e2);
        r1->add_exit("east", eevil);
        r2->add_exit("west", eevil);
        evil->add_exit("east", e2);
        evil->add_exit("west", e1);

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

    bool Game::playerIsAlone() {
        return (playerIsAlive() && (actors->size() == 1));
    }


    void Game::printStory() {
        Terminal::print("When Anakin entered the Jedi-Tempel after beeing order to destroy the Jedi-order by Darth Sidious he suddenly saw a bright light surround him. When it dissapeared he had been transported to the most peculiar place, he heard sounds of vampires and smellt the smell of trolls, he must have been transported to dev random. As Anakin recently had been turned to the dark side he pushed his confusion from his mind and as the anger overtook him he realised he would not be satisfied until EVERYTHING was DEAD.");
    }
}

int main() {
    std::srand(std::time(0));
    da_game::Game game;

}

