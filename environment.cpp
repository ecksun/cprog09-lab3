#include "environment.h"
#include <iostream>
#include <sstream>
#include "game.h"

namespace da_game {
    int Environment::instances;

    Environment::Environment() :id (instances) {
        instances++;
        objects = new std::vector<Object *>;
        actors = new std::vector<Actor *>;
        Game::add_environment(*this);
    }

    Environment::~Environment() {
        // when an environment is destroyed everything in it need to be deleted
        
        
        actors->clear();
        
        delete actors;

        objects->clear();


        delete objects;
        std::cout << "~Env done" << std::endl;
    }

    std::string Environment::description() const {
        std::stringstream s;
        s << "Objects:" << std::endl;
        for (size_t i = 0; i < objects->size(); ++i) {
            s << objects->at(i)->id << "  " << objects->at(i)->type() << std::endl;
        }
        
        s << "Actors:" << std::endl;
        for (size_t i = 0; i < actors->size(); ++i) {
            s << actors->at(i)->id << "  " << actors->at(i)->get_type() << std::endl;
        }
 
        s << "Exits:" << std::endl;
        std::vector<std::string> exit_names = get_exit_names();
 
        for (size_t i = 0; i < exit_names.size(); ++i) {
            s << exit_names[i] << std::endl;
        }
 
        return s.str();
    }

    /**
     * Adds the specified exit with the given name (preferably a point
     * of the compass) to this environment.
     *
     * @return True if the exit was added or false if an exit with the 
     * same value already existed
     */
    bool Environment::add_exit(std::string name, Exit * exit) {
        std::pair<std::string, Exit *> pair(name, exit);
        std::pair<std::map<std::string, Exit *>::iterator, bool> result = exits.insert(pair);

        return result.second;
    }

    /**
     * Returns the exit with the given name, if there is a such.
     *
     * @param name The name of the exit
     * @return The exit with the given name
     */
    Exit * Environment::get_exit(std::string name) const {
        std::map<std::string, Exit *>::const_iterator it = exits.find(name);

        if (it != exits.end()) {
            return it->second;
        }
        else {
            std::cout << "No such exit" << std::endl;
            return 0;
            // Throw exception or something, needs a return
        }
    }

    /**
     * Returns a list of all available exits in this environment.
     *
     * @return List of exits
     */
    std::vector<std::string> Environment::get_exit_names() const {
        std::map<std::string, Exit *>::const_iterator it;
        std::vector<std::string> return_exits;

        for (it = exits.begin(); it != exits.end(); ++it) {
            return_exits.push_back(it->first);
        }

        return return_exits;
    }

    /**
     * Lets the specified actor enter this environment.
     *
     * @param actor The actor to enter
     */
    void Environment::enter(Actor & actor) {
        actors->push_back(&actor);
    }

    /**
     * Lets an actor leave this environment.
     *
     * @param actor The actor to leave
     */
    void Environment::leave(Actor & actor) {
        std::vector<Actor *>::iterator it = actors->begin();
        for (; it != actors->end(); ++it) {
            if (&(**it) == &actor) {
                actors->erase(it);
                return;
            }
        }
    }

    /**
     * Someone picks up an object that is owned by this environment.
     * That means this environment must hand over the object in
     * question.
     *
     * @param object The object that is being picked up
     * @return True if the object really was held by this environment,
     * otherwise false.
     */
    bool Environment::pick_up(Object * object) {
        std::vector<Object *>::iterator it = objects->begin();
        for (; it != objects->end(); ++it) {
            if (**it == *object) {
                std::cout << "Erasing " << (*it)->type() << std::endl;
                objects->erase(it);
                return true;
            }
        }
        return false;
    }

    /**
     * Someone drops an object in this environment. That means this
     * environment must take care of it.
     *
     * @param object The object that is being dropped
     */ 
    void Environment::drop(Object * object) {
        std::cout << "Env::drop" << std::endl;
        if (object != 0)
            objects->push_back(object);
        else 
            throw;
    }
    void Environment::save(std::ofstream & save) {
        save << "ENV" << id << ":";
        bool first = true;

             first = true;
        for (size_t i = 0; i < objects->size(); ++i) {
            if (first)
                first = false;
            else
                save << ",";
            save << "OBJ" << objects->at(i)->id;
        }
        save << ":";
        first = true;
        for (size_t i = 0; i < actors->size(); ++i) {
            if (first)
                first = false;
            else
                save << ",";
            save << "ACT" << actors->at(i)->id;
        }
        save << ":";
        first = true;
        for (std::map<std::string, Exit *>::iterator it = exits.begin(); it != exits.end(); ++it) {
            if (first)
                first=false;
            else
                save << ",";
            save << "EXI" << it->second->id << "=" << it->first;
        }
        save << std::endl;

        for (size_t i = 0; i < objects->size(); ++i) {
            objects->at(i)->save(save );
        }

        for (std::map<std::string, Exit *>::iterator it = exits.begin(); it != exits.end(); ++it) {
            it->second->save(save, it->first);
        }
 
    }
    std::vector<Object *> Environment::get_objects() {
        return *objects;
    }

    std::vector<Actor *> Environment::get_actors() {
        return *actors;
    }

    /*
ENV0:OBJ2,OBJ3,OBJ4,OBJ7:ACT1
ENV1:OBJ5:ACT2
ENV2:OBJ8,OBJ6,OBJ7:ACT0,ACT3
*/
    Environment * Environment::load(std::string) {
        return new Environment;
    }

}
