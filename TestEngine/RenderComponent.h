#pragma once
#include "Component.h"

namespace Engine
{
	class RenderComponent : public Component
	{
	protected:
		Ogre::SceneNode* node;
		Ogre::Entity* entity;
	public:
		RenderComponent();

		virtual void onPostUpdate(float t, float dt) override;
		virtual void onDestroy() override;

		void createNode(Ogre::SceneNode* parentNode = 0);
		void createEntity(const Ogre::String& entityName, const Ogre::String& meshName);

		~RenderComponent();
	};
}


