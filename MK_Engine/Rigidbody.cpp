#include "Rigidbody.h"
#include "Math.h"
#include "Error.h"
#include "Physic.h"

namespace mk
{
	//DYNAMIC
	Rigidbody::Rigidbody(Object* _gameObject)
	{
		gameObject = _gameObject;
		assignedShape = gameObject->getComponent<Shape>();
		if (!assignedShape) throw Error::COMPONENT_NOT_FOUND;
	}
	Rigidbody::~Rigidbody()
	{

	}
	void Rigidbody::Update()
	{
		if (gravity)
		{
			velocity += *gravity * Physic::getDeltaTime();
		}
		velocity += force * mass * Physic::getDeltaTime();
		assignedShape->setPosition(assignedShape->getPosition() + velocity * Physic::getDeltaTime());
		angularVelocity += torque * Physic::getDeltaTime();
		assignedShape->setRotation(assignedShape->getRotation() + angularVelocity * Physic::getDeltaTime());
	}
	void Rigidbody::setMass(float _mass)
	{
		mass = _mass;
		if (_mass == 0) inverseMass = 0;
		else inverseMass = 1 / mass;
	}
	float Rigidbody::getMass() const
	{
		return mass;
	}
	float Rigidbody::getInverseMass() const
	{
		return inverseMass;
	}
	void Rigidbody::setVelocity(sf::Vector2f vel)
	{
		velocity = vel;
	}

	void Rigidbody::setInertia(float _inertia)
	{
		inertia = _inertia;
		if (_inertia == 0) inverseInertia = 0;
		else inverseInertia = 1 / inertia;
	}
	float Rigidbody::getInertia() const
	{
		return inertia;
	}
	float Rigidbody::getInverseInertia() const
	{
		return inverseInertia;
	}

	sf::Vector2f Rigidbody::getVelocity() const
	{
		return velocity;
	}

	void Rigidbody::setAngularVelocity(float _angularVelocity)
	{
		angularVelocity = _angularVelocity;
	}
	float Rigidbody::getAngularVelocity() const
	{
		return angularVelocity;
	}
	void Rigidbody::setGravity(sf::Vector2f* _gravity)
	{
		gravity = _gravity;
	}
	sf::Vector2f Rigidbody::getGravity() const
	{
		if (gravity) return *gravity;
		return sf::Vector2f(0, 0);
	}
}