#include <EnginePhysics.h>
#include "../debug/debug.h"
/**
 * Simulates a single tick of the physics engine.
 *
 * This does two things. First, it calls stepSimulation to advance the physics simulation by a single tick.
 * Second, it prints the world positions of all objects.
 */
void EnginePhysics::DoPhysicsSimulation()
{
   
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	//print positions of all objects
	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = obj->getWorldTransform();
		}
		debugLog("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}

}
