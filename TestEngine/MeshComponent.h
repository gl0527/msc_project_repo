#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC MeshComponent : public RenderComponent
	{
		Ogre::Entity* entity;
	public:
		MeshComponent(const std::string& eName, const std::string& mName);
		virtual ~MeshComponent();
		virtual void onDestroy() override;
		void setMaterial(const std::string& matName);
		Ogre::Entity* getEntity() const { return entity; }
	};
}