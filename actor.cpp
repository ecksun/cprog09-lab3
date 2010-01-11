#include "actor.h"
#include "bag.h"
#include "default_weapon.h"
#include "game.h"
#include "game_commands.h"

#include <iostream>
#include <map>
#include <sstream>

namespace da_game {
    int Actor::instances;

    Actor::Actor() : id(instances) {
        instances++;
        current_weapon = new DefaultWeapon();   // So everyone can try to fight,
                                                // Rember to delete this in inherited classes constructors
        container = new Bag(); // FIXME
        current_room = 0;
        Game::add_actor(*this);
    }

    Actor::~Actor() {
        if (current_weapon->weight() == 0 && current_weapon->volume() == 0) {
            // In case its the default weapon, we dont want them laying around
            // TODO fix this with a cast perhaps?
            delete current_weapon;
        }

        std::cout << "Droping everything Im carrying" << std::endl;
        // science the actor exists no more we drop everything in the current room
        std::vector<Object *>::iterator it;
        for (it = container->get_objects()->begin(); it != container->get_objects()->end(); ++it) {
            current_room->drop(*it);
        }
        std::cout << "clearing objects" << std::endl;
        container->get_objects()->clear();
        std::cout << "~Actor Drop container" << std::endl;

        current_room->drop(container);
        
        std::cout << "Leaving" << std::endl;
        current_room->leave(*this);
        std::cout << "remove_actor" << std::endl;
        Game::remove_actor(*this);
        std::cout << "~Actor done" << std::endl;
    }


    bool Actor::pick_up(Object * object){
        return container->add(*object);
    }

    bool Actor::drop(Object * object) {
        return container->remove(*object);
    }

    /**
     * Takes this actor to the environment that the given exit leads
     * to. However the exit must not be locked.
     *
     * @param exit_name The name of the exit to go through
     */
    void Actor::go(std::string exit_name) {
        Exit * exit = current_room->get_exit(exit_name);

        if (exit == 0) {
            std::cerr << "No such exit: " << exit_name << std::endl;
            return;
        }

        if (exit->is_locked()) {
            std::cerr << "Exit is locked -- unlock it in order to get through" << std::endl;
            return;
        }

        Environment * new_room = exit->get_outfall();

        if (new_room == 0) {
            std::cerr << "That exit leads nowhere..." << std::endl;
            return;
        }

        // if everything is in order, let the actor follow the exit
        current_room->leave(*this);
        current_room = new_room;
        current_room->enter(*this);
        std::cerr << get_name() << " entered " << exit_name << std::endl;
    }

    void Actor::fight(Actor & opponent) {
        GameCommands::fight(*this, opponent);
    }

    Weapon * Actor::weapon() {
        if (current_weapon == 0) {
            std::cerr << "FEEEL HÄR. Actor::weapon() in actor.cpp" << std::endl;
        }
        return current_weapon;
    }

    void Actor::save(std::ofstream & save) {
        save << "ACT" << id << ":" << get_type() << ":" << get_name() << ":";
        save << "current_room=" << current_room->id;
        save << ",hp=" << hp;
        save << ",strength=" << strength;

        if (serialize().length() > 0) {
            save << "," << serialize();
        }

        save << ":OBJ" << container->id;

        save << std::endl;
        container->save(save);
    }

    /**
     * Loads an actor object from the specified string.
     *
     * @param line A line describing the object to load
     * @return A pointer to a the created instance
     */
    Actor * Actor::load(const std::string line, const std::map<std::string, Environment *> & envs,
            const std::map<std::string, Object *> & objs) {
        std::istringstream input(line);
        std::vector<std::string> tokens;
        std::string token;

        while (std::getline(input, token, ':')) {
            tokens.push_back(token);
        }

        // extract properties
        std::map<std::string, std::string> properties;
        std::istringstream pss(tokens[3]);
        while (std::getline(pss, token, ',')) {
            size_t eq_sign = token.find('=');
            properties.insert(std::pair<std::string, std::string>(token.substr(0, eq_sign), token.substr(eq_sign+1)));
            std::cout << token.substr(0, eq_sign) <<  " = " << token.substr(eq_sign+1) << std::endl;
        }

        // find type
        std::string & type = tokens[1];
        Actor * actor;
        if (type == "Human") {

        }
        else if (type == "Player") {

        } 
        else if (type == "Wizard") {

        } 
        else if (type == "Troll") {

        } 
        else if (type == "Vampire") {

        }
        else if (type == "VampireFactory") {

        }
        else {
            std::cerr << "Unrecognized actor type: " << type << std::endl;
        }

        return actor;
    }

}
