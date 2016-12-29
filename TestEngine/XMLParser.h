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

		/*tinyxml2::XMLDocument document;
		tinyxml2::XMLElement* root;

		void traverse(tinyxml2::XMLElement* elem);*/
	public:
		static XMLParser& getInstance();
		static void deleteInstance();
		static bool exists();

		void addComponentFactory(const std::string& compType, IComponentFactory* compFact);

		void load(const char* fileName);
		void process();
	};
}


