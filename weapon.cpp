#include "weapon.h"
#include <stdexcept>

namespace da_game {

    Weapon::Weapon(unsigned int attack, float ratio) {
        this->strength = attack;
        if (ratio >= 0 && ratio <= 1) {
            this->ratio = ratio;
        }
        else {
            // Shouldnt happen
            this->ratio = 0;
            throw std::out_of_range("index out of range");
        }
    }

    std::string Weapon::type() const {
        return "Weapon";
    }

    int Weapon::attack_strength() const {
        return strength;
    }

    float Weapon::hit_ratio() const {
        return ratio;
    }
    void Weapon::save(std::ofstream & save) {
        save << "OBJ" << id << ":" << type(); 
        save << ":" << weight() << "kg," << volume() << "liter," << price() << "kr," << strength << "strength," << ratio << "ratio" << std::endl;

    }
}
