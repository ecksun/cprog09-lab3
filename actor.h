#ifndef DA_GAME_ACTOR_H
#define DA_GAME_ACTOR_H

#include <string>

#include "object.h"
#include "environment.h"

namespace da_game {
    
    class Object;

    class Actor {
        public:
            virtual void run() = 0;
            virtual std::string type() const = 0;
            virtual std::string name() const = 0;
            virtual void go(std::string) = 0;
            virtual void fight(Actor &) = 0;
            virtual void pick_up(Object &) = 0;
            virtual void drop(Object &) = 0;
            virtual void talk_to(Actor &) = 0;
        protected:
            int hp;
            int strength;
            Environment * current_room;
    };
}
#endif // DA_GAME_ACTOR_H