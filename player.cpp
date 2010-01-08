#include "player.h"
#include <iostream>

namespace da_game {
    Player::Player(Environment * room) : Human(false, 500){
        this->current_room = room;
        this->hp = 100;
        this->strength = 2;
    }

    Player::~Player() {
        // Player has lost :(
        // Varför körs inte den här dekonstruktorn när man dör?
        std::cerr << "Destrukting player" << std::endl;

    }

    void Player::run(){
        std::cout << "-----------------" << std::endl;;
        std::cout << "HP:\t" << hp << std::endl;
    }
    std::string Player::get_type() const{
        return "DEMAN";
    }
    std::string Player::get_name() const{
        return "Klas-Göran";
    }

    void Player::fight(Actor &){}

    void Player::talk_to(Actor & actor){
        if (&actor == this) {
            std::cout << "Hej på mig O_o" << std::endl;
            return;
        }
        std::cout << "Hello dear " << actor.get_name() << std::endl;
        actor.talk_to(*this);
    }

    Environment * Player::getRoom() const {
        return current_room;
    }
}
