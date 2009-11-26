#ifndef DA_GAME_OBJECT_H
#define DA_GAME_OBJECT_H

#include <string>

namespace da_game {
    class Object {
        public:
        virtual int weight() const = 0;
        virtual int volume() const = 0;
        virtual int price() const = 0;
        virtual std::string type() const = 0;
    };
}
#endif // DA_GAME_OBJECT_H
