#ifndef DA_GAME_ROOM_H
#define DA_GAME_ROOM_H

#include "inside.h"

namespace da_game {
    class Room : public Inside {
        public:
            virtual std::string description() const;
            virtual std::vector<std::string> directions() const;
            virtual Environment & neighbor(std::string) const;
        private:
    };
}

#endif // DA_GAME_ROOM_H

