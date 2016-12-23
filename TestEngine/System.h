#pragma once

namespace Engine
{
	class System
	{
	public:
		virtual bool init() { return true; }
		virtual bool update(float t, float dt) { return true; }
		virtual void destroy() {}
		virtual ~System() {}
	};
}


