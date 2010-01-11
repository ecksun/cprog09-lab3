#include "light_saber.h"
#include <stdexcept>

namespace da_game {

    LightSaber::LightSaber(unsigned int attack, float ratio) : Weapon(attack, ratio) {
        // this->strength = attack;
        // if (ratio >= 0 && ratio <= 1) {
            // this->ratio = ratio;
        // }
        // else {
            // // Shouldnt happen
            // this->ratio = 0;
            // throw std::out_of_range("index out of range");
        // }
    }

    int LightSaber::weight() const {
        return 5;
    }

    int LightSaber::volume() const {
        return 5;
    }

    int LightSaber::price() const {
        return 1000;
    }

    std::string LightSaber::type() const {
        return " light saber";
        std::string return_value = "";
        switch (id % 5) {
            case 0:
                return_value = "Red";
                break;
            case 1:
                return_value = "Blue";
                break;
            case 2:
                return_value = "Green";
                break;
            case 4:
                return_value = "Purple";
                break;
            case 5:
                return_value = "Black";
                break;
        }
        return_value += " light saber";

        return return_value;
    }
}
