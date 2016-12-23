#pragma once
#include <vector>
#include "EventID.h"

namespace Engine
{
	class EventHandler
	{
	public:
		EventHandler();
		~EventHandler();

		virtual void handleEvent(EventID* evtID) = 0;
	};
}


