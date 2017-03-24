#include "DynamicMovementComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

DynamicMovementComponent::DynamicMovementComponent(const std::string& name)
	:Component(name),
	moveSpeed(10000.0f),
	inputHandler(nullptr),
	ownerPhysics(nullptr)
{
}


DynamicMovementComponent::~DynamicMovementComponent()
{
}


void DynamicMovementComponent::onStart()
{
	inputHandler = Game::getInstance().getInputHandler();
	ownerPhysics = ownerObject->getFirstComponentByType<PhysicsComponent>().get();
}


void DynamicMovementComponent::onPreUpdate(float t, float dt)
{
	const OIS::MouseState& ms = inputHandler->getMouseState();
	Ogre::Vector3 force = Ogre::Vector3::ZERO;

	if (inputHandler->isKeyDown(OIS::KC_ESCAPE))
	{
		Game::getInstance().destroy();
		return;
	}
	if (inputHandler->isKeyDown(OIS::KC_D))
		force += Ogre::Vector3(1.0f, 0.0f, 0.0f);
	if (inputHandler->isKeyDown(OIS::KC_A))
		force += Ogre::Vector3(-1.0f, 0.0f, 0.0f);
	if (inputHandler->isKeyDown(OIS::KC_W))
		force += Ogre::Vector3(0.0f, 0.0f, -1.0f);
	if (inputHandler->isKeyDown(OIS::KC_S))
		force += Ogre::Vector3(0.0f, 0.0f, 1.0f);

	/*if (ms.buttonDown(OIS::MB_Left))
		std::cout << "lmb: " << ms.X.abs << ", " << ms.Y.abs << std::endl;
	if (ms.buttonDown(OIS::MB_Right))
		std::cout << "rmb: " << ms.X.rel << ", " << ms.Y.rel << std::endl;

	Ogre::Radian yaw(-0.003 * ms.X.rel);
	Ogre::Quaternion Qyaw(yaw, Ogre::Vector3::UNIT_Y);
	ownerObject->transform()->setRotation(Qyaw * ownerObject->transform()->rotation());

	const Ogre::Vector3& right = ownerObject->transform()->right();
	Ogre::Radian pitch(-0.003 * ms.Y.rel);
	Ogre::Quaternion Qpitch(pitch, right);
	ownerObject->transform()->setRotation(Qpitch * ownerObject->transform()->rotation());*/

	force.normalise();
	force = ownerObject->transform()->rotation() * force; // azert, hogy a movedir az ownerObject koordinata-rendszereben legyen ertve

	if (ownerPhysics)
	{
		ownerPhysics->setLinearVelocity(0.0f, 0.0f, 0.0f);
		ownerPhysics->activate();
		ownerPhysics->addForce(moveSpeed * force.x, moveSpeed * force.y, moveSpeed * force.z);
	}
}
