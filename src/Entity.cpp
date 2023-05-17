#include "Entity.h"

#include <iostream>
#include <filesystem>

#include "Game.h"

// #include <OgreHardwareVertexBuffer.h>
// #include <OgreHardwareBufferManager.h>

#include <OgreMaterialManager.h>
#include <OgreMeshManager.h>
//#include <OgreQuaternion.h>

extern Game game;
extern std::string meshfolder;

//extern std::mutex ogre_resource_mut;

std::string Entity::Load(std::string name, float scale, float start_x, float start_y, float start_z) {
    //ogre_resource_mut.lock();
    if (name.find(".X") != std::string::npos && name.size() > 2) {
        try {
            // From ChatGPT:
            // Ogre::String meshName = "skeleton.X";         // your mesh name
            ////Ogre::String materialName = "skeleton_D.png"; // your material name
            // Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            ////// Ogre::MaterialPtr material =
            ////Ogre::MaterialManager::getSingleton().getByName(materialName);
            ////Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("skeleton_material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

            ////material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
            ////ent->setMaterialName("skeleton_material");

            //// Flip the texture coordinates of all submeshes in the mesh
            // Ogre::Mesh::SubMeshIterator submeshIter = mesh->getSubMeshIterator();
            // while (submeshIter.hasMoreElements()) {
            //    Ogre::SubMesh *submesh = submeshIter.getNext();
            //    Ogre::HardwareVertexBufferSharedPtr vertexBuffer = submesh->vertexData->vertexBufferBinding->getBuffer(0);
            //    float *textureCoordinates = static_cast<float *>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));
            //    for (size_t i = 0; i < vertexBuffer->getNumVertices(); ++i) {
            //        //textureCoordinates[i * 2 + 1] = 1.0f - textureCoordinates[i * 2 + 1];
            //    }
            //    vertexBuffer->unlock();
            //    //submesh->setMaterial(material);
            //    std::cout << " OOOO\n";
            //}

            // Create an entity from the mesh
            // Ogre::Entity* entity = scnMgr->createEntity(mesh);
            name = name.substr(0, name.size() - 2);

            ent = game.scnMgr->createEntity(std::string(name + ".X"));
            // Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MyMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            // material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
            // ent->setMaterialName("skeleton_material");
            if (ent) {//export mesh
                Ogre::MeshSerializer serializer;
                serializer.exportMesh(ent->getMesh(), meshfolder + name + ".mesh");
            }

            SetMaterial(name);
        }
        catch (...) {
            ent = nullptr;
        }
    }
    else if (name.find(".scene") != std::string::npos && name.size() > 2) {
        try {
            ent = game.scnMgr->createEntity(std::string(name + ".scene"));
        }
        catch (...) {
            ent = nullptr;
        }
    }
    else {
        try {
            ent = game.scnMgr->createEntity(std::string(name + ".mesh"));
            SetMaterial(name);
        }
        catch (...) {
            ent = nullptr;
        }
    }
    if (ent) {

        size = ent->getBoundingBox().getSize();//this sounds like the size
        mass = 1.0f * scale * size.x * size.y * size.z;//"density" 1.0f

        node = game.scnMgr->getRootSceneNode()->createChildSceneNode();

        node->setScale(Ogre::Vector3(scale, scale, scale));
        node->setPosition(start_x, start_y, start_z);

        node->attachObject(ent);

        //ogre_resource_mut.unlock();
        return ent->getName();
    }
    else {
        std::cout << "Can't find mesh '" << name << "'\n";
        //ogre_resource_mut.unlock();
        return "";
    }
}

