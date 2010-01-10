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

        public:
            Human(bool, int);

            virtual void run();
            virtual std::string get_type() const;
            virtual std::string serialize() const;

            void eat(Food &);
    };
}
#endif // DA_GAME_HUMAN_H
