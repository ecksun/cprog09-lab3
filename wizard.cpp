#include <iostream>
#include <sstream>

#include "wizard.h"

namespace da_game {

    Wizard::Wizard(Environment * env, bool has_heart, int max_health, int max_magic)
        : Human(has_heart, max_health), magic(max_magic), max_magic(max_magic) {
            this->hp = 150;
            this->strength = 3;
            this->current_room = env;
            this->wand = new Wand(50, 0.9);
            std::cout << "A magician has been born, with full magic power.. Kazaaam!" << std::endl;

            env->enter(*this);
    }

    Wizard::Wizard(Environment * env, int hp, int strength, bool has_heart, int max_health, int magic, int max_magic)
        : Human(has_heart, max_health), magic(magic), max_magic(max_magic) {
            this->hp = hp;
            this->strength = strength;
            this->current_room = env;
            this->wand = new Wand(50, 0.9);
    }

    Wizard::~Wizard() {
        container->remove(*wand);
        delete wand;
    }

    void Wizard::run() {
        magic += 5;
        if (magic >= max_magic)
            magic = max_magic;
    }

    Weapon * Wizard::weapon() {
        if (magic >= wand->magic_cost()) {
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

    std::string Wizard::get_name() const {
        return "Darth Sidious";
    }

    void Wizard::talk_to(Actor &)  {
        std::cout << "zoom zoom zoom" << std::endl;
    }

    std::string Wizard::serialize() const {
        std::ostringstream o;
        o << Human::serialize();
        o << ",magic=" << magic;
        o << ",max_magic=" << max_magic;
        return o.str();
    }
}
