#ifndef DA_GAME_KEY_H
#define DA_GAME_KEY_H

#include "object.h"

#include <string>

namespace da_game {

    /**
     * A key may be used for locking and unlocking doors. It utilises
     * a special keycode which has to agree with the corresponding 
     * code for the door.
     */
    class Key : public Object {
        public:
            Key(std::string);
            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;
            virtual bool operator==(Key &) const;

            std::string get_key_code() const;

            virtual void save(std::ofstream &);

        private:
            std::string key_code;

    };

}

#endif /* DA_GAME_KEY_H */
