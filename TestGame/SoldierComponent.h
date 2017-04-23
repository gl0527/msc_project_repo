#pragma once
#include "AnimationComponent.h"
#include "InputHandler.h"

using namespace Engine;

class SoldierComponent : public Component
{
public:
	enum PlayerAction
	{
		PA_NONE,
		PA_WEAPON_HOLD,
		PA_SHOOT,
		PA_RUN
	};
private:
	PlayerAction action;
	std::weak_ptr<AnimationComponent> animComp;
public:
	SoldierComponent(const std::string& name);
	~SoldierComponent();

	virtual void onStart() override;
	virtual void onPostUpdate(float t, float dt) override;

	void setAction(PlayerAction a) { action = a; }
};