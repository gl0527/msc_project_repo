#include "PhysicsProcessor.h"
#include "PhysicsComponent.h"

namespace Engine
{
	void PhysicsProcessor::process(TiXmlElement* elem, GameObject* object)
	{
		const char* name = XMLParser::getInstance().parseString(elem, "name");
		float mass = XMLParser::getInstance().parseFloat(elem, "mass");
		std::string typeName = XMLParser::getInstance().parseString(elem, "type");
		PhysicsComponent::RigidBodyType type;
		
		if (typeName == "dynamic")
			type = PhysicsComponent::DYNAMIC;
		else if(typeName == "kinematic")
			type = PhysicsComponent::KINEMATIC;
		else if (typeName == "static")
			type = PhysicsComponent::STATIC;

		PhysicsComponent* collider = new PhysicsComponent(std::string(name), mass, type);

		for (auto child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			const char* childName = child->Value();

			if (strcmp(childName, "shape") == 0)
			{
				const char* shapeType = XMLParser::getInstance().parseString(child, "type");
				btCollisionShape* collShape = nullptr;
				
				if (strcmp(shapeType, "box") == 0)
				{
					float x = XMLParser::getInstance().parseFloat(child, "x");
					float y = XMLParser::getInstance().parseFloat(child, "y");
					float z = XMLParser::getInstance().parseFloat(child, "z");

					collShape = new btBoxShape(btVector3(x, y, z));
				}
				else if (strcmp(shapeType, "staticplane") == 0)
				{
					float nx = XMLParser::getInstance().parseFloat(child, "nx");
					float ny = XMLParser::getInstance().parseFloat(child, "ny");
					float nz = XMLParser::getInstance().parseFloat(child, "nz");
					float d = XMLParser::getInstance().parseFloat(child, "d");

					collShape = new btStaticPlaneShape(btVector3(nx, ny, nz), d);
				}
				else if (strcmp(shapeType, "capsule") == 0)
				{
					float radius = XMLParser::getInstance().parseFloat(child, "r");
					float height = XMLParser::getInstance().parseFloat(child, "h");

					collShape = new btCapsuleShape(radius, height);
				}
				else if (strcmp(shapeType, "sphere") == 0)
				{
					float radius = XMLParser::getInstance().parseFloat(child, "r");
					collShape = new btSphereShape(radius);
				}
				collider->addShape(collShape);
				object->addComponent(collider);
			}
			else if (strcmp(childName, "friction") == 0)
			{
				float friction = XMLParser::getInstance().parseFloat(child, "value");
				collider->setFriction(friction);
			}
			else if (strcmp(childName, "damping") == 0)
			{
				float linearDamping = XMLParser::getInstance().parseFloat(child, "linear");
				float angularDamping = XMLParser::getInstance().parseFloat(child, "angular");
				collider->setDamping(linearDamping, angularDamping);
			}
			else if (strcmp(childName, "restitution") == 0)
			{
				float restitution = XMLParser::getInstance().parseFloat(child, "value");
				collider->setRestitution(restitution);
			}
			else if (strcmp(childName, "angularfactor") == 0)
			{
				float x = XMLParser::getInstance().parseFloat(child, "x");
				float y = XMLParser::getInstance().parseFloat(child, "y");
				float z = XMLParser::getInstance().parseFloat(child, "z");

				collider->setAngularFactor(x, y, z);
			}
			else if (strcmp(childName, "trigger") == 0)
			{
				bool trigger = XMLParser::getInstance().parseBoolean(child, "value");
				collider->setTrigger(trigger);
			}
		}
	}
}