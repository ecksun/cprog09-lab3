#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>
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
#include "bad_format.h"

namespace da_game {
    std::vector<Actor *> * Game::actors;
    std::vector<Environment *> * Game::envs;
    Player * Game::player;

    Game::Game() {
        actors = new std::vector<Actor *>;
        envs = new std::vector<Environment *>;
        bool running = true;
        load();
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
//                    clear_game();
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
        new VampireFactory(evil, 2);
        // evil->enter(*vamp_fac);
        
        // exits
        Exit * e1 = new Exit(r1, true, "e1", true);
        Exit * e2 = new Exit(r2);
        Exit * eevil = new Exit(evil, true, "evil", true);

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
        Object * k2 = new Key("evil");

        r1->drop(b1);
        r1->drop(b2);
        r1->drop(b3);
        r1->drop(k2);

        r2->drop(b4);

        Object * light_saber = new LightSaber(1000,0.95);
        evil->drop(light_saber);
        evil->drop(k1);


        // Create the player

        player = new Player(r1);
        r1->enter(*player);
        commands = new GameCommands(player);


        // Initialize actors

        new Troll(r2, 1000, 88);
        // r2->enter(*t);

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

    void Game::save() {
        std::fstream file;
        file.open ("saveFile", std::ios_base::out|std::ios_base::trunc);
        for (std::vector<Actor *>::iterator it = actors->begin(); it != actors->end(); ++it) {
            (*it)->save(file);
        }
        for (std::vector<Environment *>::iterator it = envs->begin(); it != envs->end(); ++it) {
            (*it)->save(file);
        }
        file.close();
    }

    void Game::load() {
        std::ifstream file("saveFile");
        if (!file.good()) {
            std::cout << "File isint good" << std::endl;
            initialize();
            return;
        }
        std::string line;

        std::vector<std::string> * lines = new std::vector<std::string>;
    
        std::map<std::string, Environment *> created_envs; // nyckeln är IDt som en sträng
        std::map<std::string, Object *> created_objects; // nyckeln är IDt som en sträng
        std::map<std::string, Exit *> created_exits; // nyckeln är IDt som en sträng

        while (std::getline(file, line)) {
            lines->push_back(line);
            std::string obj = line.substr(0, 3);
            std::string id = line.substr(0, line.find_first_of(':'));
            id = id.substr(3);

            if (obj == "ACT" || obj == "EXI") {
                // supress warnings for actors, which is handled later
            }
            else if (obj == "ENV") {
                Environment * environment = Environment::load(line);
                std::cout << "Loading new environment:" << id << std::endl;
                created_envs[id] = environment;

                // add_environment(*environment);
            }
            else if (obj == "OBJ") {
                Object * object = Object::load(line);
                if (object == NULL)
                    std::cerr << "Game::load(): NULL OBJECT RETURNED " << std::endl;
                created_objects[id] = object;
                // add_object(*object);
            } 
            else {
                std::cerr << "Invalid object type in save file: " << obj << std::endl;
                throw BadFileFormatException();
            }
        }


        for (std::vector<std::string>::iterator it = lines->begin(); it != lines->end(); ++it) {
            line = *it;
            std::string obj = line.substr(0, 3);
            std::string id = line.substr(0, line.find_first_of(':'));
            id = id.substr(3);

            // Put all objects into their environments
            if (obj == "ENV") {
                std::string objects = line.substr(line.find_first_of(':')+1);
                objects = objects.substr(0,objects.find_first_of(':'));

                while (true) {
                    std::string object = objects.substr(0,objects.find_first_of(','));
                    object =object.substr(3);
                    
                    if (created_objects.find(object) == created_objects.end())
                        std::cerr << "Game::load(): object NOT FOUND" << std::endl;
                    created_envs[id]->drop(created_objects[object]);  

                    if (created_objects.erase(object) == 0)
                        std::cerr << "ERROR: Didnt remove anything" << std::endl;
                    

                    if (objects.find_first_of(',') == std::string::npos)
                        break;
                    objects = objects.substr(objects.find_first_of(',')+1);

                }
            }
            // Put all objects into their containers
            else if (obj == "OBJ") {
                // Only interesting of obj is a container
                Container * bag = dynamic_cast<Container *>(created_objects[id]);
                if (bag != 0) {
                    // we got a container
                    std::string objects = line.substr(line.find_first_of(':')+1);
                    objects = objects.substr(objects.find_first_of(':')+1);
                    objects = objects.substr(0,objects.find_first_of(':'));

                    // Lets go through the objects that should be inside our container
                    while (objects.length() > 0) {
                        std::string object = objects.substr(0,objects.find_first_of(','));
                        object =object.substr(3);

                        bag->add(*created_objects[object]);
                        created_objects.erase(object);

                        if (objects.find_first_of(',') == std::string::npos)
                            break;
                        objects = objects.substr(objects.find_first_of(',')+1);

                    }
                }
            }
        }

        // Loop through the actors again, they need initalized envs and objs
        for (std::vector<std::string>::iterator it = lines->begin(); it != lines->end(); ++it) {
            line = *it;
            std::string obj = line.substr(0, 3);
            std::string id = line.substr(0, line.find_first_of(':'));
            id = id.substr(3);

            if (obj == "ACT") {
                Actor * actor = Actor::load(line, created_envs, created_objects); 
                if (actor != NULL) {
                    Player * player = dynamic_cast<Player *>(actor);
                    if (player != 0) {
                        commands = new GameCommands(player);
                        this->player = player;

                    }
                }

            }

            else if (obj == "EXI") {
                Exit * exit =  Exit::load(line, created_envs);
                created_exits[id] = exit;
            }
        }


        for (std::vector<std::string>::iterator it = lines->begin(); it != lines->end(); ++it) {
            line = *it;
            std::string obj = line.substr(0, 3);
            std::string id = line.substr(0, line.find_first_of(':'));
            id = id.substr(3);
            if (obj == "ENV") {
                std::istringstream input(line);
                std::vector<std::string> tokens;
                std::string token;

                while (std::getline(input, token, ':')) {
                    tokens.push_back(token);
                }

                std::map<std::string, std::string> properties;
                std::istringstream pss(tokens[3]);
                while (std::getline(pss, token, ',')) {
                    size_t eq_sign = token.find('=');
                    properties.insert(std::pair<std::string, std::string>(token.substr(0, eq_sign), token.substr(eq_sign+1)));
                }
                for (std::map<std::string, std::string>::iterator it = properties.begin(); it != properties.end(); ++it) {
                    created_envs[id]->add_exit(it->second, created_exits[it->first.substr(3)]);
                }
            }

        }

        delete lines;
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

