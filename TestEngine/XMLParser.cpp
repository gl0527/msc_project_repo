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


	void XMLParser::save(const char * fileName)
	{
		TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
		document.LinkEndChild(decl);

		root = new TiXmlElement("map");
		document.LinkEndChild(root);

		// ...

		document.SaveFile(fileName);
	}


	void XMLParser::traverse(TiXmlElement* elem)
	{
		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			std::string tagName(child->Value());
			
			if (procs[tagName])
				procs[tagName]->process(child);

			traverse(child);
		}
	}


	void XMLParser::errorMessage(const std::string& msg) const
	{
		Ogre::LogManager::getSingleton().logMessage(msg);
		std::cout << msg << std::endl;
	}

	
	void XMLParser::process()
	{
		traverse(root);
	}


	float XMLParser::parseFloat(TiXmlElement* tag, const char* attrName) const
	{
		float value;
		if (tag->QueryFloatAttribute(attrName, &value) != 0)
		{
			std::string errorMsg(
				"Float parsing error: " + std::string(attrName) + " attribute of " + std::string(tag->Value()) + " tag not found.");
			errorMessage(errorMsg);
			return 0.0f;
		}
		return value;
	}


	int XMLParser::parseInt(TiXmlElement* tag, const char* attrName) const
	{
		int value;
		if (tag->QueryIntAttribute(attrName, &value) != 0)
		{
			std::string errorMsg(
				"Int parsing error: " + std::string(attrName) + " attribute of " + std::string(tag->Value()) + " tag not found.");
			errorMessage(errorMsg);
			return 0;
		}
		return value;
	}


	std::string XMLParser::parseString(TiXmlElement* tag, const char* attrName) const
	{
		const char* str = tag->Attribute(attrName);
		if (str == nullptr)
		{
			std::string errorMsg(
				"String parsing error: " + std::string(attrName) + " attribute of " + std::string(tag->Value()) + " tag not found.");
			errorMessage(errorMsg);
			return std::string();
		}
		return str;
	}


	bool XMLParser::parseBoolean(TiXmlElement* tag, const char* attrName) const
	{
		bool value;
		if (tag->QueryBoolAttribute(attrName, &value) != 0)
		{
			std::string errorMsg(
				"Boolean parsing error: " + std::string(attrName) + " attribute of " + std::string(tag->Value()) + " tag not found.");
			errorMessage(errorMsg);
			return false;
		}
		return value;
	}


	Ogre::Vector3 XMLParser::parseFloat3_XYZ(TiXmlElement* tag) const
	{
		const char* att[] = { "x", "y", "z" };
		std::vector<const char*> attrs(att, att + elemCount(att));

		const auto& posv = parse<float>(tag, attrs);
		return Ogre::Vector3(posv[0], posv[1], posv[2]);
	}


	Ogre::Vector3 XMLParser::parseFloat3_RGB(TiXmlElement* tag) const
	{
		const char* att[] = { "r", "g", "b" };
		std::vector<const char*> attrs(att, att + elemCount(att));

		const auto& colv = parse<float>(tag, attrs);
		return Ogre::Vector3(colv[0], colv[1], colv[2]);
	}


	Ogre::Quaternion XMLParser::parseFloat4_WXYZ(TiXmlElement* tag) const
	{
		const char* att[] = { "qw", "qx", "qy", "qz" };
		std::vector<const char*> attrs(att, att + elemCount(att));

		const auto& qv = XMLParser::getInstance().parse<float>(tag, attrs);
		return Ogre::Quaternion(qv[0], qv[1], qv[2], qv[3]);
	}
}

