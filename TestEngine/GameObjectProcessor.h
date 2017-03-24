#pragma once
#include "TagProcessor.h"

namespace Engine
{
	class GameObjectProcessor : public TagProcessor
	{
	public:
		GameObjectProcessor() : TagProcessor("gameobject") {}
		virtual void process(TiXmlElement* elem) override;
		virtual void addToParentObject(TiXmlElement* elem, const std::shared_ptr<Component>& component) {}
	};
}