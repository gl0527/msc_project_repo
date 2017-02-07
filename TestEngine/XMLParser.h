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
	public:
		static XMLParser& getInstance();
		static void deleteInstance();
		static bool exists();

		void addProcessor(TagProcessor* proc);

		void load(const char* fileName);
		void process();

		float parse1f(TiXmlElement* tag, const char* attrName);
		int parse1i(TiXmlElement* tag, const char* attrName);
		//const char* parseString(TiXmlElement* tag, const char* attrName);
		Ogre::Vector3 parse3f_XYZ(TiXmlElement* tag);
		Ogre::Vector3 parse3f_RGB(TiXmlElement* tag);
		Ogre::Quaternion parse4f_WXYZ(TiXmlElement* tag);

		template<typename T>
		std::vector<T> parse(TiXmlElement* tag, const std::vector<const char*>& attrs)
		{
			std::vector<T> attrValues;
			for (int i = 0; i < attrs.size(); ++i)
			{
				T value;
				std::stringstream ss(tag->Attribute(attrs[i]));
				ss >> value;
				attrValues.push_back(value);
			}
			return attrValues;
		}
	};
}


