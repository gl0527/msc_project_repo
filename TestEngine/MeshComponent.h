#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC MeshComponent : public RenderComponent
	{
		Ogre::Entity* entity;
		std::vector<Ogre::AnimationState*> animations;
	public:
		MeshComponent(const std::string& eName, const std::string& mName);
		virtual ~MeshComponent();

		virtual void onPostUpdate(float t, float dt) override;
		virtual void onDestroy() override;

		void setMaterial(const char* matName);
	};
}


