#pragma once
#include "CameraComponent.h"

namespace Engine
{
	class PhysicsSystem;

	class DLL_SPEC TPCameraComponent : public CameraComponent
	{
		float camHeight;
		float targetHeight;
		float camDist;
		float motBlend;
		bool fixed;
		PhysicsSystem* physicsSys;
	public:
		TPCameraComponent(const std::string& name, int zDepth);
		~TPCameraComponent();
		
		virtual void onInit(GameObject* object) override;
		virtual void onPostUpdate(float t, float dt) override;

		bool isFixed() const { return fixed; }

		void setCameraHeight(float cHeight) { camHeight = cHeight; }
		void setTargetHeight(float tHeight) { targetHeight = tHeight; }
		void setCameraDist(float dist) { camDist = dist; }
		void setMotionBlend(float mBlend) { motBlend = mBlend; }
		void setFixed(bool fix) { fixed = fix; }
	};
}
