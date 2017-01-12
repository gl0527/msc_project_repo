#include "Ticker.h"
#include <windows.h>

namespace Engine
{
	Ticker::Ticker()
		: lastTime(0),
		t(0),
		dt(0)
	{
	}


	void Ticker::tick()
	{
		unsigned int now = timeGetTime();
		dt = (now - lastTime) * 0.001f;
		t += dt;
		lastTime = now;
	}


	void Ticker::pause()
	{
		lastTime = timeGetTime();
	}


	float Ticker::uptime() const
	{
		return t;
	}


	float Ticker::elapsedTime() const
	{
		return dt;
	}

	
}
