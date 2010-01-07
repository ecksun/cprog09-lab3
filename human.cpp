#include <iostream>

#include "human.h"


namespace da_game {

    Human::Human(bool has_heart, int max_health) : has_heart(has_heart), max_health(max_health) {
        hp = 100;
    }

    void Human::run() {
        if (!has_heart) {
            // Undead, fast regen
            hp *= 2;
        }
        std::cout << "Ruuunning!" << std::endl;
    }

    std::string Human::get_name() const {
        return name;
    }

    void Human::eat(Food & food) {
        std::cout << "Yum! Food is great! Give me more " << std::endl;
        hp += food.health_increase();
        if (hp > max_health)
            hp = max_health;
    }

}

