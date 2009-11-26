#include "bag.h"

namespace da_game {

    Bag::Bag() {
        this->objects = new std::vector<Object *>();
    }

    Bag::~Bag() {
        this->objects->clear();
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

    int Bag::hold_weight() const {
        return this->hold_weight_;
    }

    int Bag::hold_volume() const {
        return this->hold_volume_;
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
