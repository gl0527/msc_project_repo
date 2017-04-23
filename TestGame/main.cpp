#include "TestEngine.h"
#include "InputComponent.h"
#include "FPSComponent.h"
#include "InputProcessor.h"
#include "DynamicMovementComponent.h"
#include "SoldierComponent.h"

using namespace Engine;

int main(int argc, char** argv)
{
	auto& game = Game::getInstance();
	
	if (!game.init())
		return -1;

	new InputProcessor;

	auto renderSys = game.getRenderSystem();
	auto& xmlParser = XMLParser::getInstance();
	auto& objectMgr = ObjectManager::getInstance();

	renderSys->createPlaneMeshXZ("ground", 0, 10, 10);
	auto rtt = renderSys->createTexture("sepia", 100, 100)->getBuffer()->getRenderTarget();

	/*const auto& tree = objectMgr.createGameObject("tree");
	tree->transform()->setPosition(Ogre::Vector3(-30.0f, 0.0f, -900.0f));
	tree->transform()->setScale(Ogre::Vector3(5, 5, 5));
	std::shared_ptr<MeshComponent> ball2Renderer(new MeshComponent("treeTrunk", "treetrunk.mesh"));
	std::shared_ptr<BillboardComponent> ball2bb(new BillboardComponent("bboard"));
	ball2bb->getBillboardSet()->setBillboardType(Ogre::BBT_PERPENDICULAR_SELF);
	ball2bb->getBillboardSet()->setMaterialName("TreeLeaves");
	ball2bb->getBillboardSet()->setSortingEnabled(true);
	ball2bb->getBillboardSet()->setCastShadows(true);

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
	tree->addComponent(ball2bb);*/

	if (!xmlParser.load("media/map/test.xml"))
		return -1;

	if (auto& exp = objectMgr.getGameObject("explosive").lock())
	{
		if(auto& explosivePhysx = exp->getFirstComponentByType<PhysicsComponent>().lock())
			explosivePhysx->setOnTriggerEnter([&objectMgr, &exp](PhysicsComponent* other) { 
				if(const auto& explosiveAudio = exp->getFirstComponentByType<AudioComponent>().lock())
					explosiveAudio->play();
				objectMgr.removeGameObject(other->getOwnerObject()->getName());
			});
	}

	if (auto& sld = objectMgr.getGameObject("soldier").lock())
	{
		std::shared_ptr<DynamicMovementComponent> movement(new DynamicMovementComponent("dynamicMvmt"));
		std::shared_ptr<AnimationComponent> anim(new AnimationComponent("soldierAnimation", Ogre::ANIMBLEND_CUMULATIVE));
		std::shared_ptr<SoldierComponent> data(new SoldierComponent("soldierComp"));

		sld->addComponent(movement);
		sld->addComponent(anim);
		sld->addComponent(data);
	}
	
	if (auto& lvl = objectMgr.getGameObject("level").lock())
	{
		if(auto& levelSound = lvl->getFirstComponentByType<AudioComponent>().lock())
			levelSound->play();
	}

	if (auto& frames = objectMgr.createGameObject("fps").lock())
	{
		std::shared_ptr<FPSComponent> fpsc(new FPSComponent("FPS"));
		frames->addComponent(fpsc);
	}
	
	// setting up environment
	auto sceneMgr = renderSys->getSceneManager();

	sceneMgr->setAmbientLight(Ogre::ColourValue(0.1f, 0.1f, 0.1f, 1.0f)); // ez is kellene az xml-be
	//sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	//sceneMgr->setShadowColour(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
	sceneMgr->setSkyBox(true, "Sky");

	game.start();
	game.deleteInstance();

	return 0;
}