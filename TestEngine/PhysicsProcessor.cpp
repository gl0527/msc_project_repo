#include "PhysicsProcessor.h"
#include "PhysicsComponent.h"

namespace Engine
{
	void PhysicsProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		float mass = XMLParser::getInstance().parseFloat(elem, "mass");
		const auto& typeName = XMLParser::getInstance().parseString(elem, "type");
		PhysicsComponent::RigidBodyType type;
		
		if (typeName == "dynamic")
			type = PhysicsComponent::DYNAMIC;
		else if(typeName == "kinematic")
			type = PhysicsComponent::KINEMATIC;
		else if (typeName == "static")
			type = PhysicsComponent::STATIC;

		auto* comp = new PhysicsComponent(name, mass, type);

		foreach_child(elem)
		{
			std::string childName(child->Value());

			if (childName == "shape")
			{
				const auto& shapeType = XMLParser::getInstance().parseString(child, "type");
				btCollisionShape* collShape = nullptr;
				
				if (shapeType == "box")
				{
					const auto& size = XMLParser::getInstance().parseFloat3_XYZ(child);
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
				comp->addShape(collShape);
				object->addComponent(comp);
			}
			else if (childName == "friction")
			{
				float friction = XMLParser::getInstance().parseFloat(child, "value");
				comp->setFriction(friction);
			}
			else if (childName == "damping")
			{
				float linearDamping = XMLParser::getInstance().parseFloat(child, "linear");
				float angularDamping = XMLParser::getInstance().parseFloat(child, "angular");
				comp->setDamping(linearDamping, angularDamping);
			}
			else if (childName == "restitution")
			{
				float restitution = XMLParser::getInstance().parseFloat(child, "value");
				comp->setRestitution(restitution);
			}
			else if (childName == "angularfactor")
			{
				const auto& angularfactor = XMLParser::getInstance().parseFloat3_XYZ(child);
				comp->setAngularFactor(angularfactor.x, angularfactor.y, angularfactor.z);
			}
			else if (childName == "trigger")
			{
				bool trigger = XMLParser::getInstance().parseBoolean(child, "value");
				comp->setTrigger(trigger);
			}
		}
	}
}