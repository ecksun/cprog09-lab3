#ifndef DA_GAME_INSIDE_H
#define DA_GAME_INSIDE_H

#include "environment.h"

namespace da_game {
    class Inside : public Environment  {
        public:
            Inside();
            Inside(Exit *, Exit *, Exit *, Exit *); 
    };
}

#endif // DA_GAME_ENVIRONTMENT_H
