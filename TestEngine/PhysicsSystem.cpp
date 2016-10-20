#include "PhysicsSystem.h"

namespace Engine
{
	PhysicsSystem::PhysicsSystem()
		: gravity(btVector3(0.0f, -10.0f, 0.0f)), collisionConfiguration(nullptr), dispatcher(nullptr), overlappingPairCache(nullptr), 
		solver(nullptr), dynamicsWorld(nullptr) 
	{
	}


	void PhysicsSystem::init()
	{
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver();

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(gravity);
		gContactProcessedCallback = onCollision;
	}


	bool PhysicsSystem::onCollision(btManifoldPoint& cp, void* body0, void* body1)
	{
		return false;
	}


	void PhysicsSystem::update(float t, float dt)
	{
		
	}


	void PhysicsSystem::setGravity(float y)
	{
		btVector3 g(0.0f, y, 0.0f);
		dynamicsWorld->setGravity(g);
	}


	void PhysicsSystem::setGravity(float x, float y, float z)
	{
		btVector3 g(x, y, z);
		dynamicsWorld->setGravity(g);
	}


	void PhysicsSystem::destroy()
	{
		// removing rigid bodies from the world
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
		// removing collision shapes
		// ...

		delete dynamicsWorld;
		delete solver;
		delete overlappingPairCache;
		delete dispatcher;
		delete collisionConfiguration;
	}


}

