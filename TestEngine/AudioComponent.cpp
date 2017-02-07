#include "AudioComponent.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include <iostream>

namespace Engine
{
	AudioComponent::AudioComponent(const std::string& fileName, const std::string& listenerName)
		: Component(fileName)
	{
		buffer = alutCreateBufferFromFile(fileName.c_str());
		ALenum error = alutGetError();
		if (error != AL_NO_ERROR)
			std::cout << "Cannot load audio file.\n";
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, buffer);
		listener = ObjectManager::getInstance().getGameObject(listenerName);
	}


	AudioComponent::~AudioComponent()
	{
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
	}


	void AudioComponent::updatePose(const Ogre::Vector3& pos, const Ogre::Vector3& dir)
	{
		alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
		alSource3f(source, AL_VELOCITY, dir.x, dir.y, dir.z);
		alSource3f(source, AL_DIRECTION, dir.x, dir.y, dir.z);
	}


	void AudioComponent::onPreUpdate(float t, float dt)
	{
		updatePose(ownerObject->getTransform()->getPosition(), ownerObject->getTransform()->getForward());
		updatePose(listener->getTransform()->getPosition(), listener->getTransform()->getForward());
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


	void AudioComponent::setVolume(float volume)
	{
		alSourcef(source, AL_GAIN, volume);
	}


	void AudioComponent::setSpeed(float speed)
	{
		alSourcef(source, AL_PITCH, speed);
	}
}

