#ifndef ENGINEPHYSICS_H
#define ENGINEPHYSICS_H
#include <btBulletDynamicsCommon.h>
class EnginePhysics
{
    
public:
    /**
     * EnginePhysics constructor.
     *
     * Initializes the Bullet physics engine by creating a collision configuration,
     * dispatcher, broadphase, constraint solver, and dynamics world. The gravity
     * is set to 0, -10, 0.
     */
    btDiscreteDynamicsWorld*  dynamicsWorld;
    btSequentialImpulseConstraintSolver* solver;
    btBroadphaseInterface* overlappingPairCache;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    void DoPhysicsSimulation();
    EnginePhysics()
    {
        ///-----initialization_start-----
        ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
        collisionConfiguration = new btDefaultCollisionConfiguration();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        dispatcher = new btCollisionDispatcher(collisionConfiguration);

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
       overlappingPairCache = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        solver = new btSequentialImpulseConstraintSolver;

        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

        dynamicsWorld->setGravity(btVector3(0, -10, 0));

    ///-----initialization_end-----
    };
    ~EnginePhysics(){};
};



#endif // ENGINEPHYSICS_H
