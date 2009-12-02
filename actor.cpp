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
        std::vector<Object *>::iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            if (**it == *object) {
                objects->erase(it);
                return true;
            }
        }
        return false;
    }

}
