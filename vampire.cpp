#include "vampire.h"
#include <iostream>
#include <cstdlib>

namespace da_game {
    Vampire::Vampire(Environment * current_room, int hp, int strength) { 
        this->hp = hp;
        this->strength = strength;
        // TODO: Perhaps we should move this up the inheretance tree?
        // might fit better in actor or something 
        this->current_room = current_room;
    }
    void Vampire::eat(Actor & actor) {
        actor.fight(*this);
    }

    void Vampire::eat(Food &) {
        std::cout << "Bläh" << std::endl;
    }

    void Vampire::run() {
        std::vector<std::string> exit_names = current_room->get_exit_names();
        switch (std::rand()%3) {
            case 1: 
                go(exit_names[std::rand()%exit_names.size()]);
                break;
            default:
                break;
        }
    }

    std::string Vampire::get_type() const {
        return "Vampire";
    }

    std::string Vampire::get_name() const {
        return "Drakula";
    }

    void Vampire::go(std::string s) {
        Environment * new_room = current_room->neighbor(s);
        if (new_room == 0) {
            std::cerr << "Couldnt go to room " << s  << std::endl;
        }
        else {
            current_room->leave(*this);
            current_room = new_room;
            current_room->enter(*this);
            std::cerr << get_name() << " entered " << s << std::endl;
        }
    }

    /*
     * I have no idea how we should implement this
     */
    void Vampire::fight(Actor &) {
        return;
    }

    void Vampire::pick_up(Object *) {
        std::cout << "IIIHH" << std::endl;
    }

    bool Vampire::drop(Object *) {
        std::cout << "IHHHHIIII" << std::endl;
        return false;
    }

    void Vampire::talk_to(Actor &) {
        std::cout << "SHREEK!" << std::endl;
    }
}
