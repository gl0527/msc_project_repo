#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC ParticleComponent : public RenderComponent
	{
		Ogre::ParticleSystem* partSys;
	public:
		ParticleComponent(const char* name, const char* partName);
		virtual ~ParticleComponent();

		virtual void onDestroy() override;
	};
}


