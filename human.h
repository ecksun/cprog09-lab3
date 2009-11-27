#ifndef DA_GAME_HUMAN_H
#define DA_GAME_HUMAN_H

#include "actor.h"
#include "food.h"

namespace da_game {

    class Food;

    class Human : public Actor {

        protected:
            bool has_heart;
            int max_health;
            std::string name;

        public:
            Human(bool, int);

            virtual void run();
            virtual std::string get_name() const;
            virtual void go(std::string);

            void eat(Food &);
    };
}
#endif // DA_GAME_HUMAN_H
