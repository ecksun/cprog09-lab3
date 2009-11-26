#ifndef DA_GAME_CONTAINER_H
#define DA_GAME_CONTAINER_H

#include <vector>

#include "object.h"

namespace da_game {
    class Container : public Object  {
        protected:
            int hold_weight_;
            int hold_volume_;
            std::vector<Object *> * objects;
            
        public:
            /*
             * Weight before container breaks
             */
            virtual int hold_weight() const = 0;
            /*
             * Volume capacity of container
             */
            virtual int hold_volume() const = 0;
            /*
             * Add an object to this container
             */
            virtual bool add(Object &) = 0;
            /*
             * Remove an object from this container
             */
            virtual bool remove(Object &) = 0;

    };
}
#endif // DA_GAME_CONTAINER_H
