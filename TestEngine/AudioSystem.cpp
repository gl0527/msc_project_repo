#include "AudioSystem.h"

namespace Engine
{
	AudioSystem::AudioSystem()
	{
	}


	AudioSystem::~AudioSystem()
	{
	}


	bool AudioSystem::init()
	{
		alutInit(0, 0);
		ALenum error;
		error = alutGetError();
		if (error != AL_NO_ERROR)
			return false;
		return true;
	}


	void AudioSystem::destroy()
	{
		alutExit();
	}


	ALuint loadFile(const char* fileName)
	{
		ALenum error;
		ALuint newBuffer;
		ALUT_SAFE_CALL(newBuffer = alutCreateBufferFromFile(fileName), "Cannot load audio file: ");
		return newBuffer;
	}
}

