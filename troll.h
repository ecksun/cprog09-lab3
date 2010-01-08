#ifndef DA_GAME_TROLL_H
#define DA_GAME_TROLL_H

#include "actor.h"
#include "food.h"

namespace da_game {
    
    class Troll : public Actor {
        public:
            Troll(Environment *, int, int);
            void eat(Actor &);
            void eat(Food &);
            virtual void run();
            virtual std::string get_type() const;
            virtual std::string get_name() const;
            virtual bool pick_up(Object *);
            virtual bool drop(Object *);
            virtual void talk_to(Actor &);
    };
}
#endif // DA_GAME_TROLL_H