std::string Entity::LoadAsImage(std::string filename, float x, float y, float z, float w, float h, float rot) {
    try {
        Ogre::TextureManager& texMgr = Ogre::TextureManager::getSingleton();
        Ogre::TexturePtr texture = texMgr.load(filename, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(filename, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        material->getTechnique(0)->getPass(0)->createTextureUnitState(filename);

        //std::string meshname = filename + std::to_string(w) + std::to_string(h);

        //if (Ogre::MaterialManager::getSingleton().resourceExists(meshname)) {
        //    //already exists
        //    return "";
        //}

        //Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(meshname, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        //Ogre::SubMesh* submesh = mesh->createSubMesh();
        //submesh->useSharedVertices = false;
        //submesh->vertexData = new Ogre::VertexData();
        //submesh->indexData = new Ogre::IndexData();

        //Ogre::VertexData* vertexData = submesh->vertexData;
        //Ogre::IndexData* indexData = submesh->indexData;

        //// Define the vertices of the rectangle
        //Ogre::VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
        //vertexDecl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
        //Ogre::VertexBufferBinding* binding = vertexData->vertexBufferBinding;
        //Ogre::HardwareVertexBufferSharedPtr vertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
        //    vertexDecl->getVertexSize(0), 4, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
        //float* vertices = static_cast<float*>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
        //vertices[0] = -1.0f; vertices[1] = 0.0f; vertices[2] = -1.0f;
        //vertices[3] = -1.0f; vertices[4] = 0.0f; vertices[5] = 1.0f;
        //vertices[6] = 1.0f; vertices[7] = 0.0f; vertices[8] = -1.0f;
        //vertices[9] = 1.0f; vertices[10] = 0.0f; vertices[11] = 1.0f;
        //vertexBuffer->unlock();
        //binding->setBinding(0, vertexBuffer);

        //// Define the indices of the rectangle
        //Ogre::HardwareIndexBufferSharedPtr indexBuffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
        //    Ogre::HardwareIndexBuffer::IT_16BIT, 6, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
        //uint16_t* indices = static_cast<uint16_t*>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
        //indices[0] = 0; indices[1] = 1; indices[2] = 2;
        //indices[3] = 1; indices[4] = 3; indices[5] = 2;
        //indexBuffer->unlock();
        //indexData->indexBuffer = indexBuffer;
        //indexData->indexCount = 6;
        //indexData->indexStart = 0;
        ent = game.scnMgr->createEntity("skeleton.X");
        ent->setMaterial(material);
        node->attachObject(ent);
    }
    catch (...) {
        ent = nullptr;
    }

    if (ent) {

        size = Ogre::Vector3(w, h, 0.0f);
        mass = 0.0f;

        node = game.scnMgr->getRootSceneNode()->createChildSceneNode();

        node->setScale(Ogre::Vector3(w, h, 0.1f));
        node->setPosition(x, y, z);
        node->rotate(Ogre::Quaternion(Ogre::Radian(rot), Ogre::Vector3::UNIT_Y), Ogre::Node::TS_PARENT);

        node->attachObject(ent);

        //ogre_resource_mut.unlock();
        return ent->getName();
    }
    else {
        //ogre_resource_mut.unlock();
        return "";
    }
}

void Entity::Update() {
    if (!node) {
        return;
    }
    //std::cout << "a";
    //node->translate(Ogre::Vector3((Ogre::Real)(0.0f), (Ogre::Real)(0.1f), (Ogre::Real)(0.0f)), Ogre::Node::TS_LOCAL);
    //if (node) {
    //    node->translate(Ogre::Vector3(0.0f, 0.02f, 0.0f), Ogre::Node::TS_PARENT);//TEST ONLY
    //    //node->setPosition(Ogre::Vector3(0.0f, 0.0f, 0.0f));
    //    //node->attachObject(ent);
    //}
    //else {
    //    std::cout << "b";
    //}
    if (moves.size() > 0) {
        //std::cout << moves.front().counter << "/" << moves.front().maxcounter << " ";
        moves.front().counter += 1;
        float weight = 1.0f / moves.front().maxcounter;
        if (moves.front().counter >= moves.front().maxcounter) {
            node->setPosition(Ogre::Vector3(moves.front().x, moves.front().y, moves.front().z));
            if (moves.front().finished_script) {
                moves.front().finished_script->Read(this);
            }
            moves.erase(moves.begin());
        }
        else {
            Ogre::Vector3 update_pos = moves.front().dir * weight;
            //std::cout << update_pos.x << " " << update_pos.y << " " << update_pos.z << ":";
            node->translate(update_pos);
        }
    }
}

void Entity::Interact() {
    if (interaction_script) {
        interaction_script->Read(this);
    }
}

void Entity::QueueMove(float x, float y, float z, float speed, Script* script) {
    if (!node || speed <= 0.0f) {
        return;
    }
    Ogre::Vector3 pos;
    if (moves.size() == 0) {
        pos = node->getPosition();
    }
    else {
        pos = Ogre::Vector3(moves.back().x, moves.back().y, moves.back().z);
    }
    float dist = sqrt(pow(x - pos.x, 2) + pow(y - pos.y, 2) + pow(z - pos.z, 2));
    Ogre::Vector3 dir = Ogre::Vector3(x, y, z) - pos;
    int maxcounter = dist / speed;
    if (maxcounter < 1) {
        maxcounter = 1;
        dir = Ogre::Vector3(0.0f, 1.0f, 0.0f);
    }
    //dir.normalise();
    moves.push_back({ x, y, z, dir, 0, maxcounter, script });
    //std::cout << "Queued a move. ";
}

void Entity::SetMaterial(std::string name) {
    if (Ogre::MaterialManager::getSingleton().resourceExists(std::string(name + "_material"))) { // material exists, just assign it
        if (ent) {
            ent->setMaterialName(std::string(name + "_material"));
        }
        return;
    }
    // otherwise, make the material
    //std::cout << name << "_material is being made\n";

    if (false) {//only works for png, jpg and perhaps a few others (not dds though)

        std::string folder = meshfolder;
        SDL_Surface* surf = IMG_Load(std::string(folder + name + "_D.png").c_str());
        if (!surf) {
            return;
        }
        if (surf->format->BytesPerPixel == 4) {
            // ok
        }
        else {
            SDL_Surface* buf_surf = surf;
            surf = SDL_ConvertSurfaceFormat(buf_surf, SDL_PIXELFORMAT_RGBA32, 0);
            SDL_FreeSurface(buf_surf);
        }

        //// modify pixel data
        // unsigned char *pixels = ( unsigned char * ) surf->pixels;
        // unsigned char *pixel_buf
        //        = ( unsigned char * ) malloc ( surf->w * surf->h * 4 );
        // memcpy ( pixel_buf, pixels, surf->w * surf->h * 4 );

        // int w = surf->w;
        // int h = surf->h;

        // for (int a = 0; a < surf->h; a++) {//flip vertically
        //     for (int b = 0; b < surf->w; b += 4) {
        //         pixels[a * w + b + 0] = pixel_buf[(a + 1) * w - b - 4 + 0];
        //         pixels[a * w + b + 1] = pixel_buf[(a + 1) * w - b - 4 + 1];
        //         pixels[a * w + b + 2] = pixel_buf[(a + 1) * w - b - 4 + 2];
        //         pixels[a * w + b + 3] = pixel_buf[(a + 1) * w - b - 4 + 3];
        //     }
        // }

        // memcpy(pixel_buf, pixels, surf->w * surf->h * 4);

        // for (int a = 0; a < surf->h; a++) {//flip horizontally
        //     for (int b = 0; b < surf->w; b += 4) {
        //         pixels[a * w + b + 0] = pixel_buf[(h - a - 1) * w + b + 0];
        //         pixels[a * w + b + 1] = pixel_buf[(h - a - 1) * w + b + 1];
        //         pixels[a * w + b + 2] = pixel_buf[(h - a - 1) * w + b + 2];
        //         pixels[a * w + b + 3] = pixel_buf[(h - a - 1) * w + b + 3];
        //     }
        // }

        // free ( pixel_buf );

        Ogre::Image image;
        image.loadDynamicImage((Ogre::uchar*)surf->pixels, (Ogre::uint32)surf->w, (Ogre::uint32)surf->h, Ogre::PF_BYTE_RGBA);
        Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().loadImage(std::string(name + "_texture"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, image);

        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(std::string(name + "_material"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        // Ogre::TextureUnitState *textureUnit =
        material->getTechnique(0)->getPass(0)->createTextureUnitState(std::string(name + "_texture"));
        SDL_FreeSurface(surf);
    }
    else {
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(std::string(name + "_material"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        //std::cout << ">";
        //std::cout << GAME_SCENE_M->meshfolder + name + "_D.dds" << "\n";
        if (std::filesystem::exists(meshfolder + name + "_D.dds")) {
            //std::cout << "D";
            material->getTechnique(0)->getPass(0)->createTextureUnitState(name + "_D.dds");
        }
        if (std::filesystem::exists(meshfolder + name + "_D2.dds")) {
            //std::cout << "D2";
            material->getTechnique(0)->getPass(0)->createTextureUnitState(name + "_D2.dds");
        }
        // material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_S.dds");
        // material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_N.dds");
        material->setCullingMode(Ogre::CullingMode::CULL_ANTICLOCKWISE);
    }

    if (ent) {
        ent->setMaterialName(std::string(name + "_material"));
    }

    return;
}


//
//void Entity::SetMaterial(std::string name) {
//    if (Ogre::MaterialManager::getSingleton().resourceExists(std::string(name + "_material"))) { // material exists, just assign it
//        if (ent) {
//            ent->setMaterialName(std::string(name + "_material"));
//        }
//        return;
//    }
//
//    // otherwise, make the material
//    // std::cout << name << "_material is being made\n";
//
//    if (false) {
//
//        std::string folder = meshfolder;
//        SDL_Surface *surf = IMG_Load(std::string(folder + name + "_D.png").c_str());
//        if (!surf) {
//            return;
//        }
//        if (surf->format->BytesPerPixel == 4) {
//            // ok
//        } else {
//            SDL_Surface *buf_surf = surf;
//            surf = SDL_ConvertSurfaceFormat(buf_surf, SDL_PIXELFORMAT_RGBA32, 0);
//            SDL_FreeSurface(buf_surf);
//        }
//
//        //// modify pixel data
//        // unsigned char *pixels = ( unsigned char * ) surf->pixels;
//        // unsigned char *pixel_buf
//        //        = ( unsigned char * ) malloc ( surf->w * surf->h * 4 );
//        // memcpy ( pixel_buf, pixels, surf->w * surf->h * 4 );
//
//        // int w = surf->w;
//        // int h = surf->h;
//
//        // for (int a = 0; a < surf->h; a++) {//flip vertically
//        //     for (int b = 0; b < surf->w; b += 4) {
//        //         pixels[a * w + b + 0] = pixel_buf[(a + 1) * w - b - 4 + 0];
//        //         pixels[a * w + b + 1] = pixel_buf[(a + 1) * w - b - 4 + 1];
//        //         pixels[a * w + b + 2] = pixel_buf[(a + 1) * w - b - 4 + 2];
//        //         pixels[a * w + b + 3] = pixel_buf[(a + 1) * w - b - 4 + 3];
//        //     }
//        // }
//
//        // memcpy(pixel_buf, pixels, surf->w * surf->h * 4);
//
//        // for (int a = 0; a < surf->h; a++) {//flip horizontally
//        //     for (int b = 0; b < surf->w; b += 4) {
//        //         pixels[a * w + b + 0] = pixel_buf[(h - a - 1) * w + b + 0];
//        //         pixels[a * w + b + 1] = pixel_buf[(h - a - 1) * w + b + 1];
//        //         pixels[a * w + b + 2] = pixel_buf[(h - a - 1) * w + b + 2];
//        //         pixels[a * w + b + 3] = pixel_buf[(h - a - 1) * w + b + 3];
//        //     }
//        // }
//
//        // free ( pixel_buf );
//
//        Ogre::Image image;
//        image.loadDynamicImage((Ogre::uchar *)surf->pixels, (Ogre::uint32)surf->w, (Ogre::uint32)surf->h, Ogre::PF_BYTE_RGBA);
//        Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().loadImage(std::string(name + "_texture"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, image);
//
//        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(std::string(name + "_material"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//        // Ogre::TextureUnitState *textureUnit =
//        material->getTechnique(0)->getPass(0)->createTextureUnitState(std::string(name + "_texture"));
//        SDL_FreeSurface(surf);
//    } else {
//        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(std::string(name + "_material"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//        if (std::filesystem::exists(meshfolder + name + "_D.dds")) {
//            material->getTechnique(0)->getPass(0)->createTextureUnitState(name + "_D.dds");
//        }
//        if (std::filesystem::exists(meshfolder + name + "_D2.dds")) {
//            material->getTechnique(0)->getPass(0)->createTextureUnitState(name + "_D2.dds");
//        }
//        //material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_S.dds");
//        //material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_N.dds");
//        material->setCullingMode(Ogre::CullingMode::CULL_ANTICLOCKWISE);
//    }
//
//    if (ent) {
//        ent->setMaterialName(std::string(name + "_material"));
//    }
//
//    return;
//}
//
//std::string Entity::Load(std::string name, float scale, float start_x, float start_y, float start_z) {
//    if (name.find(".mesh") != std::string::npos) {
//        try {
//            ent = game.scnMgr->createEntity(name);
//        }
//        catch (...) {
//            ent = nullptr;
//        }
//    } else {
//        try {
//            // From ChatGPT:
//            // Ogre::String meshName = "skeleton.X";         // your mesh name
//            ////Ogre::String materialName = "skeleton_D.png"; // your material name
//            // Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//            ////// Ogre::MaterialPtr material =
//            ////Ogre::MaterialManager::getSingleton().getByName(materialName);
//            ////Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("skeleton_material", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//
//            ////material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
//            ////ent->setMaterialName("skeleton_material");
//
//            //// Flip the texture coordinates of all submeshes in the mesh
//            // Ogre::Mesh::SubMeshIterator submeshIter = mesh->getSubMeshIterator();
//            // while (submeshIter.hasMoreElements()) {
//            //    Ogre::SubMesh *submesh = submeshIter.getNext();
//            //    Ogre::HardwareVertexBufferSharedPtr vertexBuffer = submesh->vertexData->vertexBufferBinding->getBuffer(0);
//            //    float *textureCoordinates = static_cast<float *>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));
//            //    for (size_t i = 0; i < vertexBuffer->getNumVertices(); ++i) {
//            //        //textureCoordinates[i * 2 + 1] = 1.0f - textureCoordinates[i * 2 + 1];
//            //    }
//            //    vertexBuffer->unlock();
//            //    //submesh->setMaterial(material);
//            //    std::cout << " OOOO\n";
//            //}
//
//            // Create an entity from the mesh
//            // Ogre::Entity* entity = scnMgr->createEntity(mesh);
//
//            ent = game.scnMgr->createEntity(std::string(name + ".X"));
//            // Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MyMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//            // material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
//            // ent->setMaterialName("skeleton_material");
//
//            SetMaterial(name);
//        } catch(...) { ent = nullptr; }
//    }
//    if (ent) {
//        Ogre::SceneNode *node = game.scnMgr->getRootSceneNode()->createChildSceneNode();
//
//        node->setScale(Ogre::Vector3(scale, scale, scale));
//        node->setPosition(start_x, start_y, start_z);
//
//        node->attachObject(ent);
//        return ent->getName();
//    } else {
//        std::cout << "Can't find mesh '" << name << "'\n";
//        return "";
//    }
//}