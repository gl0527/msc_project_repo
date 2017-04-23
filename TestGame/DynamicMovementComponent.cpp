#include "DynamicMovementComponent.h"
#include "GameObject.h"

DynamicMovementComponent::DynamicMovementComponent(const std::string& name)
	:Component(name),
	moveSpeed(10000.0f),
	inputHandler(nullptr),
	ownerPhysics(std::shared_ptr<PhysicsComponent>(nullptr)),
	ownerSoldierComp(std::shared_ptr<SoldierComponent>(nullptr))
{
}


DynamicMovementComponent::~DynamicMovementComponent()
{
}


void DynamicMovementComponent::onStart()
{
	inputHandler = Game::getInstance().getInputHandler();
	ownerPhysics = ownerObject->getFirstComponentByType<PhysicsComponent>();
	ownerSoldierComp = ownerObject->getFirstComponentByType<SoldierComponent>();
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
	{
		force += Ogre::Vector3(1.0f, 0.0f, 0.0f);
		if (auto& soldierComp = ownerSoldierComp.lock())
			soldierComp->setAction(SoldierComponent::PA_RUN);
	}
	if (inputHandler->isKeyDown(OIS::KC_A))
	{
		force += Ogre::Vector3(-1.0f, 0.0f, 0.0f);
		if (auto& soldierComp = ownerSoldierComp.lock())
			soldierComp->setAction(SoldierComponent::PA_RUN);
	}
	if (inputHandler->isKeyDown(OIS::KC_W))
	{
		force += Ogre::Vector3(0.0f, 0.0f, -1.0f);
		if (auto& soldierComp = ownerSoldierComp.lock())
			soldierComp->setAction(SoldierComponent::PA_RUN);
	}
	if (inputHandler->isKeyDown(OIS::KC_S))
	{
		force += Ogre::Vector3(0.0f, 0.0f, 1.0f);
		if (auto& soldierComp = ownerSoldierComp.lock())
			soldierComp->setAction(SoldierComponent::PA_RUN);
	}

	if (ms.buttonDown(OIS::MB_Left))
		if (auto& soldierComp = ownerSoldierComp.lock())
			soldierComp->setAction(SoldierComponent::PA_SHOOT);

	/*Ogre::Radian yaw(-0.003 * ms.X.rel);
	Ogre::Quaternion Qyaw(yaw, Ogre::Vector3::UNIT_Y);
	ownerObject->transform()->setRotation(Qyaw * ownerObject->transform()->rotation());

	const Ogre::Vector3& right = ownerObject->transform()->right();
	Ogre::Radian pitch(-0.003 * ms.Y.rel);
	Ogre::Quaternion Qpitch(pitch, right);
	ownerObject->transform()->setRotation(Qpitch * ownerObject->transform()->rotation());*/

	force.normalise();
	force = ownerObject->transform()->rotation() * force; // azert, hogy a movedir az ownerObject koordinata-rendszereben legyen ertve

	if (auto& phy = ownerPhysics.lock())
	{
		phy->setLinearVelocity(0.0f, 0.0f, 0.0f);
		phy->activate();
		phy->addForce(moveSpeed * force.x, moveSpeed * force.y, moveSpeed * force.z);
	}
}
