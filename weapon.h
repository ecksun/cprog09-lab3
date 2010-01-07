#ifndef DA_GAME_WEAPON_HEADER
#define DA_GAME_WEAPON_HEADER

#include "object.h"

namespace da_game {

    class Weapon : public Object  {

        public:
            Weapon(unsigned int, float); // Weapon(attack_strength, hit_ratio)
            virtual int weight() const = 0;
            virtual int volume() const = 0;
            virtual int price() const = 0;
            virtual std::string type() const;
            virtual int attack_strength() const;
            virtual float hit_ratio() const;


        protected:
            unsigned int strength;
            float ratio;
    };

}

#endif
