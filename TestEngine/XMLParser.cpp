#include "XMLParser.h"
#include "ObjectManager.h"
#include "GameObject.h"

namespace Engine
{
	XMLParser* XMLParser::instance = nullptr;

	XMLParser::XMLParser()
		: root(nullptr)
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


	void XMLParser::addProcessor(TagProcessor* proc)
	{
		if (procs.find(proc->getTag()) == procs.end())
			procs[proc->getTag()] = proc;
	}


	void XMLParser::load(const char* fileName)
	{
		document.LoadFile(fileName);
		root = document.FirstChildElement();
		if (root == nullptr)
			throw std::exception("XML document root not found.\n");
	}


	void XMLParser::traverse(TiXmlElement* elem)
	{
		static GameObject* object = nullptr;
		
		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* tagName = child->Value();

			if (strcmp(tagName, "gameobject") == 0)
			{
				const char* name = child->Attribute("name");
				object = ObjectManager::getInstance().createGameObject(name);
			}
			if (procs[tagName])
			{
				Component* comp = procs[tagName]->process(child);
				object->addComponent(comp);
			}
			traverse(child);
		}
	}

	
	void XMLParser::process()
	{
		traverse(root);
	}
}

