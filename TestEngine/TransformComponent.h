#pragma once
#include "Component.h"

namespace Engine
{
	class TransformComponent : public Component
	{
		Ogre::Vector3 pos;
		Ogre::Quaternion rot;
		Ogre::Vector3 scale;
	public:
		TransformComponent(const std::string& name) :
			Component(name),
			pos(Ogre::Vector3::ZERO),
			rot(Ogre::Quaternion::IDENTITY),
			scale(Ogre::Vector3::UNIT_SCALE)
		{}

		const Ogre::Vector3& getPosition() const { return pos; }
		const Ogre::Quaternion& getRotation() const { return rot; }
		const Ogre::Vector3& getScale() const { return scale; }

		Ogre::Vector3 getForward() const { return rot * Ogre::Vector3::NEGATIVE_UNIT_Z; }
		Ogre::Vector3 getUp() const { return rot * Ogre::Vector3::UNIT_Y; }
		Ogre::Vector3 getRight() const { return rot * Ogre::Vector3::UNIT_X; }
		Ogre::Vector3 getLocalVector(const Ogre::Vector3& vec) const { return rot * vec; }

		void setPosition(const Ogre::Vector3& p) { pos = p; }
		void setRotation(const Ogre::Quaternion& q) { rot = q; }
		void setScale(const Ogre::Vector3& s) { scale = s; }
	};
}