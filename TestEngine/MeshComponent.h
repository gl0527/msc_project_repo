#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC MeshComponent : public RenderComponent
	{
		const std::string meshName;
		Ogre::Entity* entity;
	public:
		MeshComponent(const char* eName, const char* mName);
		virtual ~MeshComponent();

		virtual void onDestroy() override;

		void setMaterial(const char* matName);
	};
}


