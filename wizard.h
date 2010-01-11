#ifndef DA_GAME_WIZARD_H
#define DA_GAME_WIZARD_H

#include "human.h"
#include "wand.h"
#include "default_weapon.h"

namespace da_game {

    class Wizard : public Human {

        private:
            int magic;
            int max_magic;
            Wand * wand;

        public: 
            ~Wizard();
            Wizard(Environment *, bool, int, int);
            Wizard(Environment *, int, int, bool, int, int, int);
            virtual Weapon * weapon();
            virtual std::string get_name() const;
            virtual std::string get_type() const;
            virtual void run();
            virtual void talk_to(Actor &);
            virtual std::string serialize() const;


    };

}

#endif // DA_GAME_WIZARD_H
