#include "AnimationComponent.h"
#include "GameObject.h"
#include "MeshComponent.h"

namespace Engine
{
	AnimationComponent::AnimationComponent(const std::string& name, const Ogre::SkeletonAnimationBlendMode& blendMode)
		:Component(name),
		entity(nullptr),
		anim(nullptr),
		animBlend(blendMode)
	{
	}


	AnimationComponent::~AnimationComponent()
	{
	}


	void AnimationComponent::onStart()
	{
		const auto& ownerMesh = ownerObject->getFirstComponentByType<MeshComponent>();
		if (ownerMesh == nullptr)
			ownerObject->removeComponent(name);
		entity = ownerMesh->getEntity();
		if(entity)
			entity->getSkeleton()->setBlendMode(animBlend);
	}


	void AnimationComponent::stop()
	{
		if (entity)
		{
			if (anim)
				anim->setEnabled(false);
		}
	}


	void AnimationComponent::start(const std::string& animName)
	{
		if (entity)
		{
			anim = entity->getAnimationState(animName);
			if (anim)
				anim->setEnabled(true);
		}
	}


	void AnimationComponent::setWeight(unsigned int weight)
	{
		if (entity)
		{
			if (anim)
				anim->setWeight(weight);
		}
	}


	void AnimationComponent::setLoop(bool loop)
	{
		if (entity)
		{
			if (anim)
				anim->setLoop(loop);
		}
	}


	bool AnimationComponent::getLoop()
	{
		if (entity)
		{
			if (anim)
				return anim->getLoop();
		}
		return false;
	}


	void AnimationComponent::setTime(float time)
	{
		if (entity)
		{
			if (anim)
				anim->setTimePosition(time);
		}
	}


	void AnimationComponent::step(float time)
	{
		if (entity)
		{
			if (anim)
				anim->addTime(time);
		}
	}


	bool AnimationComponent::ended()
	{
		if (entity)
		{
			if (anim)
				return anim->hasEnded();
		}
		return false;
	}
}
