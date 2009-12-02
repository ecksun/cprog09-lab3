#ifndef DA_GAME_ENVIRONMENT_H
#define DA_GAME_ENVIRONMENT_H

#include <string>
#include <vector>
#include <map>

#include "actor.h"
#include "object.h"

namespace da_game {

    class Actor;
    class Object;

    class Environment {
        friend class GameCommands;
        public:
            /*
             * returnera beskrivning av vad miljön innehåller, vilka
             * föremål man kan ta och vilka aktörer som befinner sig på platsen.
             * TODO: fixa så det här printas vid operator<<
             */
            virtual std::string description() const = 0;
            /*
             * returnera vilka utgångar som finns
             */
            virtual std::vector<std::string> directions() const = 0;
            /*
             * returnera granne (t.ex. referens till objekt) i gi-
             * ven riktning
             *
             * NOTE: Jag ändrade från referens till pekare för att kunna
             * returnera 0 om det inte finns en granne åt det hållet
             */
            virtual Environment * neighbor(std::string) const = 0;
            /*
             * enter(Character) - actor enters the place
             */
            virtual void enter(Actor &) = 0;
            /*
             * leave(Character) - actor leaves this environment
             */
            virtual void leave(Actor &) = 0;
            /*
             * pick_up(Object) - nån tar upp ett föremål som  finns pålatsen
             */
            virtual bool pick_up(Object *);
            /*
             * drop(Object) - någon lägger ner ett föremål på platsen
             */
            virtual void drop(Object *);

            virtual bool add_neighbor(std::string, Environment *) = 0;
        protected:
            std::vector<Object *> * objects;
            std::vector<Actor *> * actors;
            std::map<std::string, Environment *> neighbors;
    };
}
#endif // DA_GAME_ENVIRONTMENT_H
