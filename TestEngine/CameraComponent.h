#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class CameraComponent : public RenderComponent
	{
		float moveSpeed;
		float turnSpeed;
		float nearCullingPlane;
		float farCullingPlane;
		float zOrder;
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;
		Ogre::RenderTexture* renderTexture;
		Ogre::ColourValue clearColor;
	public:
		CameraComponent(const char* name, float zDepth);

		const Ogre::Ray& getRay(float screenX, float screenY);

		~CameraComponent();
	};
}


