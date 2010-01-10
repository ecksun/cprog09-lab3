#ifndef DA_GAME_ENVIRONMENT_H
#define DA_GAME_ENVIRONMENT_H

#include <string>
#include <vector>
#include <map>

#include "actor.h"
#include "exit.h"
#include "object.h"

namespace da_game {

    class Actor;
    class Object;

    class Environment {

        friend class GameCommands;

        public:
            Environment();

            ~Environment();

            const int id;

            /*
             * Any implementation of this function should return a
             * description of what the environment contains, what 
             * objects are available and what actors are in the
             * environment. 
             *
             * TODO: fixa så det här printas vid operator<<
             */
            virtual std::string description() const;

            virtual bool add_exit(std::string, Exit *);

            virtual Exit * get_exit(std::string) const;

            virtual std::vector<std::string> get_exit_names() const;

            virtual void enter(Actor &);

            virtual void leave(Actor &);

            virtual bool pick_up(Object *);

            virtual void drop(Object *);

            virtual std::vector<Object *> get_objects();

            virtual std::vector<Actor *> get_actors();

            virtual void save(std::ofstream &);
            static Environment * load(std::string);
        protected:
            static int instances;
            std::vector<Object *> * objects;
            std::vector<Actor *> * actors;
            std::map<std::string, Environment *> neighbors;
            std::map<std::string, Exit *> exits;
    };
}
#endif // DA_GAME_ENVIRONTMENT_H
