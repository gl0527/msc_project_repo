#include "AudioComponent.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include <iostream>

namespace Engine
{
	AudioComponent::AudioComponent(const std::string& fileName, const std::string& listenerName)
		: Component(fileName),
		volume(0.5f),
		speed(1.0f),
		looping(false)
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
		if (ownerObject)
			updatePose(ownerObject->transform()->position(), ownerObject->transform()->forward());
		if (auto& listenerObj = listener.lock())
			updatePose(listenerObj->transform()->position(), listenerObj->transform()->forward());
	}


	void AudioComponent::play()
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
		alGetError();
		alSourcePause(source);
	}


	void AudioComponent::stop()
	{
		alGetError();
		alSourceStop(source);
	}


	bool AudioComponent::isPlaying()
	{
		ALenum state;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	}


	void AudioComponent::setVolume(float vol)
	{
		volume = vol;
		alGetError();
		alSourcef(source, AL_GAIN, volume);
		if (alGetError() != AL_NO_ERROR)
			std::cout << "AudioComponent::setVolume: Error occured during setting volume.\n";
	}


	void AudioComponent::setSpeed(float spd)
	{
		speed = spd;
		alGetError();
		alSourcef(source, AL_PITCH, speed);
		if (alGetError() != AL_NO_ERROR)
			std::cout << "AudioComponent::setVolume: Error occured during setting speed.\n";
	}


	void AudioComponent::setLooping(bool loop)
	{
		looping = loop;
		alGetError();
		if (looping)
			alSourcei(source, AL_LOOPING, AL_TRUE);
		else
			alSourcei(source, AL_LOOPING, AL_FALSE);
		if (alGetError() != AL_NO_ERROR)
			std::cout << "AudioComponent::setVolume: Error occured during setting looping.\n";
	}
}

