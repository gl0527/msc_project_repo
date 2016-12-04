#include "XMLParser.h"

namespace Engine
{
	XMLParser* XMLParser::instance = nullptr;

	XMLParser::XMLParser()
	{
	}


	XMLParser& XMLParser::getInstance()
	{
		if (!instance)
			instance = new XMLParser;
		return *instance;
	}


	void XMLParser::deleteInstace()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}


	bool XMLParser::exists()
	{
		return (instance != nullptr);
	}


	void XMLParser::addComponentFactory(const std::string& compType, IComponentFactory* compFact)
	{

	}
}

