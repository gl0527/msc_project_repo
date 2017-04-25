#pragma once
#include "CameraComponent.h"

using namespace Engine;

class CameraControlComponent : public Component
{
	float camHeight;
	float targetHeight;
	float camDist;
	float motBlend;
	bool fixed;
	PhysicsSystem* world;
	std::weak_ptr<CameraComponent> ownerCam;
public:
	CameraControlComponent(const std::string& name);
	~CameraControlComponent();

	virtual void onStart() override;
	virtual void onPostUpdate(float t, float dt) override;
};