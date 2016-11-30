#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC CameraComponent : public RenderComponent
	{
	protected:
		float nearCullingPlane;
		float farCullingPlane;
		float zOrder;
		float motionBlend;
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;
		Ogre::RenderTexture* renderTexture;
		Ogre::ColourValue clearColor;
		GameObject* targetObject;
	public:
		CameraComponent(const char* name, float zDepth);
		
		virtual void onStart() override;
		virtual void onDestroy() override;
		virtual void onPostUpdate(float t, float dt) override;

		Ogre::Camera* getCamera() const { return camera; }
		Ogre::Viewport* getViewPort() const { return viewport; }
		const Ogre::Ray& getRay(float screenX, float screenY);

		void setCamera(Ogre::Camera* cam) { camera = cam; }
		void setTarget(GameObject* object) { targetObject = object; }
		void clearTarget() { targetObject = nullptr; }

		~CameraComponent();
	};
}


