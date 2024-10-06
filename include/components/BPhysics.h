#ifndef BPHYSICS_H
#define BPHYSICS_H
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>
#include <EnginePhysics.h>
#include <GameObject.h>

//binds Bullet with AMW
/*
Matrix Data
Update Tick
//keep track of the shapes, we release memory at exit.
//make sure to re-use collision shapes among rigid bodies whenever possible!
btAlignedObjectArray<btCollisionShape*> collisionShapes;

///create a few basic rigid bodies

//the ground is a cube of side 100 at position y = -56.
//the sphere will hit it at y = -6, with center at -5
{
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -56, 0));

	btScalar mass(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);
}

*/
extern EnginePhysics *enginePhysics;
class BPhysicsComponent : public GameComponent
{
    btAlignedObjectArray<btCollisionShape*> collisionShapes;//Bullet Shapes Vector
    btTransform *transform;
    btScalar mass;
    btVector3 localInertia;
    btDefaultMotionState* myMotionState;
    btRigidBody* body;
    void ComponentAddedCallback();
    //ref to gameobject
   
   
    void BindMatrix()
    {       

        myMotionState->getWorldTransform(*transform); 

        

        //bullet and open gl postions are inverted, might fix in shader
        parentObject->position = -glm::vec3(transform->getOrigin().x(), transform->getOrigin().y(), transform->getOrigin().z());//fine
        parentObject->rotation = glm::quat(transform->getRotation().getW(), transform->getRotation().getX(), transform->getRotation().getZ(), transform->getRotation().getY());
          }
    public:
/**
 * Constructor for BPhysicsComponent.
 * @param pos The initial position of the rigid body.
 * @param rot The initial rotation of the rigid body.
 * @param mass The mass of the rigid body (0 for static, non-zero for dynamic).
 * @param localInertia The local inertia of the rigid body.
 * @param shape The collision shape of the rigid body.
 */
        BPhysicsComponent(glm::vec3 pos, glm::quat rot, float mass, btCollisionShape* shape)
        {
            transform = new btTransform(btQuaternion(rot.x, rot.y, rot.z, 1.0f), btVector3(pos.x, pos.y, pos.z));
            this->mass = btScalar(mass);
            this->localInertia = btVector3(0, 0, 0);
            this->myMotionState = new btDefaultMotionState(*transform);
            collisionShapes.push_back(shape);
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
            btRigidBody* body = new btRigidBody(rbInfo);
            body->setWorldTransform(*transform);
            enginePhysics->dynamicsWorld->addRigidBody(body);
        };
        ~BPhysicsComponent(){};

        void OnUpdate() override
        {
            if(!parentObject->isActive || !isActive)
            {
                return;
            }
            BindMatrix();
        }
};


#endif /* BPHYSICS_H */
