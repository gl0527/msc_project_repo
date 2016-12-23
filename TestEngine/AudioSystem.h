#pragma once
#include "System.h"
#include "alut.h"
#include <iostream>

namespace Engine
{
	class AudioSystem : public System
	{
		ALCdevice* audioDevice;
		ALCcontext* audioContext;
		bool enabled;
		const unsigned char MAX_BUFFERS;
		const unsigned char MAX_SOURCES;
	public:
		AudioSystem();
		~AudioSystem();

		virtual bool init() override;
		virtual void destroy() override;

		bool isEnabled() const { return enabled; }
		void enable() { enabled = true; }
		void disable() { enabled = false; }

		const unsigned char getMaxBuffers() const { return MAX_BUFFERS; }
		const unsigned char getMaxSources() const { return MAX_SOURCES; }
	};
}


