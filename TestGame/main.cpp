#include "TestEngine.h"
#include "InputComponent.h"
#include "FPSComponent.h"
#include "InputProcessor.h"

using namespace Engine;

int main(int argc, char** argv)
{
	auto& game = Game::getInstance();
	
	if (!game.init())
		return -1;

	TransformProcessor tp;
	//CameraProcessor cp;
	TPCameraProcessor tpcp;
	InputProcessor ip;
	MeshProcessor mp;
	PhysicsProcessor pp;
	GameObjectProcessor gp;
	AudioProcessor ap;
	ParticleProcessor partp;

	auto renderSys = game.getRenderSystem();
	auto& xmlParser = XMLParser::getInstance();
	auto& objectMgr = ObjectManager::getInstance();

	renderSys->createPlaneMeshXZ("ground", 0, 10, 10);
	auto rtt = renderSys->createTexture("sepia", 100, 100)->getBuffer()->getRenderTarget();

	xmlParser.load("media/map/minath_tirith.xml");
	xmlParser.process();

	const auto& ball = objectMgr.getGameObject("ball");
	if (ball)
	{
		auto ballAudio = ball->getFirstComponentByType<AudioComponent>();
		if(ballAudio)
			ballAudio->play();
	}

	const auto& explosive = objectMgr.getGameObject("explosive");
	if (explosive)
	{
		auto explosivePhysx = explosive->getFirstComponentByType<PhysicsComponent>();
		if(explosivePhysx)
			explosivePhysx->setOnTriggerEnter([&objectMgr](PhysicsComponent* other) { 
				other->addForce(1000, 10000, 0);
				objectMgr.removeGameObject(other->getOwnerObject()->getName());
			});
	}

	const auto& sold = objectMgr.getGameObject("soldier");
	auto soldMesh = sold->getFirstComponentByType<MeshComponent>();
	if (soldMesh)
	{
		auto soldierNode = soldMesh->getNode();
		Ogre::Quaternion q(Ogre::Radian(Ogre::Math::PI), Ogre::Vector3::UNIT_Y);
		soldierNode->rotate(q);
	}

	const auto& tree = objectMgr.createGameObject("tree");
	tree->transform()->setPosition(Ogre::Vector3(-30.0f, 0.0f, -900.0f));
	tree->transform()->setScale(Ogre::Vector3(5, 5, 5));
	std::shared_ptr<MeshComponent> ball2Renderer(new MeshComponent("treeTrunk", "treetrunk.mesh"));
	std::shared_ptr<BillboardComponent> ball2bb(new BillboardComponent("bboard"));
	ball2bb->getBillboardSet()->setBillboardType(Ogre::BBT_PERPENDICULAR_SELF);
	ball2bb->getBillboardSet()->setMaterialName("TreeLeaves");
	ball2bb->getBillboardSet()->setSortingEnabled(true);

	for (int i = 0; i < 10; i++)
	{
		float h = Ogre::Math::RangeRandom(30, 60);
		Ogre::Vector3 pos(0, h, 0);
		Ogre::Vector3 dir(Ogre::Math::RangeRandom(-0.6f, 0.6f), 1, Ogre::Math::RangeRandom(-0.6f, 0.6f));
		dir.normalise();
		auto bb = ball2bb->getBillboardSet()->createBillboard(pos);
		bb->setDimensions(90.0f - h, 90.0f - h);
		bb->mDirection = dir;
	}

	tree->addComponent(ball2Renderer);
	tree->addComponent(ball2bb);

	const auto& fps = objectMgr.createGameObject("fps");
	std::shared_ptr<FPSComponent> fpsc(new FPSComponent("FPS"));
	fps->addComponent(fpsc);
	
	// setting up environment
	auto mainLight = renderSys->getSceneManager()->createLight("mainlight");
	mainLight->setType(Ogre::Light::LT_DIRECTIONAL);
	mainLight->setDirection(-1.0f, -1.0f, -1.0f);

	auto sceneMgr = renderSys->getSceneManager();

	sceneMgr->setAmbientLight(Ogre::ColourValue(0.1f, 0.1f, 0.1f, 1.0f));
	sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	sceneMgr->setShadowColour(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
	sceneMgr->setSkyBox(true, "Sunrise");

	game.start();
	game.deleteInstance();

	return 0;
}