#pragma once
#include "btBulletDynamicsCommon.h"
#include "System.h"

namespace Engine
{
	class PhysicsSystem : public System
	{
		btVector3 gravity;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* world;
		static bool onContactProcessed(btManifoldPoint& cp, void* body0, void* body1);
	public:
		PhysicsSystem();

		virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;

		btDiscreteDynamicsWorld* getWorld() const { return world; }
		btCollisionWorld::ClosestRayResultCallback rayTest(const btVector3& from, const btVector3& to);

		void setGravity(float y);
		void setGravity(float x, float y, float z);
	};
}


