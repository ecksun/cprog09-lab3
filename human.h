#ifndef DA_GAME_HUMAN_H
#define DA_GAME_HUMAN_H

namespace da_game {
    class Human : public Actor {
        bool has_heart;
        int max_health;
        public:
        void eat(Food &);
    };
}

#endif // DA_GAME_HUMAN_H
