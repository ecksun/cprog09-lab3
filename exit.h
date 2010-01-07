#ifndef DA_GAME_EXIT_H
#define DA_GAME_EXIT_H

#include <string>

#include "key.h"

namespace da_game {

    class Environment;

    /**
     * Exits are used in environments to allow actors travelling between
     * different environments.
     */
    class Exit {
        public:
            Exit();
            bool is_locked();
            void set_outfall(Environment *);
            void set_description(std::string);
            void set_key_code(std::string);
            void set_locked(bool);
            bool lock(Key *);
            bool unlock(Key *);
            bool toggle_lock(Key *);
        private:
            Environment * outfall;
            std::string description;
            std::string key_code;
            bool locked;
            bool lockable;
    };

}
#endif /* DA_GAME_EXIT_H */
