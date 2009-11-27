#ifndef DA_GAME_TROLL_H
#define DA_GAME_TROLL_H

#include "actor.h"
#include "food.h"

namespace da_game {
    
    class Troll : public Actor {
        public:
            Troll(int, int);
            void eat(Actor &);
            void eat(Food &);
            virtual void run();
            virtual std::string get_type() const;
            virtual std::string get_name() const;
            virtual void go(std::string);
            virtual void fight(Actor &);
            virtual void pick_up(Object &);
            virtual void drop(Object &);
            virtual void talk_to(Actor &);
    };
}
#endif // DA_GAME_TROLL_H
