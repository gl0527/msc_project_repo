#include "MeshComponent.h"
#include "GameObject.h"

namespace Engine
{
	unsigned int MeshComponent::instanceCount = 0;

	MeshComponent::MeshComponent(const std::string& eName, const std::string& mName)
		: RenderComponent(eName),
		entity(nullptr),
		mesh(mName)
	{
		
	}


	MeshComponent::~MeshComponent()
	{
	}


	void MeshComponent::onInit(GameObject* obj)
	{
		entity = sceneMgr->createEntity(obj->getName() + Ogre::StringConverter::toString(instanceCount++), mesh);
		object = entity;
		RenderComponent::onInit(obj);
	}


	void MeshComponent::onDestroy()
	{
		if(sceneMgr)
			sceneMgr->destroyEntity(entity->getName());
	}


	void MeshComponent::setMaterial(const std::string& matName)
	{
		if(entity)
			entity->setMaterialName(matName);
	}


}

