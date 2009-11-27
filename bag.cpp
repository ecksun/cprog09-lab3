#include "bag.h"

namespace da_game {

    Bag::Bag() {
        objects = new std::vector<Object *>();
    }

    Bag::~Bag() {
        objects->clear();
        delete this->objects;
    }

    int Bag::weight() const {
        return 17;
    }

    int Bag::volume() const {
        return 50;
    }

    int Bag::price() const {
        return 100;
    }

    std::string Bag::type() const {
        return "Orch bag";
    }

    int Bag::get_hold_weight() const {
        return this->hold_weight;
    }

    int Bag::get_hold_volume() const {
        return this->hold_volume;
    }

    bool Bag::add(Object & object) {
        // TODO check that it fits in this bag
        this->objects->push_back(&object);
        return true;
    }

    bool Bag::remove(Object & object) {
        std::vector<Object *>::iterator it;
        bool found;

        for (it = objects->begin(); it != objects->end(); it++) {
            if ((*it) == &object) {
                objects->erase(it);
                found = true;
            }
        }

        return found;
    }

}
