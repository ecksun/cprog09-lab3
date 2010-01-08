#include "container.h"
#include <iostream>

namespace da_game {
    std::vector<Object *> * Container::get_objects() {
        return objects;
    }

    int Container::get_weight_left() const {
        int held_weight = 0;
        for (std::vector<Object *>::const_iterator it = objects->begin(); 
                it != objects->end(); ++it) {
            held_weight += (*it)->weight();
        }

        return get_hold_weight() - held_weight;
    }

    int Container::get_volume_left() const {
        int held_volume = 0;
        for (std::vector<Object *>::const_iterator it = objects->begin(); 
                it != objects->end(); ++it) {
            held_volume += (*it)->volume();
        }
        return get_hold_volume() - held_volume;
    }
}
