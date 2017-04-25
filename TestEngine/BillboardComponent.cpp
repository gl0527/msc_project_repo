#include "BillboardComponent.h"
#include "GameObject.h"

namespace Engine
{
	unsigned int BillboardComponent::instanceCount = 0;

	BillboardComponent::BillboardComponent(const std::string& bbName)
		: RenderComponent(bbName),
		billboardSet(nullptr)
	{
		
	}


	BillboardComponent::~BillboardComponent()
	{
	}


	void BillboardComponent::onInit(GameObject* obj)
	{
		billboardSet = sceneMgr->createBillboardSet(obj->getName() + Ogre::StringConverter::toString(instanceCount++));
		object = billboardSet;
		RenderComponent::onInit(obj);
	}


	void BillboardComponent::onDestroy()
	{
		sceneMgr->destroyBillboardSet(billboardSet->getName());
	}


}

