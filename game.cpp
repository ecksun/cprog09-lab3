#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
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
            Terminal::print(player->get_room()->description());
            switch (terminal.run()) {
                case 1:
                    running = false;
                    break;
                case 2:
                    save();
                    running = false;
                    break;
                case 3:
                    clear_game();
                    std::cout << actors->size() << std::endl;
                    std::cout << envs->size() << std::endl;

                    load();
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

        // Create objects
        Object * b1 = new Bag();
        Object * b2 = new Bag();
        Object * b3 = new Bag();
        Object * b4 = new Food(47);
        Object * k1 = new Key("e1");
        Object * k2 = new Key("e2");

        r1->drop(b1);
        r1->drop(b2);
        r1->drop(b3);

        r2->drop(b4);

        Object * light_saber = new LightSaber(1000,0.95);
        evil->drop(light_saber);
        evil->drop(k1);
        evil->drop(k2);


        // Create the player

        player = new Player(r1);
        r1->enter(*player);
        commands = new GameCommands(player);


        // Initialize actors

        Troll * t = new Troll(r2, 1000, 88);
        r2->enter(*t);

        Wizard * w = new Wizard(evil, true, 100, 100);
        evil->enter(*w);

        Bag bag;
    }

    void Game::run() {
        for (unsigned int i = 0; i < actors->size(); ++i) {
            actors->at(i)->run();
        }
    }

    void Game::add_actor(Actor & actor) {
        actors->push_back(&actor);
    }

    void Game::add_environment(Environment & env) {
        envs->push_back(&env);
    }

    void Game::remove_actor(Actor & actor) {
        if (&actor == player) {
            player = 0;
        }
        std::cout << "Removing actor from game" << std::endl;
        std::vector<Actor *>::iterator it = actors->begin();
        for (; it != actors->end(); ++it) {
            if (&(**it) == &actor) {
                actors->erase(it);
                std::cout << "gone" << std::endl;
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

    void Game::save() {
        std::ofstream file;
        file.open ("saveFile");
        for (std::vector<Actor *>::iterator it = actors->begin(); it != actors->end(); ++it) {
            (*it)->save(file);
        }
        for (std::vector<Environment *>::iterator it = envs->begin(); it != envs->end(); ++it) {
            (*it)->save(file);
        }
        file.close();
    }
    void Game::load() {
        std::ifstream file;
        file.open("saveFile");

        file.close();
    }
    void Game::clear_game() {
        std::cout << "Removing environments" << std::endl;
        for (std::vector<Environment *>::iterator it = envs->begin(); it != envs->end(); ++it) {
            delete *it;
        }
        std::cout << "Killing players" << std::endl;
        for (std::vector<Actor *>::iterator it = actors->begin(); it != actors->end(); ++it) {
            delete *it;
        }
    }
}

int main() {
    std::srand(std::time(0));
    da_game::Game game;

}

