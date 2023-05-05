#include "Scene.h"

std::string Scene::AddEntity(std::string name, float scale, float start_x, float start_y, float start_z) {
    if (name.size() > 0) {
        entity.push_back(new Entity);
        std::string ID = entity.back()->Load(name, scale, start_x, start_y, start_z);
        return ID;
    }
    return "";
}

void Scene::UpdateAllEntities() {
    for (int a = 0; a < entity.size(); a++) {
        entity[a]->Update();
    }
}

void Scene::SetActive() {
    //?
}