#pragma once
#include "TagProcessor.h"
#include "tinyxml.h"

namespace Engine
{
	class DLL_SPEC XMLParser
	{
		std::map<std::string, TagProcessor*> procs;
		XMLParser();
		static XMLParser* instance;

		TiXmlDocument document;
		TiXmlElement* root;

		void traverse(TiXmlElement* elem);
	public:
		static XMLParser& getInstance();
		static void deleteInstance();
		static bool exists();

		void addProcessor(TagProcessor* proc);

		void load(const char* fileName);
		void process();
	};
}


