#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC ParticleComponent : public RenderComponent
	{
		static unsigned int instanceCount;
		Ogre::ParticleSystem* partSys;
		std::string particle;
	public:
		ParticleComponent(const std::string& name, const std::string& partName);
		virtual ~ParticleComponent();

		virtual void onInit(GameObject* obj) override;
		virtual void onDestroy() override;
	};
}


