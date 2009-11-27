#include "terminal.h"
#include <iostream>

namespace da_game {

    std::map<std::string, int (*)(std::string)> Terminal::functions;

    int Terminal::run() {
        std::string row;
        std::cout << "> ";

        getline(std::cin, row);

        // std::cin >> row;
        std::string command = row.substr(0, row.find_first_of(' '));
        std::string arguments = row.substr(row.find_first_of(' ')+1);
        std::cout << "Recived command: '" << command << "' with arguments: '" << arguments << "'" << std::endl;

        std::map<std::string, int (*)(std::string)>::iterator it = functions.find(command);

        if (it != functions.end()) {
            return it->second(arguments);
        }
        else {
            std::cout << "No such command" << std::endl;
        }
        std::cout << "Done executing command" << std::endl;
        return 0;
    }

    /*
     * Add a static member function to the list of avalible arguments.
     * NOTE: the function HAVE to be a static member function or an ordinary function (outside of a class)
     */
    bool Terminal::add_function(
            std::string string, 
            int (*function)(std::string)) {

        std::pair<std::map<std::string, int (*)(std::string)>::iterator, bool> ret;

        ret = Terminal::functions.insert(
                std::pair<std::string, int (*)(std::string)>(string, function));
        return ret.second;
    }
}
