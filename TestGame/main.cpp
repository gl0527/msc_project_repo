#include "TestEngine.h"
#include <memory>

using namespace Engine;

int main(int argc, char** argv)
{
	if (!Game::getInstance().init())
		return -1;

	GameObject* mainCamera = ObjectManager::getInstance().createGameObject(0);
	mainCamera->setPosition(Ogre::Vector3(0.0f, 200.0f, 50.0f));
	mainCamera->setOrientation(Ogre::Quaternion(Ogre::Radian(-Ogre::Math::PI / 5), Ogre::Vector3::UNIT_X));
	CameraComponent* cameraComponent = new CameraComponent("mainCamera", 0.0f);
	mainCamera->addComponent(cameraComponent);

	GameObject* archway = ObjectManager::getInstance().createGameObject(1);
	archway->setPosition(Ogre::Vector3(0.0f, 0.0f, -250.0f));
	archway->setScale(Ogre::Vector3(1.5f, 1.5f, 1.5f));
	RenderComponent* renderComponent = new RenderComponent("aw", "Archway.mesh");
	archway->addComponent(renderComponent);

	GameObject* box = ObjectManager::getInstance().createGameObject(2);
	box->setPosition(Ogre::Vector3(0.0f, 50.0f, -200.0f));
	box->setScale(Ogre::Vector3(10, 10, 10));
	RenderComponent* boxRenderer = new RenderComponent("box1", "doboz.mesh");
	PhysicsComponent* boxCollider = new PhysicsComponent(1.0f, PhysicsComponent::DYNAMIC);
	btCollisionShape* cs = new btBoxShape(btVector3(5,5,5));
	boxCollider->addShape(cs);
	box->addComponent(boxRenderer);
	box->addComponent(boxCollider);

	GameObject* ball = ObjectManager::getInstance().createGameObject(10);
	ball->setPosition(Ogre::Vector3(10.0f, 100.0f, -190.0f));
	ball->setScale(Ogre::Vector3(10, 10, 10));
	RenderComponent* ballRenderer = new RenderComponent("ball", "strippedBall.mesh");
	PhysicsComponent* ballCollider = new PhysicsComponent(1.0f, PhysicsComponent::DYNAMIC);
	btCollisionShape* ballShape = new btSphereShape(10);
	ballCollider->addShape(ballShape);
	ball->addComponent(ballRenderer);
	ball->addComponent(ballCollider);

	Game::getInstance().getRenderSystem()->createPlaneXZ("ground", 50, 50);

	GameObject* ground = ObjectManager::getInstance().createGameObject(3);
	ground->setScale(Ogre::Vector3(5000.0f, 0.0f, 5000.0f));
	RenderComponent* groundRender = new RenderComponent("mainGround", "ground");
	PhysicsComponent* groundCollider = new PhysicsComponent(0.0f, PhysicsComponent::STATIC);
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	groundCollider->addShape(groundShape);
	groundRender->getEntity()->setCastShadows(false);
	groundRender->getEntity()->setMaterialName("Ground");
	ground->addComponent(groundRender);
	ground->addComponent(groundCollider);

	// setting up environment
	Ogre::Light* mainLight = Game::getInstance().getRenderSystem()->getSceneManager()->createLight("mainlight");
	mainLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mainLight->setDirection(-1.0f, -1.0f, -1.0f);

	Game::getInstance().getRenderSystem()->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.3f, 0.3f, 0.3f, 1.0f));
	Game::getInstance().getRenderSystem()->getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	Game::getInstance().getRenderSystem()->getSceneManager()->setShadowColour(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
	Game::getInstance().getRenderSystem()->getSceneManager()->setSkyBox(true, "Sky", 500.0f);
	
	Game::getInstance().start();

	return 0;
}