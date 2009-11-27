#ifndef DA_GAME_WIZARD_H
#define DA_GAME_WIZARD_H

#include "human.h"

namespace da_game {

    class Wizard : public Human {

        private:
            int magic;
            int max_magic;

        public: 
            Wizard(bool, int, int);

    };

}

#endif // DA_GAME_WIZARD_H
