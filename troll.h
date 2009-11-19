#ifndef TROLL_HEADER
#define TROLL_HEADER
#include "actor.h"
namespace da_game {
    class troll : public actor {
        public:
        void eat(actor &f);
    };
}
#endif
