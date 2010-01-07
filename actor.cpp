#include "game.h"
#include "actor.h"
#include "default_weapon.h"
#include "game_commands.h"
#include <iostream>

namespace da_game {
    int Actor::instances;

    Actor::Actor() : id(instances) {
        instances++;
        current_weapon = new DefaultWeapon();   // So everyone can try to fight,
                                                // Rember to delete this in inherited classes constructors
        objects = new std::vector<Object *>;
        current_room = 0;
    }

    Actor::~Actor() {
        if (current_weapon->weight() == 0 && current_weapon->volume() == 0) {
            // In case its the default weapon, we dont want them laying around
            // TODO fix this with a cast perhaps?
            delete current_weapon;
        }

        // science the actor exists no more we drop everything in the current room
        std::vector<Object *>::iterator it;
        for (it = objects->begin(); it != objects->end(); ++it) {
            current_room->drop(*it);
        }

        delete objects;
        current_room->leave(*this);
        Game::removeActor(*this);
    }

    void Actor::pick_up(Object * object){
        objects->push_back(object);
        std::cout << "picked up " << object->type() << std::endl;
    }

    bool Actor::drop(Object * object) {
        std::vector<Object *>::iterator it;
        for (it = objects->begin(); it != objects->end(); ++it) {
            // TODO här får vi ett problem som måste lösas:
            // finns det någon som håller i objektet efter att 
            // det tagits bort ur vår inventory?
            // annars borde det delete:as
            // Det vore eventuellt rätt najs med auto_ptr här så
            // att objekt bara kan ägas av precis en sak. Eller?
            if (**it == *object) {
                objects->erase(it);
                return true;
            }
        }
        return false;
    }

    void Actor::go(std::string s) {
        Environment * new_room = current_room->neighbor(s);
        if (new_room == 0) {
            std::cerr << "Couldnt go to room " << s  << std::endl;
        }
        else {
            current_room->leave(*this);
            current_room = new_room;
            current_room->enter(*this);
            std::cerr << get_name() << " entered " << s << std::endl;
        }
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

    std::vector<Object *> Environment::get_objects() {
        return *objects;
    }

    std::vector<Actor *> Environment::get_actors() {
        return *actors;
    }
}
