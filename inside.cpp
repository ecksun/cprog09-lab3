#include "inside.h"

namespace da_game {

    /**
     * Constructs a new empty inside environment with no exits.
     */
    Inside::Inside() {
    }

    /**
     * Constructs a new inside environment.
     *
     * @param east The east exit
     * @param west The west exit
     * @param north The north exit
     * @param south The south exit
     */
    Inside::Inside(Exit * east, Exit * west, Exit * north, Exit * south) {
        if (east != 0) {
            std::pair<std::string, Exit *> e("east", east);
            exits.insert(e);
        }
        if (west != 0) {
            std::pair<std::string, Exit *> w("west", west);
            exits.insert(w);
        }
        if (north != 0) {
            std::pair<std::string, Exit *> n("north", north);
            exits.insert(n);
        }
        if (south != 0) {
            std::pair<std::string, Exit *> s("south", south);
            exits.insert(s);
        }
    }

}
