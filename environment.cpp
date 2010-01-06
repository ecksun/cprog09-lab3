#include "environment.h"
#include <iostream>

namespace da_game {
    Environment::Environment() {
        objects = new std::vector<Object *>;
        actors = new std::vector<Actor *>;
    }

    Environment::~Environment() {
        delete objects;
        delete actors;
    }

    bool Environment::pick_up(Object * object) {
        std::vector<Object *>::iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            if (**it == *object) {
                objects->erase(it);
                return true;
            }
        }
        return false;
    }

    void Environment::drop(Object * object) {
        if (object != 0)
            objects->push_back(object);
        else 
            throw;
    }

    void Environment::enter(Actor & actor) {
        actors->push_back(&actor);
    }

    void Environment::leave(Actor & actor) {
        std::cerr << "someone is trying to leave" << std::endl;
        std::vector<Actor *>::iterator it = actors->begin();
        for (; it != actors->end(); ++it) {
            if (&(**it) == &actor) {
                actors->erase(it);
                return;
            }
        }
    }
}
