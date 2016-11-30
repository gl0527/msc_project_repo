#pragma once
#include "Component.h"
#include "btBulletDynamicsCommon.h"

namespace Engine
{
	class DLL_SPEC PhysicsComponent : public Component
	{
		float mass;
		bool trigger;
		btRigidBody* rigidBody;
		btCompoundShape* shape;
		btMotionState* motionState;

		Ogre::Vector3 getPosition() const;
		Ogre::Quaternion getOrientation() const;

		void setPosition(const Ogre::Vector3& p);
		void setOrientation(const Ogre::Quaternion& q);

		static void defaultTriggerEnter(PhysicsComponent* other);
		static void defaultCollision(PhysicsComponent* other);
	public:
		typedef enum{ STATIC, DYNAMIC, KINEMATIC } RigidBodyType;
		RigidBodyType type;

		PhysicsComponent(float m, RigidBodyType rbt);
		void addShape(btCollisionShape* collShape, const Ogre::Vector3& p = Ogre::Vector3::ZERO, const Ogre::Quaternion& q = Ogre::Quaternion::IDENTITY);
		void createBody();

		virtual void onInit(GameObject* object) override;
		virtual void onStart() override;
		virtual void onUpdate(float t, float dt) override;
		virtual void onPostUpdate(float t, float dt) override;

		// minden osztalypeldanyra mas implementacio kene - fv.-pointeres megvalositas!!!
		void (*onTriggerEnter)(PhysicsComponent* other);
		void (*onCollision)(PhysicsComponent* other);
		
		btRigidBody* getRigidBody() const { return rigidBody; }

		void addForce(float fx, float fy, float fz);
		void setFriction(float friction);
		void setDamping(float linear, float angular);
		void setRestitution(float restitution);
		void setAngularFactor(float x, float y, float z);
		void disableRotation();
		
		void setMass();
		void setTrigger(bool trigger);
		void setType(RigidBodyType rbt);

		bool isTrigger() const { return trigger; }
		
		~PhysicsComponent();
	};

}

