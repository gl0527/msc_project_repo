#include "ParticleComponent.h"

namespace Engine
{
	ParticleComponent::ParticleComponent(const std::string& name, const std::string& partName)
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

