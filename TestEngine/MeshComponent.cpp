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


	void MeshComponent::onPostUpdate(float t, float dt)
	{
		RenderComponent::onPostUpdate(t, dt);
		for (auto&& it = animations.cbegin(); it != animations.cend(); ++it)
			(*it)->addTime(dt);
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

