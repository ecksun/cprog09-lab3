#include "troll.h"
#include <iostream>

namespace da_game {
    Troll::Troll(int hp, int strength) { 
        this->hp = hp;
        this->strength = strength;
    }
    void Troll::eat(Actor & a) {
        std::cout << "I dont like white meat" << std::endl;
    }

    void Troll::eat(Food & food) {
        hp += food.health_increase();
    }

    void Troll::run() {
        std::cout << "Im just sTrolling arround" << std::endl;
    }

    std::string Troll::type() {
        return "troll";
    }

    std::string Troll::name() {
        return "nisse";
    }

    void Troll::go(std::string s) {
        std::cout << "AHAHA, Im not going " << s << std::endl;
    }

    /*
     * I have no idea how we should implement this
     */
    void Troll::fight(Actor & fighter) {
        return;
    }

    void Troll::pick_up(Object &) {
        std::cout << "Im a troll ffs, i dont have any pockets" << std::endl;
    }

    void Troll::drop(Object &) {
        std::cout << "Watch out or I will drop YOU" << std::endl;
    }

    void Troll::talk_to(Actor & a) {
        std::cout << "GRUF!" << std::endl;
        a.fight(*this);
    }
}
