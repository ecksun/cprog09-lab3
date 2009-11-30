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
        std::cout << "Im going " << direction << std::endl;
        Environment * new_room = in_room->neighbor(direction);
        if (new_room == 0) {
            std::cout << "No such room" << std::endl;

        }
        else {
            in_room = new_room;
        }
        std::cout << in_room->description() << std::endl;
    }

    void Player::fight(Actor &){}
    void Player::pick_up(Object & object){
        objects->push_back(&object);
        std::cout << "picked up " << std::endl;
    }
    void Player::drop(Object &){}
    void Player::talk_to(Actor &){}
}
