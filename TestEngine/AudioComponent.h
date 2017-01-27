#pragma once
#include "alut.h"
#include "Component.h"

namespace Engine
{
	class DLL_SPEC AudioComponent : public Component
	{
		ALuint buffer;
		ALuint source;
		GameObject* listener;
		void updatePose(const Ogre::Vector3& pos, const Ogre::Vector3& dir);
	public:
		AudioComponent(const std::string& fileName, GameObject* observer);
		virtual ~AudioComponent();

		virtual void onPreUpdate(float t, float dt) override;

		void play(float volume, float speed, bool looping);
		void pause();
		void stop();
		bool isPlaying();

		void setVolume(float volume);
		void setSpeed(float speed);
	};
}


