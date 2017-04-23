#pragma once

namespace Engine
{
	class PhysicsMaterial
	{
		float friction; // surlodas (static, dynamic)
		float linearDamping; // linearis csillapitas
		float angularDamping; // perdulet csillapitas
		float bounciness; // pattogossag
	public:
		PhysicsMaterial()
			: friction(0.0f),
			linearDamping(0.0f),
			angularDamping(0.0f),
			bounciness(0.0f)
		{}
	
		float getFriction() const { return friction; }
		float getLinearDamping() const { return linearDamping; }
		float getAngularDamping() const { return angularDamping; }
		float getBounciness() const { return bounciness; }

		void setFriction(float newFriction) { friction = newFriction; }
		void setLinearDamping(float newLinearDamping) { linearDamping = newLinearDamping; }
		void setAngularDamping(float newAngularDamping) { angularDamping = newAngularDamping; }
		void setBounciness(float newBounciness) { bounciness = newBounciness; }
	};
}