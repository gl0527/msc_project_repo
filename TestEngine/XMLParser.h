#pragma once
#include "stdafx.h"
#include <map>
#include <string>
#include "IComponentFactory.h"

namespace Engine
{
	class DLL_SPEC XMLParser
	{
		std::map<std::string, IComponentFactory*> componentFactories;
		XMLParser();
		static XMLParser* instance;
	public:
		static XMLParser& getInstance();
		static void deleteInstace();
		static bool exists();

		void addComponentFactory(const std::string& compType, IComponentFactory* compFact);
	};
}


