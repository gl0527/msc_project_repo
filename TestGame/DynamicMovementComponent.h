#pragma once
#include "PhysicsComponent.h"
#include "InputHandler.h"
#include "SoldierComponent.h"

using namespace Engine;

class DynamicMovementComponent : public Component
{
	float moveSpeed;
	InputHandler* inputHandler;
	std::weak_ptr<PhysicsComponent> ownerPhysics;
	std::weak_ptr<SoldierComponent> ownerSoldierComp;
public:
	DynamicMovementComponent(const std::string& name);
	~DynamicMovementComponent();
	
	virtual void onStart() override;
	virtual void onPreUpdate(float t, float dt) override;

	void setMoveSpeed(float speed) { moveSpeed = speed; }
};