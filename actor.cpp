#include "actor.h"
namespace da_game {
    int Actor::instances;
    Actor::Actor() : id(instances) {
        instances++;
    }
}
