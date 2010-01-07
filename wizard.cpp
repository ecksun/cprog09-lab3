#include <iostream>

#include "wizard.h"

namespace da_game {

    Wizard::Wizard(Environment * env, bool has_heart, int max_health, int max_magic)
        : Human(has_heart, max_health), magic(max_magic), max_magic(max_magic) {
            hp = 150;
            strength = 3;
            name = "Darth Sidious";
            this->current_room = env;
            // this->default_weapon = current_weapon; // instansiated in actor

            wand = new Wand(50, 0.9);
            objects->push_back(wand);
            std::cout << "A magician has been born, with full magic power.. Kazaaam!" << std::endl;

    }

    void Wizard::run() {
        magic += 5;
        if (magic >= max_magic)
            magic = max_magic;
    }

    Weapon * Wizard::weapon() {
        if (magic >= wand->magic_cost()) {
            std::cout << "Wand" << std::endl;
            magic -= wand->magic_cost();
            return wand;
        }
        else {
            // Not enough magic to use wand, using default-weapon
            return current_weapon;
        }
    }

    std::string Wizard::get_type() const {
        return "Wizard";
    }

    void Wizard::talk_to(Actor &)  {
        std::cout << "zoom zoom zoom" << std::endl;
    }
}
