#pragma once
#include <iostream>

struct GameSceneManager {
    int currentScene;
    void changeScene(int scene);
    int loadScene(std::string name);
};
