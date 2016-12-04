#include "PhysicsComponent.h"
#include "GameObject.h"

namespace Engine
{
	PhysicsComponent::PhysicsComponent(const InitStruct& init)
		: Component(0), mass(init.mass), trigger(false), rigidBody(nullptr), motionState(nullptr), type(init.type),
		triggerEnter(defaultTriggerEnter), collision(defaultCollision)
	{
		shape = new btCompoundShape();
	}

	PhysicsComponent::PhysicsComponent(float m, RigidBodyType t)
		: Component(0), mass(m), trigger(false), rigidBody(nullptr), motionState(nullptr), type(t),
		triggerEnter(defaultTriggerEnter), collision(defaultCollision)
	{
		shape = new btCompoundShape();
	}


	void PhysicsComponent::addShape(btCollisionShape* collShape, const Ogre::Vector3& p, const Ogre::Quaternion& q)
	{
		btTransform pose(btQuaternion(q.x, q.y, q.z, q.w), btVector3(p.x, p.y, p.z));
		shape->addChildShape(pose, collShape);
	}


	void PhysicsComponent::createBody()
	{
		if (rigidBody)
		{
			Game::getInstance().getPhysicsSystem()->getWorld()->removeRigidBody(rigidBody);
			rigidBody->setUserPointer(nullptr);
			delete rigidBody;
			rigidBody = nullptr;
		}
		
		btVector3 inertia(0, 0, 0);
		if (type == STATIC)
			mass = 0;
		else
			shape->calculateLocalInertia(mass, inertia);

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, shape, inertia);
		rigidBody = new btRigidBody(rigidBodyCI);
		rigidBody->setMassProps(mass, inertia);

		if (type == RigidBodyType::KINEMATIC)
		{
			rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			rigidBody->setActivationState(DISABLE_DEACTIVATION);
		}
		rigidBody->setUserPointer(this);
	}


	void PhysicsComponent::onInit(GameObject* object)
	{
		ownerObject = object;

		const Ogre::Quaternion& q = ownerObject->getOrientation();
		const Ogre::Vector3& p = ownerObject->getPosition();

		btTransform pose(btQuaternion(q.x, q.y, q.z, q.w), btVector3(p.x, p.y, p.z));
		motionState = new btDefaultMotionState(pose);

		setMass();
		setType(type);
	}


	void PhysicsComponent::onStart()
	{
		Game::getInstance().getPhysicsSystem()->getWorld()->addRigidBody(rigidBody);
	}

	
	void PhysicsComponent::onUpdate(float t, float dt)
	{
		if (type == RigidBodyType::DYNAMIC)
		{
			ownerObject->setPosition(getPosition());
			ownerObject->setOrientation(getOrientation());
			//btVector3 ownerScaling(ownerObject->getScale().x, ownerObject->getScale().y, ownerObject->getScale().z);
			//shape->setLocalScaling(ownerScaling);
		}
	}


	void PhysicsComponent::onPostUpdate(float t, float dt)
	{
		if (type == RigidBodyType::KINEMATIC)
		{
			setPosition(ownerObject->getPosition());
			setOrientation(ownerObject->getOrientation());
			//btVector3 ownerScaling(ownerObject->getScale().x, ownerObject->getScale().y, ownerObject->getScale().z);
			//shape->setLocalScaling(ownerScaling);
		}
	}


	void PhysicsComponent::onDestroy()
	{
		delete motionState;
		delete shape;
	}


	Ogre::Vector3 PhysicsComponent::getPosition() const
	{
		btTransform transform;
		motionState->getWorldTransform(transform);
		return Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z());
	}


	Ogre::Quaternion PhysicsComponent::getOrientation() const
	{
		btTransform t;
		motionState->getWorldTransform(t);
		return Ogre::Quaternion(t.getRotation().w(), t.getRotation().x(), t.getRotation().y(), t.getRotation().z());
	}


	void PhysicsComponent::setPosition(const Ogre::Vector3& p)
	{
		btTransform prevTransform;
		motionState->getWorldTransform(prevTransform);
		btTransform newTransform(prevTransform.getRotation(), btVector3(p.x, p.y, p.z));
		motionState->setWorldTransform(newTransform);
	}


	void PhysicsComponent::setOrientation(const Ogre::Quaternion& q)
	{
		btTransform prevTransform;
		motionState->getWorldTransform(prevTransform);
		btTransform newTransform(btQuaternion(q.x, q.y, q.z, q.w), prevTransform.getOrigin());
		motionState->setWorldTransform(newTransform);
	}


	void PhysicsComponent::addForce(float fx, float fy, float fz)
	{
		if (type == RigidBodyType::DYNAMIC && rigidBody)
		{
			btVector3 centralForce(fx, fy, fz);
			rigidBody->applyCentralForce(centralForce);
		}
	}


	void PhysicsComponent::setFriction(float friction)
	{
		if (rigidBody)
			rigidBody->setFriction(friction);
	}


	void PhysicsComponent::setDamping(float linear, float angular)
	{
		if (rigidBody)
			rigidBody->setDamping(linear, angular);
	}


	void PhysicsComponent::setRestitution(float restitution)
	{
		if (rigidBody)
			rigidBody->setRestitution(restitution);
	}


	void PhysicsComponent::setAngularFactor(float x, float y, float z)
	{
		if (type == RigidBodyType::DYNAMIC && rigidBody)
			rigidBody->setAngularFactor(btVector3(x,y,z));
	}


	void PhysicsComponent::disableRotation()
	{
		if (type == RigidBodyType::DYNAMIC && rigidBody)
			rigidBody->setAngularFactor(0);
	}


	void PhysicsComponent::setMass()
	{
		if (mass == 0 && type != RigidBodyType::STATIC)
			setType(RigidBodyType::STATIC);

		if (mass > 0)
		{
			btVector3 inertia(0, 0, 0);
			shape->calculateLocalInertia(mass, inertia);
		}
	}


	void PhysicsComponent::setTrigger(bool t)
	{
		trigger = t;
		if (trigger)
		{
			if (rigidBody)
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}
		else
		{
			// torolni kene az elobb beallitott flag-eket
		}
	}


	void PhysicsComponent::setType(RigidBodyType rbt)
	{
		type = rbt;
		// eddig beallitott flag-ek torlese
		// ...
		createBody();
	}


	PhysicsComponent::~PhysicsComponent()
	{
	}


}

