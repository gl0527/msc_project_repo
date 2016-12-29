#include "XMLParser.h"

namespace Engine
{
	XMLParser* XMLParser::instance = nullptr;

	XMLParser::XMLParser()// : root(nullptr)
	{
	}


	XMLParser& XMLParser::getInstance()
	{
		if (!instance)
			instance = new XMLParser;
		return *instance;
	}


	void XMLParser::deleteInstance()
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


	void XMLParser::load(const char* fileName)
	{
		/*document.LoadFile(fileName);
		root = document.FirstChildElement();
		if (root == nullptr)
			throw std::exception("XML document root not found.\n");*/
	}


	/*void XMLParser::traverse(tinyxml2::XMLElement* elem)
	{
		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			//ProcessTag(child);
			traverse(child);
		}
	}*/

	
	void XMLParser::process()
	{
		//traverse(root);
	}
}

