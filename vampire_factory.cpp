#include <iostream>
#include <sstream>

#include "vampire_factory.h"
#include "vampire.h"
#include "game.h"


namespace da_game {

    VampireFactory::VampireFactory(Environment * env, int freq) : frequency(freq), age(0) {
            this->current_room = env;
            this->hp = 1000;
            this->strength = 0;
            current_room->enter(*this);
    }

    void VampireFactory::run() {
        age++;
        if (age%frequency == 0) {
            Vampire * vamp = new Vampire(current_room,3*age, 2*age);
            current_room->enter(*vamp);
        }
    }

    std::string VampireFactory::get_name() const {
        return "Vampire factory";
    }

    std::string VampireFactory::get_type() const {
        return "VampireFactory";
    }

    void VampireFactory::go(std::string) {
    }
    
    void VampireFactory::fight(Actor &) {

    }

    void VampireFactory::talk_to(Actor &) {

    }

    std::string VampireFactory::serialize() const {
        std::ostringstream o;
        o << "frequency=" << frequency;
        o << ",age=" << age;
        return o.str();
    }
}

