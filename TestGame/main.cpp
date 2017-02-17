#include "TestEngine.h"
#include "InputComponent.h"
#include "FPSComponent.h"
#include "InputProcessor.h"

using namespace Engine;

int main(int argc, char** argv)
{
	if (!Game::getInstance().init())
		return -1;

	TransformProcessor tp;
	//CameraProcessor cp;
	TPCameraProcessor tpcp;
	InputProcessor ip;
	MeshProcessor mp;
	PhysicsProcessor pp;

	Game::getInstance().getRenderSystem()->createPlaneMeshXZ("ground", 0, 10, 10);
	Ogre::RenderTexture* rtt = Game::getInstance().getRenderSystem()->createTexture("sepia", 100, 100)->getBuffer()->getRenderTarget();

	XMLParser::getInstance().load("media/map/minath_tirith.xml");
	XMLParser::getInstance().process();

	GameObject* ball = ObjectManager::getInstance().createGameObject("ball");
	ball->transform()->setPosition(Ogre::Vector3(-50.0f, 400.0f, -500.0f));
	ball->transform()->setScale(Ogre::Vector3(10, 10, 10));
	RenderComponent* ballRenderer = new MeshComponent("ball", "strippedBall.mesh");
	PhysicsComponent* ballCollider = new PhysicsComponent("ball", 1.0f, PhysicsComponent::DYNAMIC);
	btCollisionShape* ballShape = new btSphereShape(10);
	ballCollider->addShape(ballShape);
	ball->addComponent(ballRenderer);
	ball->addComponent(ballCollider);
	ballCollider->setRestitution(0.9f);

	GameObject* ball2 = ObjectManager::getInstance().createGameObject("ball2");
	ball2->transform()->setPosition(Ogre::Vector3(-1.0f, 0.0f, -2.0f));
	ball2->transform()->setScale(Ogre::Vector3(2, 2, 2));
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
	triggerObject->transform()->setPosition(Ogre::Vector3(-50.0f, 0.0f, -500.0f));
	triggerObject->transform()->setScale(Ogre::Vector3(30.0f, 30.0f, 30.0f));
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
	Game::getInstance().getRenderSystem()->getSceneManager()->setSkyBox(true, "Sunrise");

	Game::getInstance().start();
	Game::getInstance().deleteInstance();

	return 0;
}