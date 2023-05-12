#pragma once

#include "Entity.h"
#include "OgreApplicationContext.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletCollision/CollisionShapes/btShapeHull.h"
#include <map>


struct Physics {
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* broadphase;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    std::map<Entity*, std::vector<btRigidBody*>> rigidBodies;
    //std::map<Entity*, std::vector<btSoftBody*>> softBodies;

    void update(int timeSinceLastFrame);
    btRigidBody* createRigidBody(Ogre::SceneNode* node, Entity *entity);
    //btSoftBody* createSoftBody(OgreBulletCollisions::CollisionShape* shape, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float mass);

    Physics(float gravityX, float gravityY, float gravityZ);
    ~Physics();
};
