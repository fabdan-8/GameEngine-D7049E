#include "Physics.h"

Physics::Physics(float gravityX, float gravityY, float gravityZ ) {
    // //collision configuration specifies the type of collision detection algorithm to use
    // collisionConfiguration = new btDefaultCollisionConfiguration();
    
    // //dispatcher is responsible for sending collision detection events to the correct objects 
    // dispatcher = new btCollisionDispatcher(collisionConfiguration);
    
    // //broadphase algorithm create a list of possible collisions for the dispatcher to check
    // broadphase = new btDbvtBroadphase();

    // //solver resolve collisions & apply constraints
    // solver = new btSequentialImpulseConstraintSolver();
    
    // //dynamics world contains all the objects in the simulation & updates them each frame
    // //simulates gravity and apply forces to objects
    // dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    
    // //set gravity (0, -9.81, 0) for Earth
    // dynamicsWorld->setGravity(btVector3(gravityX, gravityY, gravityZ));
}

Physics::Physics() {
    //collision configuration specifies the type of collision detection algorithm to use
    collisionConfiguration = new btDefaultCollisionConfiguration();

    //dispatcher is responsible for sending collision detection events to the correct objects 
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    //broadphase algorithm create a list of possible collisions for the dispatcher to check
    broadphase = new btDbvtBroadphase();

    //solver resolve collisions & apply constraints
    solver = new btSequentialImpulseConstraintSolver();

    //dynamics world contains all the objects in the simulation & updates them each frame
    //simulates gravity and apply forces to objects
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
}

Physics::~Physics() {
    //for (btRigidBody* rb : rigidBodies) {
    //    delete rb;
    //}
    //delete &rigidBodies;
    /*for (btSoftBody* sb : softBodies) {
        delete sb;
    }
    delete &softBodies;*/
    delete dynamicsWorld;
    delete solver;
    delete broadphase;
    delete dispatcher;
    delete collisionConfiguration;
}

btRigidBody* Physics::createRigidBody(Ogre::SceneNode* node, Entity *entity) {
    //get the size & mass of the entity
    Ogre::Vector3 size = entity->getSize();
    Ogre::Real mass = entity->getMass();
    //scale size to match node scale
    size *= node->getScale();

    btCollisionShape* shape = new btBoxShape(btVector3(size.x / 2, size.y / 2, size.z / 2));
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(node->getPosition().x, node->getPosition().y, node->getPosition().z));

    btScalar btMass(mass);
    btVector3 localInertia;
    shape->calculateLocalInertia(btMass, localInertia);

    btDefaultMotionState* motionState = new btDefaultMotionState(transform);
    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(btMass, motionState, shape, localInertia);
    btRigidBody* body = new btRigidBody(rigidBodyCI);
    dynamicsWorld->addRigidBody(body);
    rigidBodies.insert(std::make_pair(entity,body));
    //rigidBodies[entity] = body;
    return body;
}

/*btSoftBody* Physics::createSoftBody(OgreBulletCollisions::CollisionShape* shape, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, float mass) {
    btSoftBody* softBody = btSoftBodyHelpers::CreateFromConvexHull(dynamicsWorld->getWorldInfo(), shape->getConvexHullShape());
    
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(btVector3(position.x, position.y, position.z));
    transform.setRotation(btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w));
    softBody->transform(transform);
    softBody->setTotalMass(mass);

    dynamicsWorld->addSoftBody(softBody);
    mSoftBodies.push_back(softBody);

    return softBody;
}*/

void Physics::update(int timeSinceLastFrame) {
    dynamicsWorld->stepSimulation(timeSinceLastFrame * 0.001f, 10);
    btRigidBody *rb;
    for(auto const& iterator : rigidBodies){
        if(iterator.second){
            // Update renderer
            // Ogre::SceneNode *node = static_cast<Ogre::SceneNode *>(iterator.second->getUserPointer());
            Ogre::SceneNode *node = iterator.first->getNode();
            rb = iterator.second;

            // Set position
            btVector3 Point = rb->getCenterOfMassPosition();
            node->setPosition(Ogre::Vector3((float)Point[0], (float)Point[1], (float)Point[2]));
            // Convert the bullet Quaternion to an Ogre quaternion
            btQuaternion btq = rb->getOrientation();
            Ogre::Quaternion quart = Ogre::Quaternion(btq.w(),btq.x(),btq.y(),btq.z());
            // use the quaternion with setOrientation
            node->setOrientation(quart);
        }
    }
}

void Physics::SetGravity(float gravityX, float gravityY, float gravityZ) {
    //set gravity (0, -9.81, 0) for Earth
    if (dynamicsWorld) {
        dynamicsWorld->setGravity(btVector3(gravityX, gravityY, gravityZ));
    }
}