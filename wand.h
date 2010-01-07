#ifndef DA_GAME_WAND_HEADER
#define DA_GAME_WAND_HEADER

#include "weapon.h"

namespace da_game {

    class Wand : public Weapon  {

        public:
            Wand(unsigned int, float); // Weapon(attack_strength, hit_ratio)
            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;
            virtual int magic_cost() const;
    };

}

#endif
