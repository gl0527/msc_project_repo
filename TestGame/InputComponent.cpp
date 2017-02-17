#include "InputComponent.h"
#include "GameObject.h"

InputComponent::InputComponent(const std::string& ident) :
	Component(ident),
	inputHandler(nullptr),
	moveSpeed(50.0f),
	turnSpeed(0.001f),
	mouseSensitivity(50.0f),
	delay(0),
	maxDelay(20)
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
	if (inputHandler->isKeyDown(OIS::KC_SYSRQ) && delay > maxDelay)
	{
		std::cout << "Screenshot taken.\n";
		Game::getInstance().getRenderSystem()->getRenderWindow()->writeContentsToTimestampedFile("screenshot", ".jpg");
		delay = 0;
	}
		
	if (ms.buttonDown(OIS::MB_Left))
		std::cout << "lmb: " << ms.X.abs << ", " << ms.Y.abs << std::endl;
	if (ms.buttonDown(OIS::MB_Right))
		std::cout << "rmb: " << ms.X.rel << ", " << ms.Y.rel << std::endl;
	
	/*if (ms.X.rel != 0 && ms.Y.rel != 0)
	{
		Ogre::Radian yaw(-turnSpeed * ms.X.rel);
		Ogre::Quaternion Qyaw(yaw, Ogre::Vector3::UNIT_Y);
		ownerObject->getTransform()->setRotation(Qyaw * ownerObject->getTransform()->getRotation());

		const Ogre::Vector3& right = ownerObject->getTransform()->getRight();
		Ogre::Radian pitch(-turnSpeed * ms.Y.rel);
		Ogre::Quaternion Qpitch(pitch, right);
		ownerObject->getTransform()->setRotation(Qpitch * ownerObject->getTransform()->getRotation());
	}*/

	moveDir.normalise();
	moveDir = ownerObject->transform()->rotation() * moveDir; // azert, hogy a movedir az ownerObject koordinata-rendszereben legyen ertve
	
	ownerObject->transform()->setPosition(ownerObject->transform()->position() + moveDir * dt * moveSpeed); // a dt miatt a mozgas sebessege fuggetlen a gep sebessegetol
}


InputComponent::~InputComponent()
{
}
