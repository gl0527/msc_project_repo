#include "PhysicsProcessor.h"
#include "PhysicsComponent.h"

namespace Engine
{
	void PhysicsProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const std::string& name = XMLParser::getInstance().parseString(elem, "name");
		float mass = XMLParser::getInstance().parseFloat(elem, "mass");
		const std::string& typeName = XMLParser::getInstance().parseString(elem, "type");
		PhysicsComponent::RigidBodyType type;
		
		if (typeName == "dynamic")
			type = PhysicsComponent::DYNAMIC;
		else if(typeName == "kinematic")
			type = PhysicsComponent::KINEMATIC;
		else if (typeName == "static")
			type = PhysicsComponent::STATIC;

		PhysicsComponent* collider = new PhysicsComponent(name, mass, type);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			std::string childName(child->Value());

			if (childName == "shape")
			{
				const std::string& shapeType = XMLParser::getInstance().parseString(child, "type");
				btCollisionShape* collShape = nullptr;
				
				if (shapeType == "box")
				{
					const Ogre::Vector3& size = XMLParser::getInstance().parseFloat3_XYZ(child);
					collShape = new btBoxShape(btVector3(size.x, size.y, size.z));
				}
				else if (shapeType == "staticplane")
				{
					float nx = XMLParser::getInstance().parseFloat(child, "nx");
					float ny = XMLParser::getInstance().parseFloat(child, "ny");
					float nz = XMLParser::getInstance().parseFloat(child, "nz");
					float d = XMLParser::getInstance().parseFloat(child, "d");

					collShape = new btStaticPlaneShape(btVector3(nx, ny, nz), d);
				}
				else if (shapeType == "capsule")
				{
					float radius = XMLParser::getInstance().parseFloat(child, "r");
					float height = XMLParser::getInstance().parseFloat(child, "h");

					collShape = new btCapsuleShape(radius, height);
				}
				else if (shapeType == "sphere")
				{
					float radius = XMLParser::getInstance().parseFloat(child, "r");
					collShape = new btSphereShape(radius);
				}
				collider->addShape(collShape);
				object->addComponent(collider);
			}
			else if (childName == "friction")
			{
				float friction = XMLParser::getInstance().parseFloat(child, "value");
				collider->setFriction(friction);
			}
			else if (childName == "damping")
			{
				float linearDamping = XMLParser::getInstance().parseFloat(child, "linear");
				float angularDamping = XMLParser::getInstance().parseFloat(child, "angular");
				collider->setDamping(linearDamping, angularDamping);
			}
			else if (childName == "restitution")
			{
				float restitution = XMLParser::getInstance().parseFloat(child, "value");
				collider->setRestitution(restitution);
			}
			else if (childName == "angularfactor")
			{
				const Ogre::Vector3 angularfactor = XMLParser::getInstance().parseFloat3_XYZ(child);
				collider->setAngularFactor(angularfactor.x, angularfactor.y, angularfactor.z);
			}
			else if (childName == "trigger")
			{
				bool trigger = XMLParser::getInstance().parseBoolean(child, "value");
				collider->setTrigger(trigger);
			}
		}
	}
}