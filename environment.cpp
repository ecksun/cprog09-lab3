#include "environment.h"
#include <iostream>

namespace da_game {
    Object * Environment::get_object(int id) {
        std::vector<Object *>::const_iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            if ((*it)->id == id) {
                return *it;
            }
        }
        return 0;
    }

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
}
