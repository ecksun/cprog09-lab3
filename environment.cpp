#include "environment.h"
#include <iostream>

namespace da_game {
    bool Environment::pick_up(Object * object) {
        std::vector<Object *>::iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            if (**it == *object) {
                objects->erase(it);
                return true;
            }
        }
        return false;
    }

    void Environment::drop(Object * object) {
        if (object != 0)
            objects->push_back(object);
        else 
            throw;
    }
}
