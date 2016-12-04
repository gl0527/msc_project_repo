#pragma once
#include "btBulletDynamicsCommon.h"
#include "System.h"
#include <vector>

namespace Engine
{
	class PhysicsComponent;

	class PhysicsSystem : public System
	{
		btVector3 gravity;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		static bool onContactProcessed(btManifoldPoint& cp, void* body0, void* body1);
	public:
		PhysicsSystem();

		virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;

		btDiscreteDynamicsWorld* getWorld() const { return dynamicsWorld; }

		void setGravity(float y);
		void setGravity(float x, float y, float z);
	};
}


