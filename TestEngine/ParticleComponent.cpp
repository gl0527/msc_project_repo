#include "ParticleComponent.h"
#include "GameObject.h"

namespace Engine
{
	unsigned int ParticleComponent::instanceCount = 0;

	ParticleComponent::ParticleComponent(const std::string& name, const std::string& partName)
		: RenderComponent(name),
		partSys(nullptr),
		particle(partName)
	{
		
	}


	ParticleComponent::~ParticleComponent()
	{
	}


	void ParticleComponent::onInit(GameObject* obj)
	{
		partSys = sceneMgr->createParticleSystem(obj->getName() + Ogre::StringConverter::toString(instanceCount++), particle);
		object = partSys;
		RenderComponent::onInit(obj);
	}


	void ParticleComponent::onDestroy()
	{
		sceneMgr->destroyParticleSystem(partSys->getName());
	}


}

