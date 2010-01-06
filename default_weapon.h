#ifndef DA_GAME_DEFAULTWEAPON_HEADER
#define DA_GAME_DEFAULTWEAPON_HEADER


#include "weapon.h"
namespace da_game {
    class DefaultWeapon : public Weapon {
        public:
            DefaultWeapon();
            int weight() const;
            int volume() const;
            int price() const;
    };
}

#endif // DA_GAME_DEFAULTWEAPON_HEADER
