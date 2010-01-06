#ifndef DA_GAME_PLAYER_H
#define DA_GAME_PLAYER_H

#include "actor.h"
#include "environment.h"
#include <string>

namespace da_game {
    class Player: public Actor {
        friend class GameCommands;
        public:
            Player(Environment *);
            ~Player();
            virtual void run();
            virtual std::string get_type() const;
            virtual std::string get_name() const;
            virtual void go(std::string);
            virtual void fight(Actor &);
            virtual void talk_to(Actor &);
            virtual Environment * getRoom() const;
    };
}

#endif // DA_GAME_PLAYER_H
