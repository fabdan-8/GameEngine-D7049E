#include "Script.h"

#include <iostream>

#include "Game.h"
#include "Scene.h"

//#include <SDL/SDL.h>
//#include <SDL/SDL_mixer.h>

extern Game game;
extern Scene scene;

extern std::map<std::string, Mix_Music*> musichandler;

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
            std::string& music_name = argument[a][0].content;
            //std::cout << "attempting to play '" << music_name << "'\n";
            if (musichandler.find(music_name) != musichandler.end()) {
                //std::cout << "playing '" << music_name << "'\n";
                Mix_PlayMusic(musichandler[music_name], 0);
            }
            else {
                //std::cout << "loading '" << music_name << "'...\n";
                Mix_Music* music = Mix_LoadMUS(music_name.c_str());
                if (music) {
                    //std::cout << "playing '" << music_name << "'\n";
                    musichandler[music_name] = music;
                    Mix_PlayMusic(music, 0);
                }
                else {
                    //std::cout << "failed to load '" << music_name << "'\n";
                }
            }
        }
        else if (command[a] == "spawn") {
            std::string name = GetContent("name", a);
            float scale = GetValue("scale", a, 1.0f);
            float start_x = GetValue("x", a);
            float start_y = GetValue("y", a);
            float start_z = GetValue("z", a);
            //also the update and interaction scripts

            scene.AddEntity(name, scale, start_x, start_y, start_z);
        }
        else if (command[a] == "make_button") {

        }
        else if (command[a] == "move") {

        }
        else if (command[a] == "spin") {

        }
        else if (command[a] == "script" && argument[a].size() > 0) {
            game.ScriptReader(argument[a][0].content);
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

float Script::GetValue(std::string name, int a, float default_value) {
    for (int b = 0; b < argument[a].size(); b++) {
        if (argument[a][b].name == name) {
            if (argument[a][b].IsValue()) {
                return argument[a][b].value;
            }
        }
    }
    return default_value;
}

std::string Script::GetContent(std::string name, int a, std::string default_content) {
    for (int b = 0; b < argument[a].size(); b++) {
        if (argument[a][b].name == name) {
            if (argument[a][b].IsString()) {
                return argument[a][b].content;
            }
        }
    }
    return default_content;
}
