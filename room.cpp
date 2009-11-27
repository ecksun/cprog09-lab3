#include "room.h"

namespace da_game {
    std::string Room::description() const {
        return "This is a room";
    }
    std::vector<std::string> Room::directions() const {
        return neighbors;
    }
    Environment & Room::neighbor(std::string direction) const {
        std::map<std::string, Environment *>::iterator it = neighbors.find(direction);

        if (it != neighbors.end()) {
            return it->second(arguments);
        }
        else {
            std::cout << "No such direction" << std::endl;
            // Throw exception or something, needs a return
        }
    }
}
