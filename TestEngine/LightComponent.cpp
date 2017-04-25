#include "LightComponent.h"
#include "GameObject.h"

namespace Engine
{
	unsigned int LightComponent::instanceCount = 0;

	LightComponent::LightComponent(const std::string& name, const Ogre::Light::LightTypes& t)
		: Component(name),
		sceneMgr(Game::getInstance().getRenderSystem()->getSceneManager()),
		light(nullptr),
		type(t)
	{
		
	}


	void LightComponent::onInit(GameObject* object)
	{
		ownerObject = object;
		light = sceneMgr->createLight(object->getName() + Ogre::StringConverter::toString(instanceCount++));
		if (light)
			light->setType(type);
	}


	void LightComponent::onPostUpdate(float t, float dt)
	{
		auto ownerTransform = ownerObject->transform();

		if (type != Ogre::Light::LT_DIRECTIONAL)
			light->setPosition(ownerTransform->position());
		if (type != Ogre::Light::LT_POINT)
			light->setDirection(ownerTransform->forward());
	}


	void LightComponent::onDestroy()
	{
		if(sceneMgr)
			sceneMgr->destroyLight(light->getName());
	}


	float LightComponent::getAttenuationRange() const
	{
		if (type != Ogre::Light::LT_DIRECTIONAL)
			return light->getAttenuationRange();
		else
		{
			std::cout << "Directional light has no attenuation!\n";
			return 0.0f;
		}
	}
	
	
	float LightComponent::getConstantAttenuation() const
	{
		if (type != Ogre::Light::LT_DIRECTIONAL)
			return light->getAttenuationConstant(); 
		else
		{
			std::cout << "Directional light has no attenuation!\n";
			return 0.0f;
		}
	}


	float LightComponent::getLinearAttenuation() const 
	{
		if (type != Ogre::Light::LT_DIRECTIONAL)
			return light->getAttenuationLinear(); 
		else
		{
			std::cout << "Directional light has no attenuation!\n";
			return 0.0f;
		}
	}


	float LightComponent::getQuadricAttenuation() const 
	{
		if (type != Ogre::Light::LT_DIRECTIONAL)
			return light->getAttenuationQuadric();
		else
		{
			std::cout << "Directional light has no attenuation!\n";
			return 0.0f;
		}
	}


	const Ogre::Vector3& LightComponent::getPosition() const
	{
		if (type != Ogre::Light::LT_DIRECTIONAL)
			return light->getPosition(); 
		else
		{
			std::cout << "Directional light has no position!\n";
			return Ogre::Vector3::ZERO;
		}
	}


	const Ogre::Vector3& LightComponent::getDirection() const
	{
		if (type != Ogre::Light::LT_POINT)
			return light->getDirection();
		else
		{
			std::cout << "Point light has no direction!\n";
			return Ogre::Vector3::ZERO;
		}
	}


	void LightComponent::setAttenuation(float range, float constant, float linear, float quadric)
	{
		if (type != Ogre::Light::LT_DIRECTIONAL)
			light->setAttenuation(range, constant, linear, quadric);
	}


	void LightComponent::setSpotRange(Ogre::Degree innerAngle, Ogre::Degree outerAngle)
	{
		if (type == Ogre::Light::LT_SPOTLIGHT)
			light->setSpotlightRange(innerAngle, outerAngle);
	}
}
