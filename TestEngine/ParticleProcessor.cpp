#include "ParticleProcessor.h"
#include "ParticleComponent.h"

namespace Engine
{
	void ParticleProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		const auto& particle = XMLParser::getInstance().parseString(elem, "particle");
		std::shared_ptr<ParticleComponent> comp(new ParticleComponent(name, particle));

		addToParentObject(elem, comp);
	}
}

