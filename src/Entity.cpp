#include "Entity.h"

#include <iostream>

#include "Game.h"

#include <OgreHardwareVertexBuffer.h>
#include <OgreHardwareBufferManager.h>

extern Game game;

void Entity::Update() {

}

std::string Entity::Load(std::string name, float scale, float start_x, float start_y, float start_z) {
    Ogre::Entity* ent;
    try {

        Ogre::String meshName = "skeleton.X";// your mesh name
        Ogre::String materialName = "skeleton_D.png";// your material name
        Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        //Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(materialName);
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("skeleton_material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        
        material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
        //ent->setMaterialName("skeleton_material");

        //// Flip the texture coordinates of all submeshes in the mesh
        //Ogre::Mesh::SubMeshIterator submeshIter = mesh->getSubMeshIterator();
        //while (submeshIter.hasMoreElements())
        //{
        //    Ogre::SubMesh* submesh = submeshIter.getNext();
        //    Ogre::HardwareVertexBufferSharedPtr vertexBuffer = submesh->vertexData->vertexBufferBinding->getBuffer(0);
        //    float* textureCoordinates = static_cast<float*>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));
        //    for (size_t i = 0; i < vertexBuffer->getNumVertices(); ++i)
        //    {
        //        textureCoordinates[i * 2 + 1] = 1.0f - textureCoordinates[i * 2 + 1];
        //    }
        //    vertexBuffer->unlock();
        //    submesh->setMaterial(material);
        //    std::cout << " OOOO\n";
        //}

        // Create an entity from the mesh
       // Ogre::Entity* entity = scnMgr->createEntity(mesh);

        ent = game.scnMgr->createEntity(name);
        //Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MyMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        //material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
        ent->setMaterialName("skeleton_material");
    }
    catch (...) {
        ent = nullptr;
    }
    if (ent) {
        Ogre::SceneNode* node = game.scnMgr->getRootSceneNode()->createChildSceneNode();
        
        node->setScale(Ogre::Vector3(scale, scale, scale));
        node->setPosition(start_x, start_y, start_z);

        node->attachObject(ent);
        return ent->getName();
    }
    else {
        std::cout << "Can't find mesh '" << name << "'\n";
        return "";
    }
}