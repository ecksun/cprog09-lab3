#ifndef DA_GAME_OBJECT_H
#define DA_GAME_OBJECT_H
#include <string>

namespace da_game {
    class Object {
        public:
        virtual int weight() = 0;
        virtual int volume() = 0;
        virtual int price() = 0;
        virtual std::string type() = 0;
    };
}
#endif // DA_GAME_OBJECT_H
