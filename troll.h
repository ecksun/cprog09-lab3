#ifndef DA_GAME_TROLL_H
#define DA_GAME_TROLL_H
#include "actor.h"

namespace da_game {
    class Troll : public Actor {
        public:
        void eat(Actor &);
        // void eat(Food &);
    };
}
#endif // DA_GAME_TROLL_H
