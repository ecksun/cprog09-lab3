#include "actor.h"
#include "Food.h"
namespace da_game {
    class human : public actor {
        bool hasHeart;
        int maxHealth;
        public:
        void eat(Food &f);
    };
}
