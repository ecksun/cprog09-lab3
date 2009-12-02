#ifndef DA_GAME_ACTOR_H
#define DA_GAME_ACTOR_H

#include <string>
#include <vector>

#include "object.h"

namespace da_game {
    
    class Environment;

    class Actor {
        public:
            const int id;
            Actor();

            virtual void run() = 0;
            virtual std::string get_type() const = 0;
            virtual std::string get_name() const = 0;
            virtual void go(std::string) = 0;
            virtual void fight(Actor &) = 0;
            virtual void pick_up(Object *);
            virtual bool drop(Object *);
            virtual void talk_to(Actor &) = 0;
        protected:
            static int instances;

            int hp;
            int strength;
            Environment * current_room;
            std::vector<Object *> * objects;
    };
}
#endif // DA_GAME_ACTOR_H
