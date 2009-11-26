#ifndef DA_GAME_CONTAINER_H
#define DA_GAME_CONTAINER_H

#include "object.h"

namespace da_game {
    class Container : public Object  {
        public:
            virtual int hold_weight() const = 0;
            virtual int hold_volume() const = 0;
            virtual int add(Object &) = 0;
            virtual int remove(Object &) = 0;
    };
}
#endif // DA_GAME_CONTAINER_H
