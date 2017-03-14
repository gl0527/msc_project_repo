#pragma once
#include "tinyxml.h"
#include "stdafx.h"
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "Ogre.h"

#define elemCount(v) sizeof(v)/sizeof(v[0])

namespace Engine
{
	class TagProcessor;

	class DLL_SPEC XMLParser
	{
		std::map<std::string, TagProcessor*> procs;
		XMLParser();
		static XMLParser* instance;

		TiXmlDocument document;
		TiXmlElement* root;

		void traverse(TiXmlElement* elem);

		void errorMessage(const std::string& msg) const;
	public:
		static XMLParser& getInstance();
		static void deleteInstance();
		static bool exists();

		void addProcessor(TagProcessor* proc);

		void load(const char* fileName);
		void save(const char* fileName);
		void process();

		float parseFloat(TiXmlElement* tag, const char* attrName) const;
		int parseInt(TiXmlElement* tag, const char* attrName) const;
		std::string parseString(TiXmlElement* tag, const char* attrName) const;
		bool parseBoolean(TiXmlElement* tag, const char* attrName) const;

		Ogre::Vector3 parseFloat3_XYZ(TiXmlElement* tag) const;
		Ogre::Vector3 parseFloat3_RGB(TiXmlElement* tag) const;
		Ogre::Quaternion parseFloat4_WXYZ(TiXmlElement* tag) const;

		template<typename T>
		std::vector<T> parse(TiXmlElement* tag, const std::vector<const char*>& attrs) const
		{
			std::vector<T> attrValues;

			if (tag == nullptr)
			{
				errorMessage("Tag not found.");
				return attrValues;
			}

			for (int i = 0; i < attrs.size(); ++i)
			{
				const char* attribute = tag->Attribute(attrs[i]);
				
				if (attribute == nullptr)
				{
					std::string errorMsg(
						std::string(attribute) + " attribute of " + std::string(tag->Value()) + " tag not found.");
					errorMessage(errorMsg);
					return attrValues;
				}
				std::stringstream ss(attribute);
				T value;
				
				if (ss >> value)
					attrValues.push_back(value);
				else
				{
					std::string errorMsg("Conversion from string to T failed.\n");
					errorMessage(errorMsg);
					return attrValues;
				}
			}
			return attrValues;
		}
	};
}


