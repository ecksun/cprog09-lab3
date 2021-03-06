#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "game_commands.h"

namespace da_game {
    Player * GameCommands::player;
    GameCommands::GameCommands(Player * pl) {
        GameCommands::player = pl;
        Terminal::add_function(std::string("exit"), &GameCommands::exit);
        Terminal::add_function(std::string("quit"), &GameCommands::exit);
        Terminal::add_function(std::string("go"), &GameCommands::go);
        Terminal::add_function(std::string("fight"), &GameCommands::fight);
        Terminal::add_function(std::string("pick_up"), &GameCommands::pick_up);
        Terminal::add_function(std::string("drop"), &GameCommands::drop);
        Terminal::add_function(std::string("talk_to"), &GameCommands::talk_to);
        Terminal::add_function(std::string("help"), &GameCommands::help);
        Terminal::add_function(std::string("inventory"), &GameCommands::inventory);
        Terminal::add_function(std::string("use"), &GameCommands::use);
        Terminal::add_function(std::string("save"), &GameCommands::save);
        Terminal::add_function(std::string("load"), &GameCommands::load);
    }

    int GameCommands::exit(std::string) {
        return 1;
    }

    int GameCommands::save(std::string) {
        return 2;
    }

    int GameCommands::load(std::string) {
        return 3;
    }

    int GameCommands::go(std::string direction) {
        player->go(direction);
        return 0;
    }

    /*
    */
    int GameCommands::fight(std::string actor) {
        Actor * opponent = get_actor(player->current_room->actors, stringToInt(actor));
        if (opponent != 0) {
            // Player begins to fight
            fight(*player, *opponent);
        }
        else {
            std::cout << "Ingen sådan person här inne" << std::endl;
        }
        return 0;
    }

    void GameCommands::fight(Actor & attacker, Actor & defender) {
        std::cout << "Fight:\t" << attacker.get_name() << " vs " << defender.get_name() << std::endl;
        std::stringstream s;
        for (unsigned int round = 0; attacker.hp > 0 && defender.hp > 0; round++) {
            s << "Attacker HP:   " << attacker.hp << std::endl;
            s << "Defender HP:   " << defender.hp << std::endl;
            if ((round & 1) == 0) {
                // Even, attackers turn

                if (std::rand()/RAND_MAX <= attacker.weapon()->hit_ratio()) {
                    int hit = attacker.weapon()->attack_strength()*attacker.strength;
                    defender.hp -= hit;
                    s << attacker.get_name() << " hit " << defender.get_name() << " and he lost " << hit << "hp" << std::endl;
                }
                else {
                    s << "You missed!" << std::endl;
                }
            }
            else {
                // Defenders turn
                if (std::rand()/RAND_MAX <= defender.weapon()->hit_ratio()) {
                    int hit = defender.weapon()->attack_strength()*defender.strength;
                    attacker.hp -= hit;
                    s << defender.get_name() << " hit " << attacker.get_name() << " and he lost " << hit << "hp" << std::endl;
                }
                else {
                    s << "Defender missed!" << std::endl;
                }

            }
        }
        if (defender.hp <= 0) {
            s << "Attacker won!" << std::endl;
            delete &defender;
        }
        else {
            s << "You lost and died!" << std::endl;
            delete &attacker;
        }
        Terminal::print(s.str());
    }

    /*
    */
    int GameCommands::pick_up(std::string object) {
        try {
            Object * obj = get_object(player->current_room->objects, stringToInt(object));
            if (obj != 0) {
                if (player->current_room->pick_up(obj)) {
                    if (player->pick_up(obj)) {
                        std::cout << "picked up " << obj->type() << std::endl;
                        return 0;
                    }
                    else {
                        std::stringstream string;
                        string << "Couldnt fit " << obj->type() << " into bag" << std::endl;
                        string << "Bag stats: " << player->container->type() << std::endl;
                        string << "    Volume Left: " << player->container->get_volume_left() << std::endl;
                        string << "    Weight Left: " << player->container->get_weight_left() << std::endl;
                        string << std::endl;
                        string << "Object: " << obj->type() << std::endl;
                        string << "    Volume: " << obj->volume() << std::endl;
                        string << "    Weight: " << obj->weight() << std::endl;
                        Terminal::print(string.str());

                        player->current_room->drop(obj);
                        return 0;
                    }
                }
            }
        }
        catch (...) {
        }
        std::cout << "No such item" << std::endl;
        return 0;
    }
    /*
    */
    int GameCommands::drop(std::string object) {
        try {
            Object * obj = get_object(player->container->get_objects(), stringToInt(object));
            if (obj != 0) {
                if (player->drop(obj)) {
                    player->current_room->drop(obj);
                    return 0;
                }
            }
        }
        catch (...) {}
        std::cout << "No such item" << std::endl;
        return 0;
    }
    /*
    */
    int GameCommands::talk_to(std::string actor) {
        Actor * act = get_actor(player->current_room->actors, stringToInt(actor));
        if (act != 0) {
            player->talk_to(*act);
        }
        else {
            std::cout << "Ingen sådan person här inne" << std::endl;
        }
        return 0;
    }

