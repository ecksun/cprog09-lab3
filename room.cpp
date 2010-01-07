#include "room.h"
#include <iostream>

namespace da_game {

    /**
     * Constructs an empty room with no exits.
     */
    Room::Room() {
    }

    /**
     * Constructs a new room with the specified exits.
     */
    Room::Room(Exit * east, Exit * west, Exit * north, Exit * south) 
        : Inside(east, west, north, south) {
    }

    /*
     * If we give the objects an id directly from this vector there might be a 
     * problem when we try to pick up something that has already been picked up
     * by someone else.
     */
    std::string Room::description() const {
        std::string description = Environment::description();
        description += "This is a room!";

        return description;
    }

}
