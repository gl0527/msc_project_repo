#pragma once
#include "System.h"
#include <al.h>
#include <alc.h>
#include <alut.h>
#include <iostream>

namespace Engine
{
#define MAX_AUDIO_BUFFERS 32
#define MAX_AUDIO_SOURCES 8
#define ALUT_SAFE_CALL(call, message) { call; \
		ALenum error = alutGetError(); \
		if(error != ALUT_ERROR_NO_ERROR) \
			 std::cout << "ALUT Error occured.\n";\
    }
#define AL_SAFE_CALL(call, message) {call; \
		ALenum error = alGetError(); \
		if(error != AL_NO_ERROR) \
			 std::cout << "AL Error occured.\n";\
    }

	class AudioSystem : public System
	{
		ALCdevice* audioDevice;
		ALCcontext* audioContext;
		bool enabled;
	public:
		AudioSystem();
		~AudioSystem();

		virtual bool init() override;
		virtual void destroy() override;

		bool isEnabled() const { return enabled; }
		ALuint loadFile(const char* fileName);
	};
}


