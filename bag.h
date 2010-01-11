#ifndef DA_GAME_BAG_H
#define DA_GAME_BAG_H

#include <string>

#include "container.h"

namespace da_game {

    class Bag : public Container {

        public:
            Bag();
            ~Bag();

            virtual int weight() const;
            virtual int volume() const;
            virtual int price() const;
            virtual std::string type() const;

            virtual int get_hold_weight() const;
            virtual int get_hold_volume() const;
            virtual bool add(Object &);
            virtual bool remove(Object &);
            virtual void save(std::fstream & save);

    };


}

#endif // DA_GAME_BAG_H
