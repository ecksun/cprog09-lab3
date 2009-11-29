#include "room.h"
#include <iostream>

namespace da_game {
    std::string Room::description() const {
        return "This is a room";
    }
    std::vector<std::string> Room::directions() const {
        std::map<std::string, Environment *>::const_iterator it = neighbors.begin();
        std::vector<std::string> return_directions;
        for (; it != neighbors.end(); ++it) {
            return_directions.push_back(it->first);
        }
        return return_directions;
    }
    Environment & Room::neighbor(std::string direction) const {
        std::map<std::string, Environment *>::const_iterator it = neighbors.find(direction);

        if (it != neighbors.end()) {
            return (*it->second);
        }
        else {
            std::cout << "No such direction" << std::endl;
            throw;
            // Throw exception or something, needs a return
        }
    }
    void Room::enter(Actor &) {

    }

    void Room::leave(Actor &) {

    }

    bool Room::pick_up(Object &) {
        return false;
    }
    void Room::drop(Object &) {

    }
}
