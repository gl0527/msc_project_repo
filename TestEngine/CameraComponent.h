#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC CameraComponent : public RenderComponent
	{
		float nearCullingPlane;
		float farCullingPlane;
		float zOrder;
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;
		Ogre::RenderTexture* renderTexture;
		Ogre::ColourValue clearColor;
	public:
		CameraComponent(const char* name, float zDepth);
		
		virtual void onStart() override;
		virtual void onDestroy() override;

		Ogre::Camera* getCamera() const { return camera; }
		Ogre::Viewport* getViewPort() const { return viewport; }
		const Ogre::Ray& getRay(float screenX, float screenY);

		~CameraComponent();
	};
}


