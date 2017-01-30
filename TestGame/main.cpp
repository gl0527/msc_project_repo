#include "TestEngine.h"
#include "InputComponent.h"
#include "FPSComponent.h"

using namespace Engine;

int main(int argc, char** argv)
{
	if (!Game::getInstance().init())
		return -1;

	TransformProcessor tp;

	XMLParser::getInstance().load("media/map/minath_tirith.xml");
	XMLParser::getInstance().process();

	Game::getInstance().getRenderSystem()->createPlaneMeshXZ("ground", 0, 10, 10);
	Ogre::RenderTexture* rtt = Game::getInstance().getRenderSystem()->createTexture("sepia", 100, 100)->getBuffer()->getRenderTarget();

	GameObject* mainCamera = ObjectManager::getInstance().createGameObject("mainCamera");
	mainCamera->getTransform()->setPosition(Ogre::Vector3(0.0f, 400.0f, 0.0f));
	mainCamera->getTransform()->setRotation(Ogre::Quaternion(Ogre::Radian(-Ogre::Math::PI / 4), Ogre::Vector3::UNIT_X));
	//CameraComponent* cameraComponent = new CameraComponent("mainCamera", 0.0f);
	//mainCamera->addComponent(cameraComponent);
	TPCameraComponent* tpCam = new TPCameraComponent("tpCam", 0);
	//tpCam->setRenderTexture(rtt);
	mainCamera->addComponent(tpCam);
	InputComponent* inputComponent = new InputComponent("input");
	mainCamera->addComponent(inputComponent);

	GameObject* archway = ObjectManager::getInstance().createGameObject("archway");
	archway->getTransform()->setPosition(Ogre::Vector3(0.0f, 0.0f, -550.0f));
	archway->getTransform()->setScale(Ogre::Vector3(1.5f, 1.5f, 1.5f));
	RenderComponent* renderer = new MeshComponent("aw", "Archway.mesh");
	archway->addComponent(renderer);
	//archway->addComponent(tpCam);

	for (int i = 10; i < 60; ++i)
	{
		GameObject* box = ObjectManager::getInstance().createGameObject("box" + Ogre::StringConverter::toString(i));
		box->getTransform()->setPosition(Ogre::Vector3(-20.0f, 10*i + 30.0f, -500.0f));
		box->getTransform()->setScale(Ogre::Vector3(10, 10, 10));
		RenderComponent* boxRenderer = new MeshComponent(box->getName().c_str(), "doboz.mesh");
		AudioComponent* boxAudio = new AudioComponent("media/sound/human_dead.wav", mainCamera);
		PhysicsComponent* boxCollider = new PhysicsComponent("box", 1.0f, PhysicsComponent::DYNAMIC);
		boxCollider->setOnCollision([](PhysicsComponent* other)
		{
			GameObject* otherObject = other->getOwnerObject();
			if (otherObject->getName() == "ground")
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

	GameObject* ball = ObjectManager::getInstance().createGameObject("ball");
	ball->getTransform()->setPosition(Ogre::Vector3(-50.0f, 400.0f, -500.0f));
	ball->getTransform()->setScale(Ogre::Vector3(10, 10, 10));
	RenderComponent* ballRenderer = new MeshComponent("ball", "strippedBall.mesh");
	PhysicsComponent* ballCollider = new PhysicsComponent("ball", 1.0f, PhysicsComponent::DYNAMIC);
	btCollisionShape* ballShape = new btSphereShape(10);
	ballCollider->addShape(ballShape);
	ball->addComponent(ballRenderer);
	ball->addComponent(ballCollider);
	ballCollider->setRestitution(0.9f);

	/*tpCam->setTargetHeight(30.0f);
	ball->addComponent(tpCam);*/

	GameObject* ball2 = ObjectManager::getInstance().createGameObject("ball2");
	ball2->getTransform()->setPosition(Ogre::Vector3(-1.0f, 0.0f, -2.0f));
	ball2->getTransform()->setScale(Ogre::Vector3(2, 2, 2));
	RenderComponent* ball2Renderer = new MeshComponent("ball2", "strippedBall.mesh");
	BillboardComponent* ball2bb = new BillboardComponent("bb");
	ball2bb->getBillboardSet()->setBillboardType(Ogre::BBT_PERPENDICULAR_SELF);
	ball2bb->getBillboardSet()->setMaterialName("TreeLeaves");
	ball2bb->getBillboardSet()->setSortingEnabled(true);

	for (int i = 0; i < 10; i++)
	{
		float h = Ogre::Math::RangeRandom(5, 10);
		Ogre::Vector3 pos(0, h, 0);
		Ogre::Vector3 dir(Ogre::Math::RangeRandom(-0.6f, 0.6f), 1, Ogre::Math::RangeRandom(-0.6f, 0.6f));
		dir.normalise();
		Ogre::Billboard* bb = ball2bb->getBillboardSet()->createBillboard(pos);
		bb->setDimensions(15.0f - h, 15.0f - h);
		bb->mDirection = dir;
	}

	ball2->addComponent(ball2Renderer);
	ball2->addComponent(ball2bb);

	// ha mind a kettonek van fizikai komponense, akkor nem mukodik
	ball2->setParent(ball);
	GameObject* triggerObject = ObjectManager::getInstance().createGameObject("trigger");
	triggerObject->getTransform()->setPosition(Ogre::Vector3(-50.0f, 0.0f, -500.0f));
	triggerObject->getTransform()->setScale(Ogre::Vector3(30.0f, 30.0f, 30.0f));
	RenderComponent* triggerRenderer = new MeshComponent("triggerRenderer", "explosive.mesh");
	ParticleComponent* triggerParticle = new ParticleComponent("dragonfire", "DragonFire");
	PhysicsComponent* triggerCollider = new PhysicsComponent("trigger", 100.0f, PhysicsComponent::KINEMATIC);
	btCollisionShape* triggerShape = new btBoxShape(btVector3(15, 30, 15));
	triggerCollider->addShape(triggerShape);
	triggerCollider->setOnTriggerEnter([](PhysicsComponent* other){ other->addForce(100, 1000, 0); });
	triggerObject->addComponent(triggerRenderer);
	triggerObject->addComponent(triggerParticle);
	triggerObject->addComponent(triggerCollider);
	triggerCollider->setTrigger(true);

	GameObject* ground = ObjectManager::getInstance().createGameObject("ground");
	ground->getTransform()->setScale(Ogre::Vector3(3000.0f, 0.1f, 3000.0f));
	MeshComponent* groundRender = new MeshComponent("mainGround", "ground");
	PhysicsComponent* groundCollider = new PhysicsComponent("ground", 0.0f, PhysicsComponent::STATIC);
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	groundCollider->addShape(groundShape);
	groundRender->setCastShadows(false);
	groundRender->setMaterial("Ground");
	ground->addComponent(groundRender);
	ground->addComponent(groundCollider);
	groundCollider->getRigidBody()->setRestitution(1.0f);
	AudioComponent* groundAudio = new AudioComponent("media/sound/main_theme.wav", mainCamera);
	ground->addComponent(groundAudio);
	groundAudio->play(0.5f, 1.0f, true); // ezt egy esemenykezelobe kellene tenni

	GameObject* fps = ObjectManager::getInstance().createGameObject("fps");
	FPSComponent* fpsc = new FPSComponent("FPS");
	fps->addComponent(fpsc);
	
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