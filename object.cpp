#include "object.h"
namespace da_game {
    int Object::instances;
    Object::Object() : id(instances) {
        instances++;
    }
}
