#include "Scene.h"
#include <mutex>
#include <thread>

#include "Ogre.h"

std::string Scene::AddEntity(std::string name, float scale, float start_x, float start_y, float start_z) {
    if (name.size() > 0) {
        //entity.push_back(new Entity);
        Entity* ent = new Entity;
        //entity_thread_busy = true;
        //entity_thread = std::thread(&Entity::Load, ent, name, scale, start_x, start_y, start_z);
        std::string ID = ent->Load(name, scale, start_x, start_y, start_z);
        if (ID.size() > 0) {
            entity_map[ID] = ent;//name should always be unique, otherwise check through map first
        }
        return ID;
    }
    return "";
}

void Scene::RemoveEntity(Entity* ent) {
    if (ent) {
        for (auto const& entity_entry : entity_map) {
            if (entity_entry.second == ent) {
                delete entity_entry.second;
                entity_map.erase(entity_entry.first);
            }
        }
    }
}

void Scene::RemoveEntityByName(std::string name) {

}

void Scene::Update() {
    //if (ogre_resource_mut.try_lock()) {
    //    entity_thread.join();
    //    ogre_resource_mut.unlock();
    //}
    UpdateAllEntities();
    //for (auto const& entity_entry : entity_map) {
    //    if (entity_entry.second) {
    //        entity_entry.second->node->translate(Ogre::Vector3(0.0f, 0.1f, 0.0f), Ogre::Node::TS_LOCAL);
    //    }
    //}
}

void Scene::Cleanup() {
    for (auto const& entity_entry : entity_map) {
        if (entity_entry.second) {
            delete entity_entry.second;
        }
    }
    entity_map.clear();
}

void Scene::UpdateAllEntities() {
    //for (int a = 0; a < entity.size(); a++) {
    //    entity[a]->Update();
    //}
    for (auto const& entity_entry : entity_map) {
        if (entity_entry.second) {
            entity_entry.second->Update();
        }
    }
}

//void Scene::SetActive() {
//    //?
//}