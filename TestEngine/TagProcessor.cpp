#include "TagProcessor.h"
#include "XMLParser.h"

namespace Engine
{
	TagProcessor::TagProcessor(const char* tagName)
		: tag(tagName)
	{
		XMLParser::getInstance().addProcessor(this);
	}
}

