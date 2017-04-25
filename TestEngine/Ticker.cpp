#include "Ticker.h"


namespace Engine
{
	void Ticker::tick()
	{
		unsigned int now = timeGetTime();
		if (lastTime == 0)
			lastTime = now;
		dt = (now - lastTime) * 0.001f;
		t += dt;
		lastTime = now;
	}	
}
