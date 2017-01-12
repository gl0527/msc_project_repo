#pragma once
#include "Component.h"
#include "RenderSystem.h"

using namespace Engine;

class FPSComponent : public Component
{
	RenderSystem* renderSys;
	Ogre::RenderWindow* renderWnd;
	Ogre::TextAreaOverlayElement* text;
public:
	FPSComponent(const char* name);
	~FPSComponent();

	virtual void onPostUpdate(float t, float dt) override;
};

