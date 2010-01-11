#include "bag.h"
#include <iostream>
#include <cstdlib>
#include <fstream>

namespace da_game {

    Bag::Bag() {
        objects = new std::vector<Object *>();
        hold_weight = std::rand()%150+100;
        hold_volume = std::rand()%50+100;
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
        int held_volume = 0;
        int held_weight = 0;

        for (std::vector<Object *>::const_iterator it = objects->begin(); it != objects->end(); ++it) {
            held_volume += (*it)->volume();
            held_weight += (*it)->weight();
        }

        if (held_volume + object.volume() > get_hold_volume() ||
                held_weight + object.weight() > get_hold_weight()) {
            return false;
        } else {
            this->objects->push_back(&object);
            return true;
        }
    }

    bool Bag::remove(Object & object) {
        std::vector<Object *>::iterator it;

        for (it = objects->begin(); it != objects->end(); it++) {
            if ((*it) == &object) {
                objects->erase(it);
                return true;
            }
        }
        return false;
    }

    void Bag::save(std::fstream & save) {
        save << "OBJ" << id << ":" << type() << ":"; 
        bool first = true;

        for (std::vector<Object *>::iterator it = objects->begin(); it != objects->end(); it++) {
            std::cout << "Saving " << (*it)->id << std::endl;
            if (first)
                first = false;
            else 
                save << ",";
            save << "OBJ" << (*it)->id;
        }
        save << ":" << weight() << "kg," << volume() << "liter," << price() << "kr" << std::endl;
        
        for (std::vector<Object *>::iterator it = objects->begin(); it != objects->end(); it++) {
            (*it)->save(save);
        }

    }
}
