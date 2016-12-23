#include "TestEngine.h"
#include "InputComponent.h"

using namespace Engine;

int main(int argc, char** argv)
{
	if (!Game::getInstance().init())
		return -1;

	GameObject* mainCamera = ObjectManager::getInstance().createGameObject(0);
	mainCamera->setPosition(Ogre::Vector3(0.0f, 400.0f, 0.0f));
	mainCamera->setOrientation(Ogre::Quaternion(Ogre::Radian(-Ogre::Math::PI / 4), Ogre::Vector3::UNIT_X));
	CameraComponent* cameraComponent = new CameraComponent("mainCamera", 0.0f);
	mainCamera->addComponent(cameraComponent);
	InputComponent* inputComponent = new InputComponent();
	mainCamera->addComponent(inputComponent);

	GameObject* archway = ObjectManager::getInstance().createGameObject(1);
	archway->setPosition(Ogre::Vector3(0.0f, 0.0f, -550.0f));
	archway->setScale(Ogre::Vector3(1.5f, 1.5f, 1.5f));
	RenderComponent* renderer = new RenderComponent("aw", "Archway.mesh");
	archway->addComponent(renderer);

	for (int i = 10; i < 50; ++i)
	{
		GameObject* box = ObjectManager::getInstance().createGameObject(200+i);
		box->setPosition(Ogre::Vector3(-20.0f, 4*i + 10, -500.0f));
		box->setScale(Ogre::Vector3(10, 10, 10));
		std::string s = "box" + Ogre::StringConverter::toString(i);
		RenderComponent* boxRenderer = new RenderComponent(s.c_str(), "doboz.mesh");
		AudioComponent* boxAudio = new AudioComponent("media/sound/human_dead.wav", mainCamera);
		PhysicsComponent* boxCollider = new PhysicsComponent(1.0f, PhysicsComponent::DYNAMIC);
		boxCollider->setOnCollision([](PhysicsComponent* other)
		{
			GameObject* otherObject = other->getOwnerObject();
			if (otherObject->getID() == 3)
				return;
			if (AudioComponent* otherAC = other->getOwnerObject()->getFirstComponentByType<AudioComponent>())
				otherAC->play(1.0f, 1.0f, false);
			
		});
		btCollisionShape* cs = new btBoxShape(btVector3(5, 5, 5));
		boxCollider->addShape(cs);
		box->addComponent(boxRenderer);
		box->addComponent(boxCollider);
		box->addComponent(boxAudio);
	}

	GameObject* ball = ObjectManager::getInstance().createGameObject(10);
	ball->setPosition(Ogre::Vector3(-50.0f, 400.0f, -500.0f));
	ball->setScale(Ogre::Vector3(10, 10, 10));
	RenderComponent* ballRenderer = new RenderComponent("ball", "strippedBall.mesh");
	PhysicsComponent* ballCollider = new PhysicsComponent(1.0f, PhysicsComponent::DYNAMIC);
	btCollisionShape* ballShape = new btSphereShape(10);
	ballCollider->addShape(ballShape);
	ball->addComponent(ballRenderer);
	ball->addComponent(ballCollider);
	ballCollider->setRestitution(0.9f);

	GameObject* ball2 = ObjectManager::getInstance().createGameObject(11);
	ball2->setPosition(Ogre::Vector3(-1.0f, 0.0f, -2.0f));
	ball2->setScale(Ogre::Vector3(2, 2, 2));
	RenderComponent* ball2Renderer = new RenderComponent("ball2", "strippedBall.mesh");
	ball2->addComponent(ball2Renderer);

	// ha mind a kettonek van fizikai komponense, akkor nem mukodik
	ball->addChild(ball2); // igy az iment megadott transzformacios ertekek a szulohoz kepest relativen ertendok

	GameObject* triggerObject = ObjectManager::getInstance().createGameObject(100);
	triggerObject->setPosition(Ogre::Vector3(-50.0f, 0.0f, -500.0f));
	triggerObject->setScale(Ogre::Vector3(30.0f, 30.0f, 30.0f));
	RenderComponent* triggerRenderer = new RenderComponent("triggerRenderer", "explosive.mesh");
	PhysicsComponent* triggerCollider = new PhysicsComponent(100.0f, PhysicsComponent::KINEMATIC);
	btCollisionShape* triggerShape = new btBoxShape(btVector3(15, 30, 15));
	triggerCollider->addShape(triggerShape);
	triggerCollider->setOnTriggerEnter([](PhysicsComponent* other){ other->addForce(100, 1000, 0); });
	triggerObject->addComponent(triggerRenderer);
	triggerObject->addComponent(triggerCollider);
	triggerCollider->setTrigger(true);

	Game::getInstance().getRenderSystem()->createPlaneMeshXZ("ground", 0, 20, 20);

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
	groundCollider->getRigidBody()->setRestitution(1.0f);
	AudioComponent* groundAudio = new AudioComponent("media/sound/main_theme.wav", mainCamera);
	ground->addComponent(groundAudio);
	groundAudio->play(0.5f, 1.0f, true); // ezt egy esemenykezelobe kellene tenni
	
	// setting up environment
	Ogre::Light* mainLight = Game::getInstance().getRenderSystem()->getSceneManager()->createLight("mainlight");
	mainLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mainLight->setDirection(-1.0f, -1.0f, -1.0f);

	Game::getInstance().getRenderSystem()->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.3f, 0.3f, 0.3f, 1.0f));
	Game::getInstance().getRenderSystem()->getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	Game::getInstance().getRenderSystem()->getSceneManager()->setShadowColour(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
	Game::getInstance().getRenderSystem()->getSceneManager()->setSkyBox(true, "Sky", 500.0f);

	Game::getInstance().start();
	Game::getInstance().deleteInstance();

	return 0;
}