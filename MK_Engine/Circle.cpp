#include "Circle.h"
#include <SFML/Graphics.hpp>
#include "Object.h"

namespace mk
{
	Circle::Circle(float _radius)
	{
		Circle::setRadius(_radius);
		circle.setOutlineThickness(1.f);
		listOfShapes.push_back(this);
	}
	Circle::Circle(Object *_gameObject)
	{
		gameObject = _gameObject;
		Circle::setRadius(1.f);
		circle.setOutlineThickness(1.f);
		listOfShapes.push_back(this);
	}
	void Circle::draw(sf::RenderWindow& _window)
	{
		_window.draw(circle);
	}
	void Circle::setRadius(float a)
	{
		circle.setRadius(a);
		circle.setOrigin(a, a);
	}
	float Circle::getRadius() const
	{
		return circle.getRadius();
	}
	void Circle::setPosition(sf::Vector2f _pos)
	{
		circle.setPosition(_pos);
	}
	sf::Vector2f Circle::getPosition() const
	{
		return circle.getPosition();
	}
	void Circle::setRotation(float _rotation)
	{
		circle.setRotation(_rotation);
	}
	float Circle::getRotation() const
	{
		return circle.getRotation();
	}
	void Circle::setColor(sf::Color _color)
	{
		circle.setFillColor(_color);
	}
	
}