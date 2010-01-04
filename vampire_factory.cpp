#include <iostream>

#include "vampire_factory.h"


namespace da_game {

    VampireFactory::VampireFactory(Environment * env, int freq) : frequency(freq), age(0) {
            this->current_room = env;
            this->hp = 1000;
            this->strength = 0;
    }

    void VampireFactory::run() {
        age++;
        if (age%frequency == 0) {
            std::cerr << "Spawning a new vampire" << std::endl; 
            //current_room->enter(new vampire...
        }
    }

    std::string VampireFactory::get_name() const {
        return "Vampire factory";
    }

    std::string VampireFactory::get_type() const {
        return "factory";
    }

    void VampireFactory::go(std::string) {
    }
    
    void VampireFactory::fight(Actor &) {

    }

    void VampireFactory::talk_to(Actor &) {

    }
}

