#ifndef DA_GAME_EVIL_LAIR_H
#define DA_GAME_EVIL_LAIR_H

#include "inside.h"

namespace da_game {
    class EvilLair : public Inside {
        public:
            EvilLair(Environment *, Environment *, Environment *, Environment *);
            ~EvilLair();
            virtual std::string description() const;
            virtual std::vector<std::string> directions() const;
            virtual Environment * neighbor(std::string) const;
            virtual bool add_neighbor(std::string, Environment *);
        private:
    };
}

#endif // DA_GAME_EVIL_LAIR_H

