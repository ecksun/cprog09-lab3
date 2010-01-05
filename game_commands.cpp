#include <iostream>
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
    }
    int GameCommands::exit(std::string) {
        return 1;
    }

    int GameCommands::go(std::string direction) {
        player->go(direction);
        return 0;
    }

    /*
     * TODO: need a way to get a opponent from a string
     */
    int GameCommands::fight(std::string ) {
        return 0;
    }
    /*
     * TODO: need a way to get a object from a string
     */
    int GameCommands::pick_up(std::string object) {
        try {
            Object * obj = get_object(player->in_room->objects, stringToInt(object));
            if (obj != 0) {
                if (player->in_room->pick_up(obj)) {
                    player->pick_up(obj);
                    return 0;
                }
            }
        }
        catch (...) {
        }
        std::cout << "No such item" << std::endl;
        return 0;
    }
    /*
     * TODO: need a way to get a object from a string
     */
    int GameCommands::drop(std::string object) {
        try {
            Object * obj = get_object(player->objects, stringToInt(object));
            if (obj != 0) {
                if (player->drop(obj)) {
                    player->in_room->drop(obj);
                    return 0;
                }
            }
        }
        catch (...) {}
        std::cout << "No such item" << std::endl;
        return 0;
    }
    /*
     * TODO: need a way to get a actor from a string
     * No problem, each actor has a unique ID
     */
    int GameCommands::talk_to(std::string actor) {
        Actor * act = get_actor(player->in_room->actors, stringToInt(actor));
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
        std::vector<Object *>::iterator it = player->objects->begin();
        for (; it != player->objects->end(); ++it) {
            std::cout << (*it)->id << "\t" << (*it)->type() << std::endl;
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
        for (; it != actors->end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        return 0;
    }
}
