#pragma once
#include "Shape.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace mk
{
	class Convex : public Shape
	{
		void calculateCoM(); //CoM = center of mass
		sf::Vector2f *transformedVerticies;
		float rotationRadians;
	public:
		sf::ConvexShape polygon;
		Convex(Object*);
		void setVertices(const std::initializer_list < sf::Vector2f >&, bool = false);
		
		void setPosition(sf::Vector2f);
		sf::Vector2f getPosition() const;

		void setRotation(float);
		float getRotation() const;
		float getRotationRadians() const;

		sf::Vector2f getAbsolutePosition(size_t) const;

		void setColor(sf::Color);
		void draw(sf::RenderWindow&);
	};
}