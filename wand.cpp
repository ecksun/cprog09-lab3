#include "wand.h"
#include <stdexcept>

namespace da_game {

    Wand::Wand(unsigned int attack, float ratio) : Weapon(attack, ratio) {
    }

    int Wand::weight() const {
        return 2;
    }

    int Wand::volume() const {
        return 2;
    }

    int Wand::price() const {
        return 285;
    }

    std::string Wand::type() const {
        return "Magical wand";
    }

    int Wand::magic_cost() const {
        return 25;
    }
}
