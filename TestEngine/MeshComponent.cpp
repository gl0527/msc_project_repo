#include "MeshComponent.h"

namespace Engine
{
	MeshComponent::MeshComponent(const std::string& eName, const std::string& mName)
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
		if(sceneMgr)
			sceneMgr->destroyEntity(objName);
	}


	void MeshComponent::setMaterial(const std::string& matName)
	{
		if(entity)
			entity->setMaterialName(matName);
	}


}

