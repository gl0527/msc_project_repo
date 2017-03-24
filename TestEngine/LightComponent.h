#pragma once
#include "Component.h"

namespace Engine
{
	class DLL_SPEC LightComponent : public Component
	{
		Ogre::SceneManager* sceneMgr;
		Ogre::Light* light;
		Ogre::Light::LightTypes type;
	public:
		LightComponent(const std::string& name, const Ogre::Light::LightTypes& t);
		~LightComponent() {}

		virtual void onDestroy() override;

		const Ogre::ColourValue& getDiffuseColor() const { return light->getDiffuseColour(); }
		const Ogre::ColourValue& getSpecularColor() const { return light->getSpecularColour(); }
		float getIntensity() const { return light->getPowerScale(); }
		float getAttenuationRange() const { return light->getAttenuationRange(); }
		float getConstantAttenuation() const { return light->getAttenuationConstant(); }
		float getLinearAttenuation() const { return light->getAttenuationLinear(); }
		float getQuadricAttenuation() const { return light->getAttenuationQuadric(); }
		const Ogre::Vector3& getPosition() const { return light->getPosition(); }
		const Ogre::Vector3& getDirection() const { return light->getDirection(); }
		
		void setDiffuseColor(const Ogre::ColourValue& diffuseColor) { light->setDiffuseColour(diffuseColor); }
		void setSpecularColor(const Ogre::ColourValue& specularColor) { light->setSpecularColour(specularColor); }
		void setIntensity(float intensity) { light->setPowerScale(intensity); }
		void setAttenuation(float range, float constant, float linear, float quadric) { light->setAttenuation(range, constant, linear, quadric); }
		void setPosition(const Ogre::Vector3& position);
		void setDirection(const Ogre::Vector3& direction);
	};
}