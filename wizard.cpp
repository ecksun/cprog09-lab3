#include <iostream>

#include "wizard.h"

namespace da_game {

    Wizard::Wizard(bool has_heart, int max_health, int max_magic)
        : Human(has_heart, max_health), magic(max_magic), max_magic(max_magic) {

        std::cout << "A magician has been born, with full magic power.. Kazaaam!" << std::endl;

    }


}
