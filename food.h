#ifndef FOOD_HEADER
#define FOOD_HEADER

#include "object.h"

namespace da_game {

    class Food : public Object  {

        public:
            Food(int);
            virtual int health_increase();
            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;
            virtual void save(std::ofstream &);

        protected:
            int food_left;
    };

}

#endif
