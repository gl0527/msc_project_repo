#pragma once
#include "System.h"
#include "Ogre.h"

namespace Engine
{
	class GUI : public System
	{
		Ogre::SceneManager* sceneManager;
	public:
		GUI();
		~GUI();

		/*virtual bool init() override;
		virtual bool update(float t, float dt) override;
		virtual void destroy() override;*/
	};
}


