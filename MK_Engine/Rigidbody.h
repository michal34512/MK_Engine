#pragma once
#include <SFML/Graphics.hpp>
#include "Shape.h"
#include "Object.h"
#include <vector>

namespace mk 
{
	class Rigidbody : public Component
	{
		Shape* assignedShape;
		sf::Vector2f *gravity = nullptr;

		sf::Vector2f velocity;
		sf::Vector2f force;

		float angularVelocity;
		float torque;
		float mass = 1;
		float inverseMass = 1;
		float inertia = 500.f;
		float inverseInertia = 0.002f;

	public:
		float restitution = 1;
		Rigidbody(Object*);
		~Rigidbody();
		
		void Update() override;
		void setMass(float _mass);
		float getMass() const;
		float getInverseMass() const;

		void setInertia(float _mass);
		float getInertia() const;
		float getInverseInertia() const;

		void setVelocity(sf::Vector2f);
		sf::Vector2f getVelocity() const;
		void setAngularVelocity(float);
		float getAngularVelocity() const;
		void setGravity(sf::Vector2f*);
		sf::Vector2f getGravity() const;
	};
}