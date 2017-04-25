#pragma once
#include "alut.h"
#include "Component.h"

namespace Engine
{
	class DLL_SPEC AudioComponent : public Component
	{
		float volume;
		float speed;
		bool looping;
		ALuint buffer;
		ALuint source;
		GameObject_wptr listener;
		void updatePose(const Ogre::Vector3& pos, const Ogre::Vector3& dir);
	public:
		AudioComponent(const std::string& fileName, const std::string& listenerName);
		virtual ~AudioComponent();

		virtual void onPreUpdate(float t, float dt) override;

		void play();
		void pause();
		void stop();
		bool isPlaying();

		void setVolume(float vol);
		void setSpeed(float spd);
		void setLooping(bool loop);
	};
}


