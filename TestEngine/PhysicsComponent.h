#pragma once
#include "Component.h"
#include "btBulletDynamicsCommon.h"
#include <functional>
#include "PhysicsMaterial.h"

namespace Engine
{
	class DLL_SPEC PhysicsComponent : public Component
	{
		float mass;
		bool trigger;
		btRigidBody* rigidBody;
		btCompoundShape* shape;
		btDefaultMotionState* motionState;
		PhysicsMaterial physicsMaterial;
		btDynamicsWorld* world;

		Ogre::Vector3 getPosition() const;
		Ogre::Quaternion getOrientation() const;

		void setPosition(const Ogre::Vector3& p);
		void setOrientation(const Ogre::Quaternion& q);

		std::function<void(PhysicsComponent*)> triggerEnter;
		std::function<void(PhysicsComponent*)> collision;

		static void defaultTriggerEnter(PhysicsComponent* other) {}
		static void defaultCollision(PhysicsComponent* other) {}
	public:
		typedef enum{ STATIC, DYNAMIC, KINEMATIC } RigidBodyType;
		RigidBodyType type;

		PhysicsComponent(const std::string& name, float m, RigidBodyType rbt);
		void addShape(btCollisionShape* collShape, const Ogre::Vector3& p, const Ogre::Quaternion& q);
		void removeShape(btCollisionShape* collShape);
		void createBody();

		virtual void onInit(GameObject* object) override;
		virtual void onUpdate(float t, float dt) override;
		virtual void onDestroy() override;
		
		btRigidBody* getRigidBody() const { return rigidBody; }
		const PhysicsMaterial& getPhysicsMaterial() const { return physicsMaterial; }
		void setPhysicsMaterial(PhysicsMaterial phyMat);

		void addForce(float fx, float fy, float fz);
		void setAngularFactor(float x, float y, float z);
		void setLinearVelocity(float x, float y, float z);
		void activate();
		void disableRotation();
		
		void setMass();
		void setTrigger(bool trigger);
		void setType(RigidBodyType rbt);

		void setOnTriggerEnter(std::function<void(PhysicsComponent*)>&& f) { triggerEnter = f; }
		void setOnCollision(std::function<void(PhysicsComponent*)>&& f) { collision = f; }

		void onTriggerEnter(PhysicsComponent* other) { triggerEnter(other); }
		void onCollision(PhysicsComponent* other) { collision(other); }

		bool isTrigger() const { return trigger; }
		
		virtual ~PhysicsComponent();
	};

}

