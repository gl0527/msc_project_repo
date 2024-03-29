#pragma once
#include "Component.h"

namespace Engine
{
	class DLL_SPEC RenderComponent : public Component
	{
	protected:
		Ogre::SceneNode* parentNode;
		Ogre::SceneNode* currentNode;
		Ogre::MovableObject* object;
		Ogre::SceneManager* sceneMgr;

		void createNode();
	public:
		RenderComponent(const std::string& name);

		virtual void onInit(GameObject* obj) override;
		virtual void onPostUpdate(float t, float dt) override;
		virtual void onDestroy() override;

		Ogre::SceneNode* getNode() const { return currentNode; }

		void setCastShadows(bool cast);
		void setVisible(bool visible);

		virtual ~RenderComponent();
	};
}


