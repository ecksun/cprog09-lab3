#include "evil_lair.h"
#include <iostream>

namespace da_game {

    /**
     * Constructs an empty evil lair
     */
    EvilLair::EvilLair() {
    }

    /*
     * If we give the objects an id directly from this vector there might be a 
     * problem when we try to pick up something that has already been picked up
     * by someone else.
     */
    std::string EvilLair::description() const {
        std::string description = Environment::description();
        description += "Evil Lair!";

        return description;
    }

}
