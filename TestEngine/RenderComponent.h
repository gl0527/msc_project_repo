#pragma once
#include "Component.h"

namespace Engine
{
	class DLL_SPEC RenderComponent : public Component
	{
	protected:
		Ogre::SceneNode* parentNode;
		Ogre::SceneNode* currentNode;
		Ogre::Entity* entity;
		const std::string entityName;
		const std::string meshName;

		void createNode();
		void createEntity();
	public:
		class InitStruct : public Component::InitStruct
		{
		public:
			const char* eName;
			const char* mName;
			InitStruct(const char* en, const char* mn) : eName(en), mName(mn){}
		};

		RenderComponent(const char* eName, const char* mName = "");
		RenderComponent(const InitStruct& init);

		virtual void onStart() override;
		virtual void onPostUpdate(float t, float dt) override;
		virtual void onDestroy() override;

		Ogre::SceneNode* getNode() const { return currentNode; }
		Ogre::Entity* getEntity() const { return entity; }
		const std::string& getEntityName() const { return entityName; }

		virtual ~RenderComponent();
	};
}


