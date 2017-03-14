#pragma once

namespace Engine
{
	class PhysicsMaterial
	{
		float friction; // surlodas
		float linearDamping; // linearis csillapitas
		float angularDamping; // perdulet csillapitas
		float restitution; // pattogossag
	public:
		PhysicsMaterial()
			: friction(0.0f),
			linearDamping(0.0f),
			angularDamping(0.0f),
			restitution(0.0f)
		{}
	
		float getFriction() const { return friction; }
		float getLinearDamping() const { return linearDamping; }
		float getAngularDamping() const { return angularDamping; }
		float getRestitution() const { return restitution; }

		void setFriction(float newFriction) { friction = newFriction; }
		void setLinearDamping(float newLinearDamping) { linearDamping = newLinearDamping; }
		void setAngularDamping(float newAngularDamping) { angularDamping = newAngularDamping; }
		void setRestitution(float newRestitution) { restitution = newRestitution; }
	};
}