#include "actor.h"
#include "default_weapon.h"
#include "game_commands.h"
#include <iostream>

namespace da_game {
    int Actor::instances;

    Actor::Actor() : id(instances) {
        instances++;
        current_weapon = new DefaultWeapon(); // So everyone can try to fight
        objects = new std::vector<Object *>;
    }

    Actor::~Actor() {
        if (current_weapon->weight() == 0 && current_weapon->volume() == 0) {
            // In case its the default weapon
            delete current_weapon;
        }

        // science the actor exists no more we drop everything in the current room
        std::vector<Object *>::iterator it;
        for (it = objects->begin(); it != objects->end(); ++it) {
            current_room->drop(*it);
        }

        delete objects;
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

    void Actor::fight(Actor & opponent) {
        GameCommands::fight(*this, opponent);
    }

    Weapon * Actor::weapon() {
        if (current_weapon == 0) {
            std::cerr << "FEEEL HÄR. Actor::weapon() in actor.cpp" << std::endl;
        }
        return current_weapon;
    }
}
