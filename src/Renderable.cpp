#include "Renderable.h"

#include <filesystem>
#include <iostream>

#include "GameEngine.h"
#include "GameSceneManager.h"
#include "Global.h"

//#include <OgreMaterialManager.h>
//#include <OgreMeshManager.h>
#include <OgreMeshSerializer.h>

#include "SDL.h"

//std::string meshfolder;

int Renderable::Update() {
    //if (GAME_ENGINE->renderableMap.find(entityId) != GAME_ENGINE->renderableMap.end()) {
    //    //ok

    //    return 1;
    //}
    //else {
    //    return 0;
    //    //cleanup self, whatever called function should delete to free memory
    //}
}

//Renderable::Renderable(int entityId, std::string filename, float scale, Ogre::Vector3 xyz) : entityId(entityId) {
//    // TODO: actually load the object that is to be rendered
//    if (filename.size() > 0) {
//        // GAME_ENGINE->renderableMap.insert(std::pair<int, Renderable *>(entityId, this));
//        GAME_ENGINE->renderableMap[entityId] = this;
//        // this->Load(filename, scale, xyz);
//    }
//}

void Renderable::SetMaterial(std::string name) {
    if (Ogre::MaterialManager::getSingleton().resourceExists(std::string(name + "_material"))) { // material exists, just assign it
        if (ent) {
            ent->setMaterialName(std::string(name + "_material"));
        }
        return;
    }
    // otherwise, make the material
    //std::cout << name << "_material is being made\n";

    if (false) {//only works for png, jpg and perhaps a few others (not dds though)

        std::string folder = GAME_SCENE_M->meshfolder;
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
        if (std::filesystem::exists(GAME_SCENE_M->meshfolder + name + "_D.dds")) {
            //std::cout << "D";
            material->getTechnique(0)->getPass(0)->createTextureUnitState(name + "_D.dds");
        }
        if (std::filesystem::exists(GAME_SCENE_M->meshfolder + name + "_D2.dds")) {
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

std::string Renderable::Load(std::string name, float scale, float start_x, float start_y, float start_z) {
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

            ent = GAME_SCENE_M->sceneManager->createEntity(std::string(name + ".X"));
            // Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MyMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            // material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
            // ent->setMaterialName("skeleton_material");
            if (ent) {//export mesh
                Ogre::MeshSerializer serializer;
                serializer.exportMesh(ent->getMesh(), GAME_SCENE_M->meshfolder + name + ".mesh");
            }

            SetMaterial(name);
        }
        catch (...) {
            ent = nullptr;
        }
    }
    else {
        try {
            ent = GAME_SCENE_M->sceneManager->createEntity(std::string(name + ".mesh"));
            SetMaterial(name);
        }
        catch (...) {
            ent = nullptr;
        }
    }
    if (ent) {
        Ogre::SceneNode* node = GAME_SCENE_M->sceneManager->getRootSceneNode()->createChildSceneNode();

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