#pragma once

namespace Engine
{
	class System
	{
	public:
		virtual void init() {}
		virtual void update(float t, float dt) {}
		virtual void destroy() {}
	};
}


