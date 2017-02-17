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
			it->second->addTime(dt);
	}


	void MeshComponent::onDestroy()
	{
		sceneMgr->destroyEntity(objName);
	}


	void MeshComponent::addAnimationState(const char* animState)
	{
		animations[animState] = entity->getAnimationState(animState);
		animations[animState]->setEnabled(true);
		animations[animState]->setWeight(1);
		animations[animState]->setLoop(true);
	}


	void MeshComponent::disableAnimation(const char* animState)
	{
		if (animations.find(animState) != animations.end())
			animations[animState]->setEnabled(false);
	}


	void MeshComponent::enableAnimation(const char* animState)
	{
		if (animations.find(animState) != animations.end())
			animations[animState]->setEnabled(true);
	}


	void MeshComponent::setAnimationWeight(const char* animState, unsigned int weight)
	{
		if (animations.find(animState) != animations.end())
			animations[animState]->setWeight(weight);
	}


	void MeshComponent::setAnimationLoop(const char* animState, bool loop)
	{
		if (animations.find(animState) != animations.end())
			animations[animState]->setLoop(loop);
	}
	
	
	void MeshComponent::setAnimationTimePosition(const char* animState, unsigned int time)
	{
		if (animations.find(animState) != animations.end())
			animations[animState]->setTimePosition(time);
	}


	void MeshComponent::setMaterial(const char* matName)
	{
		entity->setMaterialName(matName);
	}


}

