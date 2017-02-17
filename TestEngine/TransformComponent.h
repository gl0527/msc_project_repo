#pragma once
#include "Component.h"

namespace Engine
{
	class TransformComponent : public Component
	{
		Ogre::Vector3 _pos;
		Ogre::Quaternion _rot;
		Ogre::Vector3 _scale;
	public:
		TransformComponent(const std::string& name) :
			Component(name),
			_pos(Ogre::Vector3::ZERO),
			_rot(Ogre::Quaternion::IDENTITY),
			_scale(Ogre::Vector3::UNIT_SCALE)
		{}

		// getter functions
		const Ogre::Vector3& position() const { return _pos; }
		const Ogre::Quaternion& rotation() const { return _rot; }
		const Ogre::Vector3& scale() const { return _scale; }
		
		Ogre::Vector3 forward() const { return _rot * Ogre::Vector3::NEGATIVE_UNIT_Z; }
		Ogre::Vector3 up() const { return _rot * Ogre::Vector3::UNIT_Y; }
		Ogre::Vector3 right() const	{ return _rot * Ogre::Vector3::UNIT_X; }

		// setter functions
		void setPosition(const Ogre::Vector3& p) { _pos = p; }
		void setRotation(const Ogre::Quaternion& q) { _rot = q; }
		void setScale(const Ogre::Vector3& s) { _scale = s; }

		void translate(const Ogre::Vector3& p) { _pos += p; }
		void rotate(const Ogre::Quaternion& q) { _rot = _rot * q; }
		void scaling(const Ogre::Vector3& s) { _scale *= s; }
	};
}