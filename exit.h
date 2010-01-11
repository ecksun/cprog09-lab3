#ifndef DA_GAME_EXIT_H
#define DA_GAME_EXIT_H

#include <string>
#include <fstream>
#include <map>

#include "key.h"

namespace da_game {

    class Environment;

    /**
     * Exits are used in environments to allow actors travelling between
     * different environments.
     */
    class Exit {
        public:
            const int id;
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
            void save(std::fstream &, std::string);
            static Exit * load(std::string , const std::map<std::string, Environment *> &);
        private:
            Environment * outfall;
            std::string description;
            bool has_lock;
            std::string key_code;
            bool locked;
            static int instances;
    };

}
#endif /* DA_GAME_EXIT_H */
