#ifndef DA_GAME_ENVIRONMENT_H
#define DA_GAME_ENVIRONMENT_H

#include <string>
#include <vector>

#include "actor.h"
#include "object.h"

namespace da_game {

    class Actor;
    class Object;

    class Environment {
        /*
         * returnera beskrivning av vad miljön innehåller, vilka
         * föåman kan ta och vilka aktö som befinner sig pålatsen.
         */
        virtual std::string description() const = 0;
        /*
         * returnera vilka utgåar som finns
         */
        virtual std::vector<std::string> directions() const = 0;
        /*
         * returnera granne (t.ex. referens till objekt) i gi-
         * ven riktning
         */
        virtual Environment & neighbor(std::string) const = 0;
        /*
         * enter(Character) - actor enters the place
         */
        virtual void enter(Actor &) = 0;
        /*
         * leave(Character) - actor leaves this environment
         */
        virtual void leave(Actor &) = 0;
        /*
         * pick_up(Object) - nån tar upp ett föåsom finns pålatsen
         */
        virtual bool pick_up(Object &) = 0;
        /*
         * drop(Object) - nån läer ner ett föåpålatsen
         */
        virtual void drop(Object &) = 0;
    };
}
#endif // DA_GAME_ENVIRONTMENT_H