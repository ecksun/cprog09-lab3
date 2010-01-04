#include "room.h"
#include <iostream>

namespace da_game {

    Room::Room(Environment * east, Environment * west, Environment * north, Environment * south) 
        : Inside(east, west, north, south){
    }

    bool Room::add_neighbor(std::string direction, Environment * neighbor) {
        std::pair<std::string, Environment *> pair(direction, neighbor);
        std::pair<std::map<std::string, Environment *>::iterator, bool> result = neighbors.insert(pair);
        return result.second;

    }

    /*
     * If we give the objects an id directly from this vector there might be a 
     * problem when we try to pick up something that has already been picked up
     * by someone else.
     */
    std::string Room::description() const {
        std::cout << "Objects:" << std::endl;
        for (size_t i = 0; i < objects->size(); ++i) {
            std::cout << objects->at(i)->id << "\t" << objects->at(i)->type() << std::endl;
        }
        
        std::cout << "Persons:" << std::endl;
        for (size_t i = 0; i < actors->size(); ++i) {
            std::cout << actors->at(i)->id << "\t" << actors->at(i)->get_type() << std::endl;
        }

        std::cout << "Directions:" << std::endl;
        std::vector<std::string> rooms = directions();

        for (size_t i = 0; i < rooms.size(); ++i) {
            std::cout << rooms[i] << std::endl;
        }

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
    Environment * Room::neighbor(std::string direction) const {
        std::map<std::string, Environment *>::const_iterator it = neighbors.find(direction);

        if (it != neighbors.end()) {
            return it->second;
        }
        else {
            std::cout << "No such direction" << std::endl;
            return 0;
            // Throw exception or something, needs a return
        }
    }
}
