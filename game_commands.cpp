#include <iostream>
#include <string>

#include "game_commands.h"

namespace da_game {
    Player * GameCommands::player;
    GameCommands::GameCommands(Player * pl) {
        GameCommands::player = pl;
        Terminal::add_function(std::string("exit"), &GameCommands::exit);
        Terminal::add_function(std::string("quit"), &GameCommands::exit);
        Terminal::add_function(std::string("go"), &GameCommands::go);
        Terminal::add_function(std::string("fight"), &GameCommands::fight);
        Terminal::add_function(std::string("pick_up"), &GameCommands::pick_up);
        Terminal::add_function(std::string("drop"), &GameCommands::drop);
        Terminal::add_function(std::string("talk_to"), &GameCommands::talk_to);
        Terminal::add_function(std::string("help"), &GameCommands::help);
    }
    int GameCommands::exit(std::string) {
        return 1;
    }

    int GameCommands::go(std::string direction) {
        player->go(direction);
        return 0;
    }

    /*
     * TODO: need a way to get a opponent from a string
     */
    int GameCommands::fight(std::string oponent) {
        return 0;
    }
    /*
     * TODO: need a way to get a object from a string
     */
    int GameCommands::pick_up(std::string object) {
        return 0;
    }
    /*
     * TODO: need a way to get a object from a string
     */
    int GameCommands::drop(std::string object) {
        return 0;
    }
    /*
     * TODO: need a way to get a actor from a string
     */
    int GameCommands::talk_to(std::string actor) {
        return 0;
    }
    /*
     * TODO: need a way to get a actor from a string
     */
    int GameCommands::help(std::string string) {
        const std::map<std::string, int (*)(std::string)> & functions = Terminal::get_functions();
        std::map<std::string, int (*)(std::string)>::const_iterator it;

        for (it = functions.begin(); it != functions.end(); it++) {
            std::cout << it->first << std::endl;
        }

        return 0;
    }

}
