#include "food.h"

namespace da_game {

    Food::Food(int food) {
        food_left = food;
    }

    int Food::health_increase() {
        int tmp = food_left;
        food_left = 0;
        return tmp;
    }

}
