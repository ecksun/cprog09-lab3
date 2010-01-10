#include <iostream>
#include <sstream>
#include "object.h"
#include "food.h"
namespace da_game {

    int Object::instances;

    Object::Object() : id(instances) {
        instances++;
    }

    bool Object::operator==(Object & obj) const {
        return obj.id == this->id;
    }
    /*
     * OBJ1:Orch bag::17kg,50liter,100kr
     * OBJ10:Orch bag::17kg,50liter,100kr
     * OBJ12:Orch bag::17kg,50liter,100kr
     * OBJ14:Orch bag:OBJ15:17kg,50liter,100kr
     * OBJ2:Orch bag::17kg,50liter,100kr
     * OBJ3:Orch bag::17kg,50liter,100kr
     * OBJ4:Orch bag::17kg,50liter,100kr
     * OBJ7:Key (evil):1kg,1liter,50kr
     * OBJ5:Mat:5kg,16liter,94kr,47food
     * OBJ8: light saber:5kg,5liter,1000kr
     * OBJ6:Key (e1):1kg,1liter,50kr
     * OBJ7:Key (evil):1kg,1liter,50kr
     */
    Object * Object::load(std::string line) {
        line = line.substr(line.find_first_of(':')+1);
        std::string type = line.substr(0,line.find_first_of(':'));
        std::cout << line << std::endl;
        if (type == "Orch bag") {
            // Ladda in object
        }
        else if (type == "Mat") {
            std::string tmp = line.substr(line.find_last_of(',')+1);
            tmp = tmp.substr(0,tmp.length()-4);
            std::istringstream stream(tmp);
            int food;
            stream >> food;
            return new Food(food);
        }
        else if (type == " light saber") {

        }
        // else if its a key
        return NULL;
    }
}
