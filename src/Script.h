#pragma once

#include <iostream>

struct Script {
    const int scriptId; // This is not entityId
    std::string name;
    void *code;

    void Update();

    Script(std::string filename);
};
