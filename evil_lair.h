#ifndef DA_GAME_EVIL_LAIR_H
#define DA_GAME_EVIL_LAIR_H

#include "inside.h"

namespace da_game {
    class EvilLair : public Inside {
        public:
            EvilLair();

            virtual std::string description() const;
        private:
    };
}

#endif // DA_GAME_EVIL_LAIR_H

