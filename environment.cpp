#include "environment.h"
#include <iostream>

namespace da_game {
    Object * Environment::get_object(int id) {
        std::vector<Object *>::const_iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            std::cout << "comparing " << (*it)->id << " to " << id << std::endl;
            if ((*it)->id == id) {
                std::cout << "Found it!" << std::endl;
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
