#ifndef DA_GAME_LIGHTSABER_HEADER
#define DA_GAME_LIGHTSABER_HEADER

#include "weapon.h"

namespace da_game {

    class LightSaber : public Weapon  {

        public:
            LightSaber(unsigned int, float); // Weapon(attack_strength, hit_ratio)
            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;
    };

}

#endif
