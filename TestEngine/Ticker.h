#pragma once

namespace Engine
{
	class Ticker
	{
		unsigned int lastTime;
		float t;
		float dt;
	public:
		Ticker();
		void tick();
		void pause();
		float uptime() const;
		float elapsedTime() const;
	};
}


