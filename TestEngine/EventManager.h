#pragma once
#include <map>
#include "EventHandler.h"
#include "EventID.h"

namespace Engine
{
	class EventManager
	{
		std::map<EventID*, EventHandler*> handlers;
	public:
		EventManager();
		~EventManager();

		void handleEvents();
		void bind(EventID* evtID, EventHandler* evtHandler);
		void unbind(EventID* evtID, EventHandler* evtHandler);
	};
}

