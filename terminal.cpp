#include "terminal.h"
#include <iostream>

namespace da_game {
    void Terminal::run() {
        std::string row;
        std::cout << "> ";
        std::cin >> row;
        std::cout << "Recived: " << row << std::endl;
    }

    bool Terminal::add_function(
            std::string string, 
            void (*function)(std::string, std::string)) {

        std::pair<std::map<std::string, void (*)(std::string, std::string)>::iterator, bool> ret;

        ret = functions.insert(
                std::pair<std::string, void (*)(std::string, std::string)>(string, function));
        return ret.second;
    }
}
