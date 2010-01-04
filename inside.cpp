#include "inside.h"

namespace da_game {
    Inside::Inside(Environment * east, Environment * west, Environment * north, Environment * south) {
        if (east != 0) {
            std::pair<std::string, Environment *> e("east", east);
            neighbors.insert(e);
        }
        if (west != 0) {
            std::pair<std::string, Environment *> w("west", west);
            neighbors.insert(w);
        }
        if (north != 0) {
            std::pair<std::string, Environment *> n("north", north);
            neighbors.insert(n);
        }
        if (south != 0) {
            std::pair<std::string, Environment *> s("south", south);
            neighbors.insert(s);
        }
    }
}
