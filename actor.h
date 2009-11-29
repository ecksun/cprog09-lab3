#ifndef DA_GAME_ACTOR_H
#define DA_GAME_ACTOR_H

#include <string>
#include <vector>

namespace da_game {
    
    class Environment;
    class Object;

    class Actor {
        public:
            Actor();
            virtual void run() = 0;
            virtual std::string get_type() const = 0;
            virtual std::string get_name() const = 0;
            virtual void go(std::string) = 0;
            virtual void fight(Actor &) = 0;
            virtual void pick_up(Object &) = 0;
            virtual void drop(Object &) = 0;
            virtual void talk_to(Actor &) = 0;
        protected:
            int hp;
            int strength;
            Environment * current_room;
            std::vector<Object *> * objects;
    };
}
#endif // DA_GAME_ACTOR_H
