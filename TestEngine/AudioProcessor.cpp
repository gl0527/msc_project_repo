#include "AudioProcessor.h"
#include "AudioComponent.h"

namespace Engine
{
	void AudioProcessor::process(TiXmlElement* elem)
	{
		const auto& file = XMLParser::getInstance().parseString(elem, "file");
		const auto& listener = XMLParser::getInstance().parseString(elem, "listener");
		std::shared_ptr<AudioComponent> comp(new AudioComponent(file, listener));

		addToParentObject(elem, comp);

		foreach_child(elem)
		{
			std::string childName(child->Value());

			if (childName == "volume")
			{
				float volume = XMLParser::getInstance().parseFloat(child, "value");
				comp->setVolume(volume);
			}
			else if (childName == "speed")
			{
				float speed = XMLParser::getInstance().parseFloat(child, "value");
				comp->setSpeed(speed);
			}
			else if (childName == "loop")
			{
				bool loop = XMLParser::getInstance().parseBoolean(child, "value");
				comp->setLooping(loop);
			}
		}
	}
}

