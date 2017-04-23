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

		virtual void onPostUpdate(float t, float dt) override;
		virtual void onDestroy() override;

		const Ogre::ColourValue& getDiffuseColor() const { return light->getDiffuseColour(); }
		const Ogre::ColourValue& getSpecularColor() const { return light->getSpecularColour(); }
		float getIntensity() const { return light->getPowerScale(); }
		float getAttenuationRange() const;
		float getConstantAttenuation() const;
		float getLinearAttenuation() const;
		float getQuadricAttenuation() const;
		const Ogre::Vector3& getPosition() const;
		const Ogre::Vector3& getDirection() const;
		
		void setDiffuseColor(const Ogre::ColourValue& diffuseColor) { light->setDiffuseColour(diffuseColor); }
		void setSpecularColor(const Ogre::ColourValue& specularColor) { light->setSpecularColour(specularColor); }
		void setIntensity(float intensity) { light->setPowerScale(intensity); }
		void setAttenuation(float range, float constant, float linear, float quadric);
		void setSpotRange(Ogre::Degree innerAngle, Ogre::Degree outerAngle);
	};
}