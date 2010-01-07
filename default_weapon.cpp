#include "default_weapon.h"

namespace da_game {
    DefaultWeapon::DefaultWeapon() : Weapon(1, 0.5) {}
    int DefaultWeapon::weight() const {
        return 0;
    }
    int DefaultWeapon::volume() const {
        return 0;
    }
    int DefaultWeapon::price() const {
        return 0;
    }
}
