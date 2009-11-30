#include "object.h"
namespace da_game {
    int Object::instances;
    Object::Object() : id(instances) {
        instances++;
    }

    bool Object::operator==(Object & obj) const {
        return obj.id == this->id;
    }
}
