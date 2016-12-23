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
	public:
		AudioComponent(const char* fileName, GameObject* observer);
		virtual ~AudioComponent();

		virtual void onPreUpdate(float t, float dt) override;

		void play(float volume, float speed, bool looping);
		void pause();
		void stop();
		bool isPlaying();
	};
}


