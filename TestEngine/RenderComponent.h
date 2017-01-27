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
		std::string objName;

		void createNode();
	public:
		/*class InitStruct : public Component::InitStruct
		{
		public:
			const char* eName;
			const char* mName;
			InitStruct(const char* en, const char* mn) : eName(en), mName(mn){}
		};*/

		RenderComponent(const std::string& name);
		//RenderComponent(const InitStruct& init);

		virtual void onStart() override;
		virtual void onPostUpdate(float t, float dt) override;
		virtual void onDestroy() override;

		Ogre::SceneNode* getNode() const { return currentNode; }

		void setCastShadows(bool cast);
		void setVisible(bool visible);

		virtual ~RenderComponent();
	};
}


