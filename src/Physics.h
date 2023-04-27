#pragma once

struct Physics {
    const int entityId;
    bool isImoveable;
    float weight; // How fast it moves

    void Update();

    Physics(int id, bool isMoveable = true, int weight = 1.0f);
};
