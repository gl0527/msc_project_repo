#include "PhysicsSystem.h"
#include "PhysicsComponent.h"

namespace Engine
{
	PhysicsSystem::PhysicsSystem()
		: gravity(btVector3(0.0f, -100.0f, 0.0f)),
		collisionConfiguration(nullptr),
		dispatcher(nullptr),
		overlappingPairCache(nullptr), 
		solver(nullptr),
		dynamicsWorld(nullptr)
	{
	}


	bool PhysicsSystem::init()
	{
		collisionConfiguration = new btDefaultCollisionConfiguration;
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		overlappingPairCache = new btDbvtBroadphase;
		solver = new btSequentialImpulseConstraintSolver;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
		dynamicsWorld->setGravity(gravity);
		gContactProcessedCallback = onContactProcessed;

		return true;
	}


	bool PhysicsSystem::onContactProcessed(btManifoldPoint& cp, void* body0, void* body1)
	{
		btRigidBody* rigidbody0 = (btRigidBody*)body0;
		btRigidBody* rigidbody1 = (btRigidBody*)body1;

		PhysicsComponent* collider0 = (PhysicsComponent*)rigidbody0->getUserPointer();
		PhysicsComponent* collider1 = (PhysicsComponent*)rigidbody1->getUserPointer();

		if (collider0 && collider0->isTrigger()) // az elso szereplo trigger volt
		{
			collider0->onTriggerEnter(collider1);
		}
		else if (collider1 && collider1->isTrigger()) // a masodik szereplo trigger volt
		{
			collider1->onTriggerEnter(collider0);
		}
		else // egyik szereplo sem volt trigger
		{
			collider0->onCollision(collider1);
			collider1->onCollision(collider0);
		}
		return true;
	}


	bool PhysicsSystem::update(float t, float dt)
	{
		if (dynamicsWorld)
		{
			dynamicsWorld->stepSimulation(dt);
			return true;
		}
		else
			return false;
	}


	void PhysicsSystem::setGravity(float y)
	{
		btVector3 g(0.0f, y, 0.0f);
		if (dynamicsWorld)
			dynamicsWorld->setGravity(g);
	}


	void PhysicsSystem::setGravity(float x, float y, float z)
	{
		btVector3 g(x, y, z);
		if (dynamicsWorld)
			dynamicsWorld->setGravity(g);
	}


	void PhysicsSystem::destroy()
	{
		if (dynamicsWorld)
		{
			delete dynamicsWorld;
			dynamicsWorld = nullptr;
		}
		if (solver)
		{
			delete solver;
			solver = nullptr;
		}
		if (overlappingPairCache)
		{
			delete overlappingPairCache;
			overlappingPairCache = nullptr;
		}
		if (dispatcher)
		{
			delete dispatcher;
			dispatcher = nullptr;
		}
		if (collisionConfiguration)
		{
			delete collisionConfiguration;
			collisionConfiguration = nullptr;
		}
	}


}

