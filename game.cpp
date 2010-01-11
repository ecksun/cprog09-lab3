#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
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
        // load();
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
        VampireFactory * vamp_fac = new VampireFactory(evil, 2);
        evil->enter(*vamp_fac);
        
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
        std::string line;

        std::vector<std::string> * lines = new std::vector<std::string>;
    
        std::map<std::string, Environment *> created_envs; // nyckeln är IDt som en sträng
        // std::map<std::string, Actor *> created_actors; // nyckeln är IDt som en sträng
        std::map<std::string, Object *> created_objects; // nyckeln är IDt som en sträng

        while (std::getline(file, line)) {
            lines->push_back(line);
            std::string obj = line.substr(0, 3);
            std::string id = line.substr(0, line.find_first_of(':'));
            id = id.substr(3);

            if (obj == "ACT") {
                // supress warnings for actors, which is handled later
            }
            else if (obj == "ENV") {
                Environment * environment = Environment::load(line);
                created_envs[id] = environment;

                add_environment(*environment);
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
            }
        }

        std::cout << "Loaded objects:" << std::endl;
        for (std::map<std::string, Object *>::iterator it = created_objects.begin(); it != created_objects.end(); ++it) {
            std::cout << it->first << " => " << it->second->type() << std::endl;
        }   
        std::cout << "Loaded environments:" << std::endl;
        for (std::map<std::string, Environment *>::iterator it = created_envs.begin(); it != created_envs.end(); ++it) {
            std::cout << it->first << " => "  << std::endl;
        }   

        for (std::vector<std::string>::iterator it = lines->begin(); it != lines->end(); ++it) {
            line = *it;
            std::string obj = line.substr(0, 3);
            std::string id = line.substr(0, line.find_first_of(':'));
            id = id.substr(3);

            /*
             * ENV0:OBJ2,OBJ3,OBJ4,OBJ7:ACT1
             * ENV1:OBJ5:ACT2
             * ENV2:OBJ8,OBJ6,OBJ7:ACT0,ACT3
             */
            // Put all objects into their environments
            // TODO put the actors into their respective environment
            if (obj == "ENV") {
                std::string objects = line.substr(line.find_first_of(':')+1);
                objects = objects.substr(0,objects.find_first_of(':'));

                while (true) {
                    std::string object = objects.substr(0,objects.find_first_of(','));
                    object =object.substr(3);
                    
                    // std::cout << "Droping object("<<object<<") into env" << std::endl;
                    if (created_objects.find(object) == created_objects.end())
                        std::cerr << "Game::load(): object NOT FOUND" << std::endl;
                    // std::cout << created_objects[object] << std::endl;
                    // std::cout << created_objects[object]->type() << std::endl;
                    created_envs[id]->drop(created_objects[object]);  

                    if (created_objects.erase(object) == 0)
                        std::cout << "Didnt remove anything" << std::endl;
                    

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
                    // OBJ14:Orch bag:OBJ15:17kg,50liter,100kr
                    // std::cout << "Container!" << std::endl;
                    // std::cout << line << std::endl;
                    std::string objects = line.substr(line.find_first_of(':')+1);
                    objects = objects.substr(objects.find_first_of(':')+1);
                    objects = objects.substr(0,objects.find_first_of(':'));

                    // Lets go through the objects that should be inside our container
                    while (objects.length() > 0) {
                        // std::cout << "Objects:" <<objects << std::endl;
                        std::string object = objects.substr(0,objects.find_first_of(','));
                        object =object.substr(3);
                        // std::cout << "Putting object into container:" << object << std::endl;

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

            if (obj == "ACT") {
                std::cout << "ACT" << std::endl;
                Actor * actor = Actor::load(line, created_envs, created_objects); 
                if (actor != NULL) {
                    std::cout << "Casting " << std::endl;
                    Player * player = dynamic_cast<Player *>(actor);
                    if (player != 0) {
                        std::cout << "Initializing player" << std::endl;
                        commands = new GameCommands(player);
                    }
                }

                // FIXME Do we need to do more? they fix the rest themselves?
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

