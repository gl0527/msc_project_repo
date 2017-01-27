#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC ParticleComponent : public RenderComponent
	{
		Ogre::ParticleSystem* partSys;
	public:
		ParticleComponent(const std::string& name, const std::string& partName);
		virtual ~ParticleComponent();

		virtual void onDestroy() override;
	};
}


