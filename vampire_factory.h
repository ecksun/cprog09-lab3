#ifndef DA_GAME_VAMPIRE_FACTORY_H
#define DA_GAME_VAMPIRE_FACTORY_H

#include "actor.h"

namespace da_game {

    class VampireFactory : public Actor {
        public:
            VampireFactory(Environment *, int);

            virtual void run();
            virtual std::string get_name() const;
            virtual std::string get_type() const;
            virtual void go(std::string);
            virtual void fight(Actor &);

            virtual void talk_to(Actor &);

        private:
            unsigned int frequency;
            unsigned int age;
    };
}
#endif // DA_GAME_VAMPIRE_FACTORY_H
