#ifndef DA_GAME_CONTAINER_H
#define DA_GAME_CONTAINER_H

#include "object.h"

namespace da_game {
    class Container : public Object  {
        public:
            virtual int hold_weight() = 0;
            virtual int hold_volume() = 0;
            virtual int add(Object &) = 0;
            virtual int remove(Object &) = 0;
    };
}
#endif // DA_GAME_CONTAINER_H
