#include "InputComponent.h"
#include "GameObject.h"

InputComponent::InputComponent() : Component(11), inputHandler(nullptr), moveSpeed(200.0f), delay(0), maxDelay(10)
{
}


void InputComponent::onStart()
{
	inputHandler = Game::getInstance().getInputHandler();
}


void InputComponent::onPreUpdate(float t, float dt)
{	
	const OIS::MouseState& ms = inputHandler->getMouseState();
	Ogre::Vector3 moveDir = Ogre::Vector3::ZERO;
	++delay;

	if (inputHandler->isKeyDown(OIS::KC_ESCAPE))
	{
		Game::getInstance().destroy();
		return;
	}
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
	if (inputHandler->isKeyDown(OIS::KC_SPACE) && delay > maxDelay)
	{
		std::cout << "space is pressed.\n";
		delay = 0;
	}
		
	if (ms.buttonDown(OIS::MB_Left))
		std::cout << "lmb: " << ms.X.abs << ", " << ms.Y.abs << std::endl;
	if (ms.buttonDown(OIS::MB_Right))
		std::cout << "rmb: " << ms.X.rel << ", " << ms.Y.rel << std::endl;

	moveDir.normalise();
	moveDir = ownerObject->getOrientation() * moveDir; // azert, hogy a movedir az ownerObject koordinata-rendszereben legyen ertve
	
	ownerObject->setPosition(ownerObject->getPosition() + moveDir * dt * moveSpeed); // a dt miatt a mozgas sebessege fuggetlen a gep sebessegetol
}


InputComponent::~InputComponent()
{
}
