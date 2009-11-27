#ifndef DA_GAME_TERMINAL_H
#define DA_GAME_TERMINAL_H
#include <string>
#include <map>
namespace da_game {
    class Terminal {
        public:
            int run();
            static bool add_function(std::string, int (*)(std::string));
            static const std::map<std::string, int (*)(std::string)> get_functions();
        private:
            static std::map<std::string, int (*)(std::string)> functions;
    };
}

#endif // DA_GAME_TERMINAL_H

