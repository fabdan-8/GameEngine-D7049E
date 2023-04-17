#include "Scene.h"

void Scene::AddEntity(Entity* ent) {
	if (ent) {
		entity.push_back(ent);
	}
}

void Scene::UpdateAllEntities() {
	for (int a = 0; a < entity.size(); a++) {
		entity[a]->Update();
	}
}

void Scene::SetActive() {

}