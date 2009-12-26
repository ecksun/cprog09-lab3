#include "actor.h"
#include <iostream>

namespace da_game {
    int Actor::instances;

    Actor::Actor() : id(instances) {
        instances++;
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
}
