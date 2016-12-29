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
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;
		Ogre::RenderWindow* renderWnd;
		Ogre::RenderTexture* renderTexture;
		Ogre::ColourValue clearColor;
		GameObject* targetObject;
	public:
		CameraComponent(const char* name, float zDepth, const Ogre::ColourValue& clear = Ogre::ColourValue(0,0,0));
		
		//virtual void onStart() override;
		virtual void onDestroy() override;
		virtual void onPostUpdate(float t, float dt) override;

		Ogre::Camera* getCamera() const { return camera; }
		Ogre::Viewport* getViewPort() const { return viewport; }
		const Ogre::Ray& getRay(float screenX, float screenY);

		void setCamera(Ogre::Camera* cam) { camera = cam; }
		void setTarget(GameObject* object) { targetObject = object; }
		void clearTarget() { targetObject = nullptr; }

		virtual ~CameraComponent();
	};
}


