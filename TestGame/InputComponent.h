#pragma once
#include "Component.h"
#include "InputHandler.h"

using namespace Engine;

class InputComponent : public Component
{
	InputHandler* inputHandler;
	float moveSpeed;
	unsigned int delay;
	unsigned int maxDelay;
public:
	InputComponent();

	virtual void onStart() override;
	virtual void onPreUpdate(float t, float dt) override;

	~InputComponent();
};

