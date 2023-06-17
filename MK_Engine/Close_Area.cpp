#include "Close_Area.h"
#include "Circle.h"
#include "Convex.h"
#include "Shape.h"

namespace mk
{
	Close_Area::Close_Area(Convex* _assignedShape)
	{
		assignedShape = _assignedShape;
		float maxRadiusSquared = 0;
		for (size_t i = 0; i < _assignedShape->polygon.getPointCount(); i++)
		{
			sf::Vector2f vec = _assignedShape->polygon.getPoint(i);
			maxRadiusSquared = std::max(maxRadiusSquared, vec.x * vec.x + vec.y * vec.y);
		}
		radius = sqrt(maxRadiusSquared);
	}
	Close_Area::Close_Area(Circle* _assignedShape)
	{
		assignedShape = _assignedShape;
		radius = _assignedShape->getRadius();
	}
	bool Close_Area::operator==(const Close_Area& _other)
	{
		if (!assignedShape) return false;
		sf::Vector2f dif = assignedShape->getPosition() - _other.assignedShape->getPosition();
		float rad = radius + _other.radius;
		return dif.x * dif.x + dif.y * dif.y <= rad * rad;
	}
	bool Close_Area::operator==(const sf::Vector2f& _vec)
	{
		if (!assignedShape) return false;
		sf::Vector2f dif = assignedShape->getPosition() - _vec;
		return dif.x * dif.x + dif.y * dif.y <= radius * radius;
	}
}