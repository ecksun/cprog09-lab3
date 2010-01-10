#include <iostream>
#include <sstream>
#include "object.h"
#include "food.h"
#include "bag.h"
#include "light_saber.h"
#include "key.h"


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
        if (type == "Orch bag") {
            return new Bag();
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
        //  light saber:5kg,5liter,1000kr,1000strength,0.95ratio
        else if (type == " light saber") {
            std::string ratio = line.substr(line.find_last_of(',')+1);
            ratio = ratio.substr(0,4);
            std::string strength = line;
            strength = strength.substr(strength.find_first_of(',')+1);
            strength = strength.substr(strength.find_first_of(',')+1);
            strength = strength.substr(strength.find_first_of(',')+1);
            strength = strength.substr(0,strength.find_first_of('s'));
            int str;
            float rat;
            std::istringstream stream(strength);
            stream >> str;
            std::istringstream iss(ratio);
            stream >> rat;
            return new LightSaber(str, rat);
        }
        else if (type.substr(0,3) == "Key") {
            std::string name = line.substr(line.find_first_of('(')+1);
            name = name.substr(0,name.find_first_of(')'));
            return new Key(name);
        }
        return NULL;
    }
}
