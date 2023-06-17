#pragma once
#include "Shape.h"
#include <SFML/Graphics.hpp>

namespace mk
{
	class Circle : public Shape
	{
		sf::CircleShape circle;
	public:
		Circle(float);
		Circle(Object*);
		Circle() = default;

		void setPosition(sf::Vector2f);
		sf::Vector2f getPosition() const;
		
		void setRotation(float);
		float getRotation() const;

		void setColor(sf::Color);
		void setRadius(float);
		float getRadius() const;
		void draw(sf::RenderWindow&);
	};
}