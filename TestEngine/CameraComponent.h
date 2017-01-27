#pragma once
#include "RenderComponent.h"

namespace Engine
{
	class DLL_SPEC CameraComponent : public RenderComponent
	{
	protected:
		int zOrder;
		Ogre::Camera* camera;
		Ogre::Viewport* viewport;
		Ogre::RenderWindow* renderWnd;
		Ogre::RenderTexture* renderTexture;
	public:
		CameraComponent(const std::string& name, int zDepth);
		
		virtual void onDestroy() override;

		Ogre::Camera* getCamera() const { return camera; }
		Ogre::Viewport* getViewPort() const { return viewport; }
		Ogre::Ray getRay(float screenX, float screenY) const;

		void setCamera(Ogre::Camera* cam) { camera = cam; }
		void SetPosition(const Ogre::Vector3& newPos) { camera->setPosition(newPos); }
		void setLookAt(const Ogre::Vector3& newLookAt) { camera->lookAt(newLookAt); }
		void setNearClip(float nclip) { camera->setNearClipDistance(nclip); }
		void setFarClip(float fclip) { camera->setFarClipDistance(fclip); }
		void setRenderDist(float dist) { camera->setRenderingDistance(dist); }
		void setRenderTexture(Ogre::RenderTexture* rt);

		virtual ~CameraComponent();
	};
}


