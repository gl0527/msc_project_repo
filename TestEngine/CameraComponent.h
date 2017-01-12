#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC CameraComponent : public RenderComponent
	{
	protected:
		float zOrder;
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;
		Ogre::RenderWindow* renderWnd;
		Ogre::RenderTexture* renderTexture;
		Ogre::ColourValue clearColor;
		GameObject* targetObject;
	public:
		CameraComponent(const char* name, float zDepth, const Ogre::ColourValue& clear = Ogre::ColourValue(0,0,0));
		
		virtual void onDestroy() override;

		Ogre::Camera* getCamera() const { return camera; }
		Ogre::Viewport* getViewPort() const { return viewport; }
		const Ogre::Ray& getRay(float screenX, float screenY) const;

		void setCamera(Ogre::Camera* cam) { camera = cam; }
		void setTarget(GameObject* object) { targetObject = object; }
		void clearTarget() { targetObject = nullptr; }
		void setNearClip(float nclip) { camera->setNearClipDistance(nclip); }
		void setFarClip(float fclip) { camera->setFarClipDistance(fclip); }
		void setRenderDist(float dist) { camera->setRenderingDistance(dist); }

		virtual ~CameraComponent();
	};
}


