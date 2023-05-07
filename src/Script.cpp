#include "Script.h"

#include <iostream>

#include "Game.h"

extern Game game;

void Script::Read() {
    //std::cout << "script is being read\n";
    //std::cout << command.size() << " " << argument.size() << "\n";
    if (command.size() == 0 || command.size() != argument.size()) {//not a valid command
        return;
    }
    //the command vector is valid
    for (int a = 0; a < command.size(); a++) {
        //std::cout << "command:\n";
        if (command[a] == "shutdown") {
            game.Shutdown();
        }
        else if (command[a] == "music") {

        }
        else if (command[a] == "spawn") {

        }
        else if (command[a] == "make_button") {

        }
        else if (command[a] == "script" && argument[a].size() > 0) {
            game.ScriptReader(argument[a][0].name);
        }
        else if (command[a] == "print" && argument[a].size() > 0) {
            if (argument[a][0].IsValue()) {
                std::cout << argument[a][0].value << "\n";
            }
            else {
                std::cout << argument[a][0].content << "\n";
            }
        }
    }
}