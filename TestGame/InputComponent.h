#pragma once
#include "Component.h"
#include "InputHandler.h"

using namespace Engine;

class InputComponent : public Component
{
	InputHandler* inputHandler;
	float moveSpeed;
	float turnSpeed;
	float mouseSensitivity;
	unsigned int delay;
	unsigned int maxDelay;
public:
	InputComponent(const std::string& ident);

	virtual void onStart() override;
	virtual void onPreUpdate(float t, float dt) override;

	void setMoveSpeed(float ms) { moveSpeed = ms; }
	void setTurnSpeed(float ts) { turnSpeed = ts; }
	void setMouseSens(float ms) { mouseSensitivity = ms; }
	void setMaxDelay(unsigned int d) { maxDelay = d; }

	~InputComponent();
};

