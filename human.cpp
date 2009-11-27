#include <iostream>

#include "human.h"


namespace da_game {

    Human::Human(bool has_heart, int max_health) : has_heart(has_heart), max_health(max_health) {

    }

    void Human::run() {
        std::cout << "Ruuunning!" << std::endl;
    }

    std::string Human::get_name() const {
        return name;
    }

    void Human::eat(Food & food) {
        std::cout << "Yum! Food is great! Give me more " << std::endl;
    }

}

