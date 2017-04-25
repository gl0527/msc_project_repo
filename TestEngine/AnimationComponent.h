#pragma once
#include "Component.h"

namespace Engine
{
	class DLL_SPEC AnimationComponent : public Component
	{
		bool hasSkeleton;
		Ogre::Entity* entity;
		Ogre::AnimationState* anim;
		Ogre::SkeletonAnimationBlendMode animBlend;
	public:
		AnimationComponent(const std::string& name, const Ogre::SkeletonAnimationBlendMode& blendMode);
		~AnimationComponent();

		virtual void onStart() override;

		void init(const std::string& animName);
		void start();
		void setEnabled(bool enable);
		void stop();
		void setWeight(unsigned int weight);
		void setLoop(bool loop);
		bool getLoop();
		void setTime(float time);
		void step(float time);
		bool ended();
	};
}