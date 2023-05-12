#pragma once

#include "Entity.h"
#include "Physics.h"
#include <vector>
// #include <map>

class Scene {
public:
	std::string AddEntity(std::string name, float scale = 1.0f, float start_x = 0.0f, float start_y = 0.0f, float start_z = 0.0f);
	std::string AddImage(std::string filename, float x, float y, float z, float w, float h, float rot = 0.0f);
	void RemoveEntity(Entity* ent);
	void RemoveEntityByName(std::string name);
	void Update();

	Entity* GetCenteredEntity();
	Entity* GetHoveredEntity();

	void Cleanup();
	//void SetActive();
	Physics physics;
private:
	void UpdateAllEntities();
	//std::vector<Entity*> entity;
	//std::thread entity_thread;
	//bool entity_thread_busy = false;
	std::map<std::string, Entity*> entity_map;
	Ogre::SceneNode *node = nullptr; //?
};
