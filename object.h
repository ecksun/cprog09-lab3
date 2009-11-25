#ifndef DA_GAME_OBJECT_H
#define DA_GAME_OBJECT_H

namespace da_game {
    class Object {
        int weight;
        public:
        virtual int weight() = 0;
        virtual int volume() = 0;
        virtual int price() = 0;
    };
}

#endif // DA_GAME_OBJECT_H
