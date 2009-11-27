#include "player.h"
#include <iostream>

namespace da_game {
    void Player::run(){}
    std::string Player::get_type() const{
        return "DEMAN";
    }
    std::string Player::get_name() const{
        return "Klas-Göran";
    }
    void Player::go(std::string direction) { 
        std::cout << "Im going " << direction << std::endl;
    }
    void Player::fight(Actor &){}
    void Player::pick_up(Object &){}
    void Player::drop(Object &){}
    void Player::talk_to(Actor &){}
}
