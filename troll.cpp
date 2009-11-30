#include "troll.h"
#include <iostream>

namespace da_game {
    Troll::Troll(int hp, int strength) { 
        this->hp = hp;
        this->strength = strength;
    }
    void Troll::eat(Actor &) {
        std::cout << "I dont like white meat" << std::endl;
    }

    void Troll::eat(Food & food) {
        hp += food.health_increase();
    }

    void Troll::run() {
        std::cout << "Im just sTrolling arround" << std::endl;
    }

    std::string Troll::get_type() const {
        return "troll";
    }

    std::string Troll::get_name() const {
        return "nisse";
    }

    void Troll::go(std::string s) {
        std::cout << "AHAHA, Im not going " << s << std::endl;
    }

    /*
     * I have no idea how we should implement this
     */
    void Troll::fight(Actor &) {
        return;
    }

    void Troll::pick_up(Object *) {
        std::cout << "Im a troll ffs, i dont have any pockets" << std::endl;
    }

    void Troll::drop(Object &) {
        std::cout << "Watch out or I will drop YOU" << std::endl;
    }

    void Troll::talk_to(Actor & actor) {
        std::cout << "GRUF!" << std::endl;
        actor.fight(*this);
    }
}
