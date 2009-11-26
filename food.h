#ifndef FOOD_HEADER
#define FOOD_HEADER
#include "object.h"
namespace da_game {
    class Food : public Object  {
        public:
            Food(int);
            int health_increase();
        private:
            int foodLeft;
    };
}

#endif
