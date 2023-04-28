#pragma once

#include <iostream>

struct Sound {
    const int entityId;
    std::string name;
    //<type> data;

    void playSound();

    Sound(std::string filename);
};
