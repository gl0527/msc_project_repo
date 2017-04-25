#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC BillboardComponent : public RenderComponent
	{
		static unsigned int instanceCount;
		Ogre::BillboardSet* billboardSet;
	public:
		BillboardComponent(const std::string& bbName);
		virtual ~BillboardComponent();

		virtual void onInit(GameObject* obj) override;
		virtual void onDestroy() override;

		Ogre::BillboardSet* getBillboardSet() const { return billboardSet; }
	};
}


