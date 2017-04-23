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
		if (auto& ownerMesh = ownerObject->getFirstComponentByType<MeshComponent>().lock())
		{
			entity = ownerMesh->getEntity();
			if (entity)
				entity->getSkeleton()->setBlendMode(animBlend);
		}
		else
			ownerObject->removeComponent(name);
	}


	void AnimationComponent::stop()
	{
		if (entity)
		{
			if (anim)
				anim->setEnabled(false);
		}
	}


	void AnimationComponent::init(const std::string& animName)
	{
		if (entity)
			anim = entity->getAnimationState(animName);
	}


	void AnimationComponent::start()
	{
		if (entity)
		{
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
