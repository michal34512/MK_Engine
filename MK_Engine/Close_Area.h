#pragma once
#include <SFML/Graphics.hpp>
namespace mk
{
	class Shape;
	class Circle;
	class Convex;
	class Close_Area
	{
		float radius=0;
		Shape* assignedShape;
	public:
		Close_Area() {};
		Close_Area(Convex*);
		Close_Area(Circle*);
		bool operator==(const Close_Area&); //Checks for overlaping
		bool operator==(const sf::Vector2f&);
	};
}