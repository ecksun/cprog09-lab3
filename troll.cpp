#include "troll.h"
#include "human.h"
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
        std::vector<std::string> exit_names = current_room->get_exit_names();

        switch (std::rand()%5) {
            case 1: 
                go(exit_names[std::rand()%exit_names.size()]);
                break;
            case 2:
                {
                    std::vector<Actor *> actors = current_room->get_actors();
                    std::vector<Actor *>::iterator it = actors.begin();

                    for (; it != actors.end(); ++it) {
                        Human * human = dynamic_cast<Human *>(*it);
                        if (human != NULL) {
                            fight(**it);
                            break;
                        }
                    }
                }
                break;
            default:
                break;
        }

    }

    std::string Troll::get_type() const {
        return "Troll";
    }

    std::string Troll::get_name() const {
        return "nisse";
    }

    bool Troll::pick_up(Object *) {
        std::cout << "I'm a troll ffs, I dont have any pockets" << std::endl;
        return false;
    }

    bool Troll::drop(Object *) {
        std::cout << "Watch out or I will drop YOU" << std::endl;
        return false;
    }

    void Troll::talk_to(Actor & actor) {
        std::cout << "GRUF!" << std::endl;
        actor.fight(*this);
    }

    std::string Troll::serialize() const {
        return "";
    }

}
