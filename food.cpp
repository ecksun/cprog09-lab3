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

    int Food::weight() const {
        return food_left/10+1;
    }

    int Food::volume() const {
        return food_left/3+1;
    }

    int Food::price() const {
        return food_left*2;
    }

    std::string Food::type() const {
        return "Mat";
    }

    void Food::save(std::ofstream & save) {
        save << "OBJ" << id << ":" << type(); 
        save << ":" << weight() << "kg," << volume() << "liter," << price() << "kr," << food_left << "food" << std::endl;
    }

}
