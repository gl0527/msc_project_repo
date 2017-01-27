#pragma once
#include <windows.h>

namespace Engine
{
	class Ticker
	{
		unsigned int lastTime;
		float t;
		float dt;
	public:
		Ticker() : lastTime(0), t(0), dt(0) {}
		void tick();
		void pause() { lastTime = timeGetTime(); }
		float uptime() const { return t; }
		float elapsedTime() const { return dt; }
	};
}


