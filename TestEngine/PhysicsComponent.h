#pragma once
#include "Component.h"
#include "btBulletDynamicsCommon.h"

namespace Engine
{
	class DLL_SPEC PhysicsComponent : public Component
	{
		float mass;
		bool isTrigger;
		btRigidBody* rigidBody;
		btCompoundShape* shape;
		btMotionState* motionState;

		void setPosition(const Ogre::Vector3& p);
		void setOrientation(const Ogre::Quaternion& q);
	public:
		typedef enum{ STATIC, DYNAMIC, KINEMATIC } RigidBodyType;
		RigidBodyType type;

		PhysicsComponent(float m, RigidBodyType rbt);
		void addShape(btCollisionShape* collShape, const Ogre::Vector3& p = Ogre::Vector3::ZERO, const Ogre::Quaternion& q = Ogre::Quaternion::IDENTITY);
		void createBody();

		virtual void onInit(GameObject* object) override;
		virtual void onUpdate(float t, float dt) override;
		virtual void onPostUpdate(float t, float dt) override;

		Ogre::Vector3 getPosition() const;
		Ogre::Quaternion getOrientation() const;
		btRigidBody* getRigidBody() const { return rigidBody; }

		void addForce(float fx, float fy, float fz);
		void setFriction(float friction);
		void setDamping(float linear, float angular);
		void setRestitution(float restitution);
		void setAngularFactor(float x, float y, float z);
		
		void setMass();
		void setTrigger(bool trigger);
		void setType(RigidBodyType rbt);

		~PhysicsComponent();
	};

}

