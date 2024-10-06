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



}
