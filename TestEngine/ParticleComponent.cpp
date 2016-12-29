#include "ParticleComponent.h"

namespace Engine
{
	ParticleComponent::ParticleComponent(const char* name, const char* partName)
		: RenderComponent(name),
		partSys(nullptr)
	{
		partSys = sceneMgr->createParticleSystem(name, partName);
		object = partSys;
	}


	ParticleComponent::~ParticleComponent()
	{
	}


	void ParticleComponent::onDestroy()
	{
		sceneMgr->destroyParticleSystem(objName);
	}


}

