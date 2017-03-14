#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC MeshComponent : public RenderComponent
	{
		Ogre::Entity* entity;
		std::map<std::string, Ogre::AnimationState*> animations; // skeletonnal ez nem kell
	public:
		MeshComponent(const std::string& eName, const std::string& mName);
		virtual ~MeshComponent();

		virtual void onPostUpdate(float t, float dt) override;
		virtual void onDestroy() override;

		void addAnimationState(const char* animState);
		Ogre::AnimationState* getAnimationState(const char* animState) { return animations[animState]; }
		
		void disableAnimation(const char* animState);
		void enableAnimation(const char* animState);
		void setAnimationWeight(const char* animState, unsigned int weight);
		void setAnimationLoop(const char* animState, bool loop); // getter
		void setAnimationTimePosition(const char* animState, unsigned int time); // animation ended

		void setMaterial(const std::string& matName);
	};
}


