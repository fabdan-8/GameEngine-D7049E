#include "Script.h"

#include <iostream>

#include "Game.h"
#include "Scene.h"

//#include <SDL/SDL.h>
//#include <SDL/SDL_mixer.h>

extern Game game;
extern Scene scene;

extern std::string soundsfolder;

extern std::map<std::string, Script*> scripthandler;
extern std::map<std::string, Mix_Music*> musichandler;
extern std::map<std::string, Mix_Chunk*> soundhandler;
extern std::map<std::string, Variable*> variablehandler;

void Script::Read(void* target) {
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
            std::string music_name = soundsfolder + argument[a][0].content;
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
        else if (command[a] == "sound") {
            std::string sound_name = soundsfolder + argument[a][0].content;
            //std::cout << "attempting to play '" << music_name << "'\n";
            if (musichandler.find(sound_name) != musichandler.end()) {
                //std::cout << "playing '" << music_name << "'\n";
                Mix_PlayChannel(0, soundhandler[sound_name], 0);
            }
            else {
                //std::cout << "loading '" << music_name << "'...\n";
                Mix_Chunk* sound = Mix_LoadWAV(sound_name.c_str());
                if (sound) {
                    //std::cout << "playing '" << music_name << "'\n";
                    soundhandler[sound_name] = sound;
                    Mix_PlayChannel(0, soundhandler[sound_name], 0);
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
            std::string update_script = GetContent("update_script", a);
            std::string interaction_script = GetContent("interaction_script", a);
            //std::cout << interaction_script;
            scene.AddEntity(name, scale, start_x, start_y, start_z, interaction_script, update_script);
        }
        else if (command[a] == "make_button") {

        }
        else if (command[a] == "move") {
            float set_x = GetValue("x", a);
            float set_y = GetValue("y", a);
            float set_z = GetValue("z", a);
            float speed = GetValue("speed", a);
            std::string script_name = GetContent("script", a);
            if (target) {
                Script* script = game.ScriptLoader(script_name);
                //script doesn't have to be valid
                ((Entity*)(target))->QueueMove(set_x, set_y, set_z, speed, script);
            }
        }
        else if (command[a] == "spin") {

        }
        else if (command[a] == "set_variable" && argument[a].size() > 0) {
            std::string var_name = argument[a][0].name;
            std::string op = GetContent("operation", a);
            if (op == "add") {
                if (variablehandler.find(var_name) != variablehandler.end()) {
                    Variable* var = variablehandler[var_name];
                    var->value += 1;
                    //std::cout << var->name << "=" << var->value;
                }
                else {
                    Variable* var = new Variable;
                    *var = argument[a][0];
                    variablehandler[var_name] = var;
                    var->value += 1;
                    //std::cout << var->name << "=" << var->value;
                }
            }
            else {
                if (variablehandler.find(var_name) != variablehandler.end()) {
                    Variable* var = variablehandler[var_name];
                    *var = argument[a][0];
                }
                else {
                    Variable* var = new Variable;
                    *var = argument[a][0];
                    variablehandler[var_name] = var;
                }
            }
        }
        else if (command[a] == "check_variable") {
            std::string var_name = argument[a][0].name;
            std::string check = GetContent("check", a);
            std::string check_true = GetContent("true", a);
            std::string check_false = GetContent("false", a);
            bool is_true = false;
            if (variablehandler.find(var_name) != variablehandler.end() && (check_true.size() > 0 || check_false.size() > 0)) {
                Variable* var = variablehandler[var_name];
                if (check == "equals") {
                    if (var->value == argument[a][0].value && var->content == argument[a][0].content) {
                        is_true = true;
                        //std::cout << "TRUE";
                    }
                    else {
                        is_true = false;
                        //std::cout << "FALSE";
                    }
                }
            }
            if (is_true && check_true.size() > 0) {
                if (check_true == "jump") {
                    a += 1;
                }
            }
            else if (!is_true && check_false.size() > 0) {
                if (check_false == "jump") {
                    a += 1;
                }
            }
        }
        else if (command[a] == "set_update" && argument[a].size() > 0) {
            std::string script_name = argument[a][0].content;
            if (target) {
                Script* script = game.ScriptLoader(script_name);
                ((Entity*)(target))->update_script = script;
            }
        }
        else if (command[a] == "set_interaction" && argument[a].size() > 0) {
            std::string script_name = argument[a][0].content;
            if (target) {
                Script* script = game.ScriptLoader(script_name);
                ((Entity*)(target))->interaction_script = script;
            }
        }
        else if (command[a] == "no_update") {
            if (target) {
                ((Entity*)(target))->update_script = nullptr;
            }
        }
        else if (command[a] == "no_interaction") {
            if (target) {
                ((Entity*)(target))->interaction_script = nullptr;
            }
        }
        else if (command[a] == "break") {
            a = command.size();
        }
        else if (command[a] == "jump" && argument[a].size() > 0) {
            std::string jump_string = argument[a][0].content;
            int jump_length = atoi(jump_string.c_str());
            if (jump_length > 0) {
                a += jump_length;
            }
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
