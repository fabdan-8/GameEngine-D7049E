#include "Scene.h"
#include <mutex>
#include <thread>

#include "Game.h"
#include "OgreRay.h"

#include <iostream>

#include "Physics.h"

extern Game game;
//extern Physics physics;

std::string Scene::AddEntity(std::string name, float scale, float start_x, float start_y, float start_z, std::string interaction_script, std::string update_script) {
    if (name.size() > 0) {
        //entity.push_back(new Entity);
        Entity* ent = new Entity;
        //entity_thread_busy = true;
        //entity_thread = std::thread(&Entity::Load, ent, name, scale, start_x, start_y, start_z);
        std::string ID = ent->Load(name, scale, start_x, start_y, start_z);
        if (ID.size() > 0) {
            ent->update_script = game.ScriptLoader(update_script);
            ent->interaction_script = game.ScriptLoader(interaction_script);
            if (ent->interaction_script) {
                std::cout << "YES";
            }
            entity_map[ID] = ent;//name should always be unique, otherwise check through map first
            physics.createRigidBody(ent->getNode(), ent);
        }
        return ID;
    }
    return "";
}

std::string Scene::AddImage(std::string filename, float x, float y, float z, float w, float h, float rot) {
    if (filename.size() > 0) {
        Entity* ent = new Entity;
        std::string ID = ent->LoadAsImage(filename, x, y, z, w, h, rot);
        if (ID.size() > 0) {
            entity_map[ID] = ent;
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

Entity* Scene::GetCenteredEntity() {
    Entity* ret = nullptr;
    float least_distance = 10000.0f;
    Ogre::Ray ray = game.GetCamera()->getCameraToViewportRay(0.5f, 0.5f);

    for (auto const& entity_entry : entity_map) {
        if (entity_entry.second) {
            // Get the world transform of the parent node
            const Ogre::Matrix4& worldTransform = entity_entry.second->getNode()->_getFullTransform();

            // Get the AxisAlignedBox from the entity's bounding box
            const Ogre::AxisAlignedBox& localAABB = entity_entry.second->getEntity()->getBoundingBox();

            // Transform the minimum and maximum corners of the local bounding box to world space
            Ogre::AxisAlignedBox worldAABB;
            worldAABB.merge(worldTransform * localAABB.getMinimum());
            worldAABB.merge(worldTransform * localAABB.getMaximum());

            //// Access the minimum and maximum corners of the transformed AxisAlignedBox
            //const Ogre::Vector3& minCorner = worldAABB.getMinimum();
            //const Ogre::Vector3& maxCorner = worldAABB.getMaximum();
            Ogre::RayTestResult res = ray.intersects(worldAABB);
            if (res.first && res.second < least_distance) {
                ret = entity_entry.second;
                least_distance = res.second;
            }
            else {
                //std::cout << entity_entry.second->getEntity()->getBoundingBox();
            }
        }
    }
    return ret;
}

Entity* Scene::GetHoveredEntity() {
    Entity* ret = nullptr;
    float least_distance = 10000.0f;
    Ogre::Ray ray = game.GetCamera()->getCameraToViewportRay((Ogre::Real)game.mouseX / (Ogre::Real)game.GetWindow()->getWidth(), (Ogre::Real)game.mouseY / (Ogre::Real)game.GetWindow()->getHeight());

    for (auto const& entity_entry : entity_map) {
        if (entity_entry.second) {
            // Get the world transform of the parent node
            const Ogre::Matrix4& worldTransform = entity_entry.second->getNode()->_getFullTransform();

            // Get the AxisAlignedBox from the entity's bounding box
            const Ogre::AxisAlignedBox& localAABB = entity_entry.second->getEntity()->getBoundingBox();

            // Transform the minimum and maximum corners of the local bounding box to world space
            Ogre::AxisAlignedBox worldAABB;
            worldAABB.merge(worldTransform * localAABB.getMinimum());
            worldAABB.merge(worldTransform * localAABB.getMaximum());

            //// Access the minimum and maximum corners of the transformed AxisAlignedBox
            //const Ogre::Vector3& minCorner = worldAABB.getMinimum();
            //const Ogre::Vector3& maxCorner = worldAABB.getMaximum();
            Ogre::RayTestResult res = ray.intersects(worldAABB);
            if (res.first && res.second < least_distance) {
                ret = entity_entry.second;
                least_distance = res.second;
            }
            else {
                //std::cout << entity_entry.second->getEntity()->getBoundingBox();
            }
        }
    }
    return ret;
}

void Scene::Cleanup() {
    for (auto const& entity_entry : entity_map) {
        if (entity_entry.second) {
            //entity_entry.second.Cleanup();
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