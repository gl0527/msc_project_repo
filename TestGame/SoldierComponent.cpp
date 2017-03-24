#include "SoldierComponent.h"
#include "GameObject.h"

SoldierComponent::SoldierComponent(const std::string& name)
	: Component(name),
	animComp(nullptr)
{
}


SoldierComponent::~SoldierComponent()
{
}


void SoldierComponent::onStart()
{
	animComp = ownerObject->getFirstComponentByType<AnimationComponent>().get();
	if (animComp == nullptr)
		ownerObject->removeComponent(name);
}


void SoldierComponent::onPostUpdate(float t, float dt)
{
	animComp->start("leg_run");
	animComp->setWeight(1);
	animComp->setLoop(true);
	animComp->step(dt);

	animComp->start("up_run");
	animComp->setWeight(1);
	animComp->setLoop(true);
	animComp->step(dt);
}