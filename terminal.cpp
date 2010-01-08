#include "terminal.h"
#include <iostream>

namespace da_game {

    std::map<std::string, int (*)(std::string)> Terminal::functions;

    int Terminal::run() {
        std::string row;
        std::cout << "> ";

        getline(std::cin, row);
        if (std::cin.eof()) {
            return 1;
        }

        // std::cin >> row;
        std::string command = row.substr(0, row.find_first_of(' '));
        std::string arguments = row.substr(row.find_first_of(' ')+1);
        // std::cout << "Recived command: '" << command << "' with arguments: '" << arguments << "'" << std::endl;

        std::map<std::string, int (*)(std::string)>::iterator it = functions.find(command);

        if (it != functions.end()) {
            return it->second(arguments);
        }
        else {
            std::cout << "No such command" << std::endl;
        }
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

    const std::map<std::string, int (*)(std::string)> Terminal::get_functions() {
        return functions;
    }

    void Terminal::print(std::string s) {
        unsigned int minSize = 80;
        s.insert(0, "| ");
        unsigned int row = 0;
        for (unsigned int i = 0; i <= s.length(); i++, row++) {
            if (row == minSize) {
                s.insert(i, " |\n");
                s.insert(i+3, "| ");
                row = 0;
                i = i+3;
            }
            else if (s[i] == '\n') {
                s.insert(i, minSize-row, ' ');
                s.insert(i   + (minSize-row), " |");
                s.insert(i+3 + (minSize-row), "| ");
                i = i + 3 + (minSize-row);
                row = 0;
            }
        }

        s.append(minSize - row +2, ' ');
        s.append("|");

        std::string line = "";
        line.append(minSize+2, '-'); // compensate for newline

        std::cout << line << std::endl;
        std::cout << s << std::endl;
        std::cout << line << std::endl;
    }
}
