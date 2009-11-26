#include "food.h"

namespace da_game {
    Food::Food(int food) {
        foodLeft = food;
    }
    int Food::health_increase() {
        int tmp = foodLeft;
        foodLeft = 0;
        return tmp;
    }
}
