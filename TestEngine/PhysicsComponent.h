#pragma once
#include "Component.h"
#include "btBulletDynamicsCommon.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
		float mass;
		bool isTrigger;
		btRigidBody* rigidBody;
		std::vector<btCollisionShape*> shapes;
		btMotionState* motionState;

		void setPosition(const Ogre::Vector3& p);
		void setOrientation(const Ogre::Quaternion& q);

	public:
		PhysicsComponent(float m);

		enum{ STATIC, DYNAMIC, KINEMATIC } type;

		virtual void onPreUpdate(float t, float dt) override;
		virtual void onUpdate(float t, float dt) override;
		virtual void onPostUpdate(float t, float dt) override;

		Ogre::Vector3 getPosition() const;
		Ogre::Quaternion getOrientation() const;

		void addForce(float fx, float fy, float fz);
		void setFriction(float friction);
		void setDamping(float linear, float angular);
		void setRestitution(float restitution);
		void setAngularFactor(float x, float y, float z);
		void setTrigger(bool trigger) { isTrigger = trigger; }

		~PhysicsComponent();
	};

}

