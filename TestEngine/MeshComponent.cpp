#include "MeshComponent.h"

namespace Engine
{
	MeshComponent::MeshComponent(const char* eName, const char* mName)
		: RenderComponent(eName),
		entity(nullptr)
	{
		entity = sceneMgr->createEntity(objName, mName);
		object = entity;
	}


	MeshComponent::~MeshComponent()
	{
	}


	void MeshComponent::onDestroy()
	{
		sceneMgr->destroyEntity(objName);
	}


	void MeshComponent::setMaterial(const char* matName)
	{
		entity->setMaterialName(matName);
	}


}

