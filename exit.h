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
            explicit Exit(Environment *, bool has_lock=false, std::string code="", bool locked=false, std::string desc="");
            Environment * get_outfall() const;
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
            bool has_lock;
            std::string key_code;
            bool locked;
    };

}
#endif /* DA_GAME_EXIT_H */
