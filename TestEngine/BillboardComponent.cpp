#include "BillboardComponent.h"
#include "GameObject.h"

namespace Engine
{
	BillboardComponent::BillboardComponent(const std::string& bbName)
		: RenderComponent(bbName),
		billboardSet(nullptr)
	{
		billboardSet = sceneMgr->createBillboardSet(bbName);
		object = billboardSet;
	}


	BillboardComponent::~BillboardComponent()
	{
	}


	void BillboardComponent::onDestroy()
	{
		sceneMgr->destroyBillboardSet(objName);
	}


}

