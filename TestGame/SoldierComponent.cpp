#include "SoldierComponent.h"
#include "GameObject.h"

SoldierComponent::SoldierComponent(const std::string& name)
	: Component(name),
	action(PA_NONE),
	animComp(std::shared_ptr<AnimationComponent>(nullptr))
{
}


SoldierComponent::~SoldierComponent()
{
}


void SoldierComponent::onStart()
{
	animComp = ownerObject->getFirstComponentByType<AnimationComponent>();
	if(animComp.lock() == nullptr)
		ownerObject->removeComponent(name);
}


void SoldierComponent::onPostUpdate(float t, float dt)
{
	if (auto& anim = animComp.lock())
	{
		anim->init("leg_stand");
		anim->setWeight(1);
		anim->setLoop(action == PA_NONE);
		anim->setEnabled(action == PA_NONE);
		anim->step(dt);

		anim->init("up_stand");
		anim->setWeight(1);
		anim->setLoop(action == PA_NONE);
		anim->setEnabled(action == PA_NONE);
		anim->step(dt);

		anim->init("leg_run");
		anim->setWeight(1);
		anim->setLoop(true);
		anim->setEnabled(action == PA_RUN);
		anim->step(dt);

		anim->init("up_run");
		anim->setWeight(1);
		anim->setLoop(true);
		anim->setEnabled(action == PA_RUN);
		anim->step(dt);

		anim->init("up_shoot");
		anim->setWeight(1);
		anim->setLoop(false);
		anim->setEnabled(action == PA_SHOOT);
		anim->step(dt);
		if (anim->ended() && action == PA_SHOOT) {
			anim->setTime(0.0f);
			action = PA_NONE;
		}
	}
}