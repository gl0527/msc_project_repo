#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC MeshComponent : public RenderComponent
	{
		static unsigned int instanceCount;
		Ogre::Entity* entity;
		std::string mesh;
	public:
		MeshComponent(const std::string& eName, const std::string& mName);
		virtual ~MeshComponent();

		virtual void onInit(GameObject* obj) override;
		virtual void onDestroy() override;
		
		void setMaterial(const std::string& matName);
		Ogre::Entity* getEntity() const { return entity; }
	};
}