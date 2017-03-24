#pragma once
#include "PhysicsComponent.h"
#include "InputHandler.h"

using namespace Engine;

class DynamicMovementComponent : public Component
{
	float moveSpeed;
	InputHandler* inputHandler;
	PhysicsComponent* ownerPhysics;
public:
	DynamicMovementComponent(const std::string& name);
	~DynamicMovementComponent();
	
	virtual void onStart() override;
	virtual void onPreUpdate(float t, float dt) override;
};