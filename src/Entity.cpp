#include "Entity.h"

#include <iostream>

#include "Game.h"

// #include <OgreHardwareVertexBuffer.h>
// #include <OgreHardwareBufferManager.h>

#include <OgreMaterialManager.h>

extern Game game;

void Entity::Update() {
}

void Entity::SetMaterial(std::string name) {
    if (Ogre::MaterialManager::getSingleton().resourceExists(std::string(name + "_material"))) { // material exists, just assign it
        if (ent) {
            ent->setMaterialName(std::string(name + "_material"));
        }
        return;
    }

    // otherwise, make the material
    // std::cout << name << "_material is being made\n";

    std::string folder = "mesh/";
    SDL_Surface *surf = IMG_Load(std::string(folder + name + "_D.png").c_str());
    if (!surf) {
        return;
    }
    if (surf->format->BytesPerPixel == 4) {
        // ok
    } else {
        SDL_Surface *buf_surf = surf;
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
    image.loadDynamicImage((Ogre::uchar *)surf->pixels, (Ogre::uint32)surf->w, (Ogre::uint32)surf->h, Ogre::PF_BYTE_RGBA);
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().loadImage(std::string(name + "_texture"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, image);

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(std::string(name + "_material"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::TextureUnitState *textureUnit = material->getTechnique(0)->getPass(0)->createTextureUnitState(std::string(name + "_texture"));

    if (ent) {
        ent->setMaterialName(std::string(name + "_material"));
    }

    SDL_FreeSurface(surf);
    return;
}

std::string Entity::Load(std::string name, float scale, float start_x, float start_y, float start_z) {
    try {
        // From ChatGPT:
        //               Ogre::String meshName = "skeleton.X";// your mesh name
        //               Ogre::String materialName = "skeleton_D.png";// your
        //               material name Ogre::MeshPtr mesh =
        //               Ogre::MeshManager::getSingleton().load(meshName,
        //               Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        //               //Ogre::MaterialPtr material =
        //               Ogre::MaterialManager::getSingleton().getByName(materialName);
        //               Ogre::MaterialPtr material =
        //               Ogre::MaterialManager::getSingleton().create("skeleton_material",
        //               Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        //
        //               material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
        //               ent->setMaterialName("skeleton_material");

        //// Flip the texture coordinates of all submeshes in the mesh
        // Ogre::Mesh::SubMeshIterator submeshIter = mesh->getSubMeshIterator();
        // while (submeshIter.hasMoreElements())
        //{
        //     Ogre::SubMesh* submesh = submeshIter.getNext();
        //     Ogre::HardwareVertexBufferSharedPtr vertexBuffer =
        //     submesh->vertexData->vertexBufferBinding->getBuffer(0); float*
        //     textureCoordinates =
        //     static_cast<float*>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));
        //     for (size_t i = 0; i < vertexBuffer->getNumVertices(); ++i)
        //     {
        //         textureCoordinates[i * 2 + 1] = 1.0f - textureCoordinates[i *
        //         2 + 1];
        //     }
        //     vertexBuffer->unlock();
        //     submesh->setMaterial(material);
        //     std::cout << " OOOO\n";
        // }

        // Create an entity from the mesh
        // Ogre::Entity* entity = scnMgr->createEntity(mesh);

        ent = game.scnMgr->createEntity(std::string(name + ".X"));
        // Ogre::MaterialPtr material =
        // Ogre::MaterialManager::getSingleton().create("MyMaterial",
        // Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        // material->getTechnique(0)->getPass(0)->createTextureUnitState("skeleton_D.png");
        // ent->setMaterialName("skeleton_material");

        SetMaterial(name);
    } catch (...) {
        ent = nullptr;
    }
    if (ent) {
        Ogre::SceneNode *node = game.scnMgr->getRootSceneNode()->createChildSceneNode();

        node->setScale(Ogre::Vector3(scale, scale, scale));
        node->setPosition(start_x, start_y, start_z);

        node->attachObject(ent);
        return ent->getName();
    } else {
        std::cout << "Can't find mesh '" << name << "'\n";
        return "";
    }
}