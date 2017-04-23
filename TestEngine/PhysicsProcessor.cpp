#include "PhysicsProcessor.h"
#include "PhysicsComponent.h"

namespace Engine
{
	void PhysicsProcessor::process(TiXmlElement* elem)
	{
		const auto& name = XMLParser::getInstance().parseString(elem, "name");
		float mass = XMLParser::getInstance().parseFloat(elem, "mass");
		const auto& typeName = XMLParser::getInstance().parseString(elem, "type");
		PhysicsComponent::RigidBodyType type;
		
		if (typeName == "dynamic")			type = PhysicsComponent::DYNAMIC;
		else if (typeName == "kinematic")	type = PhysicsComponent::KINEMATIC;
		else if (typeName == "static")		type = PhysicsComponent::STATIC;

		std::shared_ptr<PhysicsComponent> comp(new PhysicsComponent(name, mass, type));

		unsigned int shapeCount = 0;

		foreach_child(elem)
		{
			std::string childName(child->Value());
			
			if (childName == "shape") // lehet, hogy ennek a parszolasa kulon fuggvenybe kellene, hogy legyen
			{
				shapeCount++;
				
				const auto& shapeType = XMLParser::getInstance().parseString(child, "type");
				btCollisionShape* collShape = nullptr;
				
				if (shapeType == "box")
				{
					const auto& size = XMLParser::getInstance().parseFloat3_XYZ(child);
					collShape = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
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

				auto shapePos = Ogre::Vector3::ZERO;
				auto shapeRot = Ogre::Quaternion::IDENTITY;
				for (auto child2 = child->FirstChildElement(); child2 != nullptr; child2 = child2->NextSiblingElement())
				{
					std::string childName2(child2->Value());
					if (childName2 == "position") shapePos = XMLParser::getInstance().parseFloat3_XYZ(child2);
					if (childName2 == "rotation") shapeRot = XMLParser::getInstance().parseFloat4_WXYZ(child2);
				}
				comp->addShape(collShape, shapePos, shapeRot);
				if (shapeCount == 1)
					addToParentObject(elem, comp);
			}
			else if (childName == "material")
			{
				PhysicsMaterial phyMat;
				
				phyMat.setFriction(XMLParser::getInstance().parseFloat(child, "friction"));
				phyMat.setLinearDamping(XMLParser::getInstance().parseFloat(child, "lin_damping"));
				phyMat.setAngularDamping(XMLParser::getInstance().parseFloat(child, "ang_damping"));
				phyMat.setBounciness(XMLParser::getInstance().parseFloat(child, "bounciness"));
				
				comp->setPhysicsMaterial(phyMat);
			}
			else if (childName == "angularfactor")
			{
				const auto& angularfactor = XMLParser::getInstance().parseFloat3_XYZ(child);
				comp->setAngularFactor(angularfactor.x, angularfactor.y, angularfactor.z);
			}
			else if (childName == "trigger")
			{
				comp->setTrigger(XMLParser::getInstance().parseBoolean(child, "value"));
			}
			else if (childName == "rotation")
			{
				bool enableRotation = XMLParser::getInstance().parseBoolean(child, "enabled");
				if (!enableRotation)
					comp->disableRotation();
			}
		}
	}
}