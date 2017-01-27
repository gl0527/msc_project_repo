#include "Ticker.h"


namespace Engine
{
	void Ticker::tick()
	{
		unsigned int now = timeGetTime();
		dt = (now - lastTime) * 0.001f;
		t += dt;
		lastTime = now;
	}	
}
