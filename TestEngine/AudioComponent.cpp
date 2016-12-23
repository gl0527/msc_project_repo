#include "AudioComponent.h"
#include "GameObject.h"
#include <iostream>

namespace Engine
{
	AudioComponent::AudioComponent(const char* fileName, GameObject* observer)
		: Component(0),
		listener(observer)
	{
		buffer = alutCreateBufferFromFile(fileName);
		ALenum error = alutGetError();
		if (error != AL_NO_ERROR)
			std::cout << "Cannot load audio file";
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, buffer);
	}


	AudioComponent::~AudioComponent()
	{
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
	}


	void AudioComponent::onPreUpdate(float t, float dt)
	{
		const Ogre::Vector3& ownerPos = ownerObject->getPosition();
		const Ogre::Vector3& ownerDir = ownerObject->getDirection();

		const Ogre::Vector3& listenerPos = listener->getPosition();
		const Ogre::Vector3& listenerDir = listener->getDirection();
		
		alSource3f(source, AL_POSITION, ownerPos.x, ownerPos.y, ownerPos.z);
		alSource3f(source, AL_VELOCITY, ownerDir.x, ownerDir.y, ownerDir.z);
		alSource3f(source, AL_DIRECTION, ownerDir.x, ownerDir.y, ownerDir.z);
		
		alListener3f(AL_POSITION, listenerPos.x, listenerPos.y, listenerPos.z);
		alListener3f(AL_VELOCITY, listenerDir.x, listenerDir.y, listenerDir.z);
		alListener3f(AL_DIRECTION, listenerDir.x, listenerDir.y, listenerDir.z);
	}


	void AudioComponent::play(float volume, float speed, bool looping)
	{
		if (isPlaying())
			return;
		if (looping)
			alSourcei(source, AL_LOOPING, AL_TRUE);
		alSourcef(source, AL_GAIN, volume);
		alSourcef(source, AL_PITCH, speed);
		alSourcePlay(source);
	}


	void AudioComponent::pause()
	{
		alSourcePause(source);
	}


	void AudioComponent::stop()
	{
		alSourceStop(source);
	}


	bool AudioComponent::isPlaying()
	{
		ALenum state;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	}
}

