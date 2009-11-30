#ifndef DA_GAME_ROOM_H
#define DA_GAME_ROOM_H

#include "inside.h"

namespace da_game {
    class Room : public Inside {
        public:
            Room(Environment *, Environment *, Environment *, Environment *);
            virtual std::string description() const;
            virtual std::vector<std::string> directions() const;
            virtual Environment * neighbor(std::string) const;
            virtual void enter(Actor &);
            virtual void leave(Actor &);
            virtual bool pick_up(Object &);
            virtual void drop(Object &);
            virtual bool add_neighbor(std::string, Environment *);
        private:
    };
}

#endif // DA_GAME_ROOM_H

