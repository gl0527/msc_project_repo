#include "XMLParser.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "TagProcessor.h"

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
				object->removeComponent(name); // a régi transform kitörlése
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


	float XMLParser::parse1f(TiXmlElement* tag, const char* attrName)
	{
		float value;
		if (tag->QueryFloatAttribute(attrName, &value) != 0)
			throw std::exception("Float attribute cannot be parsed.\n");
		else return value;
	}


	int XMLParser::parse1i(TiXmlElement* tag, const char* attrName)
	{
		int value;
		if (tag->QueryIntAttribute(attrName, &value) != 0)
			throw std::exception("Int attribute cannot be parsed.\n");
		return value;
	}


	Ogre::Vector3 XMLParser::parse3f_XYZ(TiXmlElement* tag)
	{
		const char* att[] = { "x", "y", "z" };
		std::vector<const char*> attrs(att, att + elemCount(att));

		const auto& posv = parse<float>(tag, attrs);
		Ogre::Vector3 pos(posv[0], posv[1], posv[2]);

		return pos;
	}


	Ogre::Vector3 XMLParser::parse3f_RGB(TiXmlElement* tag)
	{
		const char* att[] = { "r", "g", "b" };
		std::vector<const char*> attrs(att, att + elemCount(att));

		const auto& colv = parse<float>(tag, attrs);
		Ogre::Vector3 col(colv[0], colv[1], colv[2]);

		return col;
	}


	Ogre::Quaternion XMLParser::parse4f_WXYZ(TiXmlElement* tag)
	{
		const char* att[] = { "qw", "qx", "qy", "qz" };
		std::vector<const char*> attrs(att, att + elemCount(att));

		const auto& qv = XMLParser::getInstance().parse<float>(tag, attrs);
		Ogre::Quaternion q(qv[0], qv[1], qv[2], qv[3]);
		
		return q;
	}
}

