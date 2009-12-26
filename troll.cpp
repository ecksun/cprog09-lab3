#include "troll.h"
#include <iostream>
#include <cstdlib>

namespace da_game {
    Troll::Troll(Environment * current_room, int hp, int strength) { 
        this->hp = hp;
        this->strength = strength;
        // TODO: Perhaps we should move this up the inheretance tree?
        // might fit better in actor or something 
        this->current_room = current_room;
    }
    void Troll::eat(Actor &) {
        std::cout << "I dont like white meat" << std::endl;
    }

    void Troll::eat(Food & food) {
        hp += food.health_increase();
    }

    void Troll::run() {
        std::vector<std::string> rooms = current_room->directions();
        switch (std::rand()%5) {
            case 1: 
                go(rooms[std::rand()%rooms.size()]);
                break;
            default:
                break;
        }
    }

    std::string Troll::get_type() const {
        return "troll";
    }

    std::string Troll::get_name() const {
        return "nisse";
    }

    void Troll::go(std::string s) {
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
    void Troll::fight(Actor &) {
        return;
    }

    void Troll::pick_up(Object *) {
        std::cout << "Im a troll ffs, i dont have any pockets" << std::endl;
    }

    bool Troll::drop(Object *) {
        std::cout << "Watch out or I will drop YOU" << std::endl;
        return false;
    }

    void Troll::talk_to(Actor & actor) {
        std::cout << "GRUF!" << std::endl;
        actor.fight(*this);
    }
}
