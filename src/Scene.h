#pragma once

#include "Entity.h"
#include <vector>
// #include <map>

class Scene {
  public:
    std::string AddEntity(std::string name, float scale = 1.0f, float start_x = 0.0f, float start_y = 0.0f, float start_z = 0.0f);
    void UpdateAllEntities();
    void SetActive();

  private:
    std::vector<Entity *> entity;
    Ogre::SceneNode *node = nullptr; //?
};
