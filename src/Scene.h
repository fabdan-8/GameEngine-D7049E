#pragma once

#include "Entity.h"
#include <vector>

class Scene {
public:
	void AddEntity(Entity* ent);
	void UpdateAllEntities();
	void SetActive();
private:
	std::vector<Entity*> entity;
	Ogre::SceneNode* node = nullptr;
};

