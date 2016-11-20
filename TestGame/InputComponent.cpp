#include "InputComponent.h"
#include "GameObject.h"

InputComponent::InputComponent() : Component(11), inputHandler(nullptr), moveSpeed(100.0f)
{
}


void InputComponent::onStart()
{
	inputHandler = Game::getInstance().getInputHandler();
}


void InputComponent::onPreUpdate(float t, float dt)
{
	Ogre::Vector3 moveDir = Ogre::Vector3::ZERO;

	if (inputHandler->isKeyDown(OIS::KC_W))
		moveDir += Ogre::Vector3(0.0f, 1.0f, -1.0f);
	if (inputHandler->isKeyDown(OIS::KC_S))
		moveDir += Ogre::Vector3(0.0f, -1.0f, 1.0f);
	if (inputHandler->isKeyDown(OIS::KC_D))
		moveDir += Ogre::Vector3(1.0f, 0.0f, 0.0f);
	if (inputHandler->isKeyDown(OIS::KC_A))
		moveDir += Ogre::Vector3(-1.0f, 0.0f, 0.0f);
	if (inputHandler->isKeyDown(OIS::KC_ADD))
		moveDir += Ogre::Vector3(0.0f, 0.0f, -1.0f);
	if (inputHandler->isKeyDown(OIS::KC_SUBTRACT))
		moveDir += Ogre::Vector3(0.0f, 0.0f, 1.0f);

	moveDir.normalise();
	moveDir = ownerObject->getOrientation() * moveDir; // azert, hogy a movedir az ownerObject koordinata-rendszereben legyen ertve
	
	ownerObject->setPosition(ownerObject->getPosition() + moveDir * dt * moveSpeed);
}


InputComponent::~InputComponent()
{
}