    int GameCommands::help(std::string) {
        const std::map<std::string, int (*)(std::string)> & functions = Terminal::get_functions();
        std::map<std::string, int (*)(std::string)>::const_iterator it;

        for (it = functions.begin(); it != functions.end(); it++) {
            std::cout << it->first << std::endl;
        }

        return 0;
    }

    int GameCommands::inventory(std::string) {
        std::vector<Object *>::iterator it = player->container->get_objects()->begin();
        for (; it != player->container->get_objects()->end(); ++it) {
            std::cout << (*it)->id << "\t" << (*it)->type() << std::endl;
        }
        return 0;
    }

    /**
     * Lets the player use objects, either the objects alone or in
     * combination with other things such as keys on exits.
     *
     * @param arg The specified argument
     * @return 0 if successfully used
     */
    // TODO: make sure the item being used is either in invetory or in the same room
    int GameCommands::use(std::string arg) {
        if (arg == "use") {
            arg = ""; // ugly hack for the words size to be 0
        }

        // split arg string on whitespace into words vector
        std::istringstream iss(arg);
        std::vector<std::string> words;
        copy(std::istream_iterator<std::string>(iss),
                std::istream_iterator<std::string>(),
                std::back_inserter<std::vector<std::string> >(words));

        // get objects from arg words, if possible
        int id;
        std::vector<Object *> objs;
        for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
            std::istringstream stream(*it);
            if (stream >> id) {
                objs.push_back(get_object(player->container->get_objects(), id));
                // please notice that indices might get out of sync here
            }
        }

        switch (words.size()) {
            case 0:
                std::cerr << "What do you want to use?" << std::endl;
                return -1;
            case 1:
                {
                    Weapon * weapon = dynamic_cast<Weapon *>(objs[0]);
                    if (weapon != 0) {
                        std::cout << "Changing weapon to :" << weapon->type() << std::endl;
                        player->current_weapon = weapon;
                    }

                    Food * food = dynamic_cast<Food *>(objs[0]);
                    if (food != 0) {
                        player->eat(*food);
                    }

                    Container * bag = dynamic_cast<Container *>(objs[0]);
                    if (bag != 0) {
                        int held_volume = 0;
                        int held_weight = 0;
                        for (std::vector<Object *>::const_iterator it = player->container->get_objects()->begin(); 
                                it != player->container->get_objects()->end(); ++it) {
                            held_volume += (*it)->volume();
                            held_weight += (*it)->weight();
                        }

                        if (held_weight <= bag->get_hold_weight() && held_volume <= bag->get_hold_volume()) {
                            std::cout << "Changing bag" << std::endl;
                            while (player->container->get_objects()->size() > 0) {
                                Object * o = player->container->get_objects()->at(player->container->get_objects()->size()); // Get the item
                                bag->add(*o); // add it to the new bag
                                player->container->remove(*o); // remove it from the old
                            }
                            player->current_room->drop(player->container);
                            player->container = bag;
                        }
                        else {
                            std::stringstream string;
                            string << "You cant fit everything in this bag" << std::endl;
                            string << "Old bag: " << player->container->type() << std::endl;
                            string << "    Volume: " << player->container->get_hold_volume() << std::endl;
                            string << "    Weight: " << player->container->get_hold_weight() << std::endl;
                            string << std::endl;
                            string << "New bag: " << bag->type() << std::endl;
                            string << "    Volume: " << bag->get_hold_volume() << std::endl;
                            string << "    Weight: " << bag->get_hold_weight() << std::endl;
                            Terminal::print(string.str());
                        }
                    }
                    break;
                }
            case 2: 
                {
                    // Keys
                    Key * key = dynamic_cast<Key *>(objs[0]);
                    if (key != 0) {
                        Exit * exit = dynamic_cast<Exit *>(player->get_room()->get_exit(words[1]));
                        if (exit != 0) {
                            exit->toggle_lock(key);
                        }
                    }

                    // Do the same for other type of objects here
                    // ...
                    break;
                }
            default:
                return -1;
        }

        return 0;
    }


    int GameCommands::stringToInt(std::string string) {
        int num = -4711;
        std::istringstream stream(string);
        if (!(stream >> num)) {
            // TODO: fixa ett riktigt exception
            throw -4711;
        }
        return num;
    }

    Object * GameCommands::get_object(std::vector<Object *> * objects, int id) {
        std::vector<Object *>::const_iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        return 0;
    }

    Actor * GameCommands::get_actor(std::vector<Actor *> * actors, int id) {
        std::vector<Actor *>::const_iterator it = actors->begin();
        std::cerr << "get_actor" << std::endl;
        for (; it != actors->end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        std::cerr << "get_actor" << std::endl;
        return 0;
    }
}
