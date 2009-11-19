#ifndef ACTOR_HEADER
#define ACTOR_HEADER
#include <string>
#include "Object.h"
namespace da_game {
    class actor {
        int hp;
        public:
        void run();
        virtual std::string type() = 0;
        virtual std::string name() = 0;
        virtual void go(std::string) = 0;
        virtual void fight(actor &) = 0;
        virtual void pick_up(Object &) = 0;
        virtual void drop(Object &) = 0;
        virtual void talk_to(actor &) = 0;
    };
}
#endif
