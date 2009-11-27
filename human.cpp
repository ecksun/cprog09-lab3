#include <iostream>

#include "human.h"


namespace da_game {

    Human::Human(bool has_heart, int max_health) : has_heart(has_heart), max_health(max_health) {

    }

    void run() {
        std::cout << "Ruuunning!" << std::endl;
    }

    std::string get_name() {
        return name;
    }

    void Human::eat(Food & food) {
        std::cout << "Yum! Food is great!" << std::endl;
    }

}

