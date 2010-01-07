#ifndef DA_GAME_ROOM_H
#define DA_GAME_ROOM_H

#include "inside.h"

namespace da_game {
    class Room : public Inside {
        public:
            Room();
            Room(Exit *, Exit *, Exit *, Exit *);
            virtual std::string description() const;
        private:
    };
}

#endif // DA_GAME_ROOM_H

