#ifndef DA_GAME_ACTOR_H
#define DA_GAME_ACTOR_H
namespace da_game {
    class Actor;
}
#include <string>
#include "object.h"
#include "environment.h"

namespace da_game {
    class Actor {
        int hp;
        Environment * current_room;
        public:
        void run();
        virtual std::string type() = 0;
        virtual std::string name() = 0;
        virtual void go(std::string) = 0;
        virtual void fight(Actor &) = 0;
        virtual void pick_up(Object &) = 0;
        virtual void drop(Object &) = 0;
        virtual void talk_to(Actor &) = 0;
    };
}
#endif // DA_GAME_ACTOR_H
