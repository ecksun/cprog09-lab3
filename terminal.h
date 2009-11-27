#ifndef DA_GAME_TERMINAL_H
#define DA_GAME_TERMINAL_H
#include <string>
#include <map>
namespace da_game {
    class Terminal {
        public:
            void run();
            static bool add_function(std::string, void (*)(std::string, std::string));
        private:
            static std::map<std::string, void (*)(std::string, std::string)> functions;
    };
}

#endif // DA_GAME_TERMINAL_H

