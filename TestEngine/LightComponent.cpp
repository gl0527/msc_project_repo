#include "LightComponent.h"
#include "GameObject.h"

namespace Engine
{
	LightComponent::LightComponent(const std::string & name, const Ogre::Light::LightTypes & t)
		:Component(name),
		sceneMgr(Game::getInstance().getRenderSystem()->getSceneManager()),
		light(sceneMgr->createLight(name)),
		type(t)
	{
		light->setType(type);
	}


	void LightComponent::onDestroy()
	{
		if(sceneMgr)
			sceneMgr->destroyLight(name);
	}


	void LightComponent::setPosition(const Ogre::Vector3& position)
	{
		if (light)
		{
			if(ownerObject)
				light->setPosition(ownerObject->transform()->position() + position);
			else
				light->setPosition(position);
		}
	}


	void LightComponent::setDirection(const Ogre::Vector3& direction)
	{
		if (light)
		{
			light->setDirection(direction);
		}
	}
}
