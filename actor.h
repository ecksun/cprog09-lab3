#ifndef DA_GAME_ACTOR_H
#define DA_GAME_ACTOR_H

#include <string>
#include <vector>

#include "object.h"
#include "environment.h"
#include "weapon.h"
#include "container.h"

namespace da_game {

    class Environment;
    
    class Actor {
        friend class GameCommands;
        friend class Game;
        public:
            const int id;
            Actor();
            ~Actor();

            static Actor * load(const std::string, const std::map<std::string, Environment *> &, const std::map<std::string, Object *> &);

            virtual void run() = 0;
            virtual std::string get_type() const = 0;
            virtual std::string get_name() const = 0;
            virtual void go(std::string);
            virtual bool pick_up(Object *);
            virtual bool drop(Object *);
            virtual void talk_to(Actor &) = 0;
            virtual Weapon * weapon();
            virtual void fight(Actor &);
            void save(std::fstream &);
            virtual std::string serialize() const = 0;
        protected:
            static int instances;

            int hp;
            int strength;
            Weapon * current_weapon;
            Environment * current_room;
            Container * container;
        private:
            static int str2int(std::string);
    };
}
#endif // DA_GAME_ACTOR_H
