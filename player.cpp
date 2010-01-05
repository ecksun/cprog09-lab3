#include "player.h"
#include <iostream>

namespace da_game {
    Player::Player(Environment * room) {
        this->in_room = room;
        std::cout << in_room->description() << std::endl;
        objects = new std::vector<Object *>;
    }
    void Player::run(){}
    std::string Player::get_type() const{
        return "DEMAN";
    }
    std::string Player::get_name() const{
        return "Klas-Göran";
    }

    void Player::go(std::string direction) { 
        Environment * new_room = in_room->neighbor(direction);
        if (new_room == 0) {
            std::cout << "No such room" << std::endl;

        }
        else {
            in_room->leave(*this);
            in_room = new_room;
            in_room->enter(*this);
        }
        std::cout << in_room->description() << std::endl;
    }

    void Player::fight(Actor &){}

    void Player::talk_to(Actor & actor){
        std::cout << "Hello dear " << actor.get_name() << std::endl;
    }
}
