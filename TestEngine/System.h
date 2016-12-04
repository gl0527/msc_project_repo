#pragma once

namespace Engine
{
	class System
	{
	public:
		virtual bool init() { return false; }
		virtual bool update(float t, float dt) { return false; }
		virtual void destroy() {}
		virtual ~System() {}
	};
}


