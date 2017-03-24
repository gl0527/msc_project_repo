#include "PhysicsComponent.h"
#include "GameObject.h"

namespace Engine
{
	PhysicsComponent::PhysicsComponent(const std::string& name, float m, RigidBodyType t)
		: Component(name),
		mass(m),
		trigger(false),
		rigidBody(nullptr),
		shape(new btCompoundShape),
		world(Game::getInstance().getPhysicsSystem()->getWorld()),
		type(t),
		triggerEnter(defaultTriggerEnter),
		collision(defaultCollision)
	{
		
	}


	void PhysicsComponent::addShape(btCollisionShape* collShape, const Ogre::Vector3& p, const Ogre::Quaternion& q)
	{
		btTransform pose(btQuaternion(q.x, q.y, q.z, q.w), btVector3(p.x, p.y, p.z));
		shape->addChildShape(pose, collShape);
	}


	void PhysicsComponent::removeShape(btCollisionShape* collShape)
	{
		shape->removeChildShape(collShape);
	}


	void PhysicsComponent::createBody()
	{
		if (rigidBody)
		{
			world->removeRigidBody(rigidBody);
			rigidBody->setUserPointer(nullptr);
			delete rigidBody;
			rigidBody = nullptr;
		}
		
		btVector3 inertia(0, 0, 0);
		if (type == RigidBodyType::STATIC)
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
		world->addRigidBody(rigidBody);
	}


	void PhysicsComponent::onInit(GameObject* object)
	{
		ownerObject = object;

		const Ogre::Quaternion& q = ownerObject->transform()->rotation();
		const Ogre::Vector3& p = ownerObject->transform()->position();

		btTransform pose(btQuaternion(q.x, q.y, q.z, q.w), btVector3(p.x, p.y, p.z));
		motionState = new btDefaultMotionState(pose);

		setMass();
		setType(type);
	}

	
	void PhysicsComponent::onUpdate(float t, float dt)
	{
		if (type == RigidBodyType::DYNAMIC)
		{
			ownerObject->transform()->setPosition(getPosition());
			ownerObject->transform()->setRotation(getOrientation());
		}
		else if (type == RigidBodyType::KINEMATIC)
		{
			setPosition(ownerObject->transform()->position());
			setOrientation(ownerObject->transform()->rotation());

			// getshape, atallitas (localscale), setshape
			// vagy rigidbody lezuzas
			
			/*auto collShape = rigidBody->getCollisionShape();
			const auto& ownerScale = ownerObject->transform()->scale();
			collShape->setLocalScaling(btVector3(ownerScale.x, ownerScale.y, ownerScale.z));
			rigidBody->setCollisionShape(collShape);*/
		}
	}


	void PhysicsComponent::onDestroy()
	{
		for (int i = 0; i<shape->getNumChildShapes(); ++i)
		{
			btCollisionShape* s = shape->getChildShape(i);
			shape->removeChildShape(s);
		}
		btCollisionObject* obj = static_cast<btCollisionObject*>(rigidBody);
		world->removeCollisionObject(obj);
		world->removeRigidBody(rigidBody);
		
		if (shape)
		{
			delete shape;
			shape = nullptr;
		}
		if (motionState)
		{
			delete motionState;
			motionState = nullptr;
		}
		if (rigidBody)
		{
			delete rigidBody;
			rigidBody = nullptr;
		}
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


	void PhysicsComponent::setPhysicsMaterial(PhysicsMaterial phyMat)
	{
		physicsMaterial = phyMat;
		if (rigidBody)
		{
			rigidBody->setFriction(physicsMaterial.getFriction());
			rigidBody->setDamping(physicsMaterial.getLinearDamping(), physicsMaterial.getAngularDamping());
			rigidBody->setRestitution(physicsMaterial.getRestitution());
		}
	}


	void PhysicsComponent::addForce(float fx, float fy, float fz)
	{
		if (type == RigidBodyType::DYNAMIC && rigidBody)
		{
			btVector3 centralForce(fx, fy, fz);
			rigidBody->applyCentralForce(centralForce);
		}
	}


	void PhysicsComponent::setAngularFactor(float x, float y, float z)
	{
		if (type == RigidBodyType::DYNAMIC && rigidBody)
			rigidBody->setAngularFactor(btVector3(x,y,z));
	}


	void PhysicsComponent::setLinearVelocity(float x, float y, float z)
	{
		if(type == RigidBodyType::DYNAMIC && rigidBody)
			rigidBody->setLinearVelocity(btVector3(x, y, z));
	}


	void PhysicsComponent::activate()
	{
		if (rigidBody)
			rigidBody->activate(true);
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
			if (rigidBody)
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & !btCollisionObject::CF_NO_CONTACT_RESPONSE);
		}
	}


	void PhysicsComponent::setType(RigidBodyType rbt)
	{
		if (type == RigidBodyType::KINEMATIC && rbt != RigidBodyType::KINEMATIC)
		{
			if (rigidBody)
			{
				rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & !btCollisionObject::CF_KINEMATIC_OBJECT);
				//rigidBody->setActivationState(DISABLE_DEACTIVATION);
			}
		}
		type = rbt;
		createBody();
	}


	PhysicsComponent::~PhysicsComponent()
	{
	}


}

