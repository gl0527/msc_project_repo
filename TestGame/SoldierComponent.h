#pragma once
#include "AnimationComponent.h"
#include "InputHandler.h"

using namespace Engine;

class SoldierComponent : public Component
{
	AnimationComponent* animComp;
public:
	SoldierComponent(const std::string& name);
	~SoldierComponent();

	virtual void onStart() override;
	virtual void onPostUpdate(float t, float dt) override;
};