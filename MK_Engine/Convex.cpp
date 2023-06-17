#include "Convex.h"
#include "Math.h"

namespace mk
{
	Convex::Convex(Object* _gameObject) 
	{
		gameObject = _gameObject;
		setVertices({sf::Vector2f(0,0), sf::Vector2f(10,0), sf::Vector2f(10,10), sf::Vector2f(0,10)});
		listOfShapes.push_back(this);
	}
	void Convex::setVertices(const std::initializer_list < sf::Vector2f >& _verticies, bool doNotCalculateCOM)
	{
		size_t i = 0;
		polygon.setPointCount(_verticies.end() - _verticies.begin());
		transformedVerticies = new sf::Vector2f[polygon.getPointCount()];
		for (auto ver = _verticies.begin(); ver < _verticies.end(); ++ver)
		{
			polygon.setPoint(i, (*ver));
			transformedVerticies[i] = (*ver);
			i++;
		}
		polygon.setPosition(0, 0);
		if(!doNotCalculateCOM) calculateCoM();
		setRotation(0);
	}
	void Convex::calculateCoM()
	{
		//Calculating shape area
		float twoAreas = 0;
		for (int i = 0; i < polygon.getPointCount() - 1; i++)
			twoAreas += (polygon.getPoint(i).x + polygon.getPoint(i + 1).x) * (polygon.getPoint(i + 1).y - polygon.getPoint(i).y);
		
		sf::Vector2f com;
		com = (polygon.getPoint(polygon.getPointCount() - 1) + polygon.getPoint(0)) * (polygon.getPoint(polygon.getPointCount() - 1).x * polygon.getPoint(0).y - polygon.getPoint(0).x * polygon.getPoint(polygon.getPointCount() - 1).y);
		for (int i = 0; i < polygon.getPointCount() - 1; i++)
			com += (polygon.getPoint(i) + polygon.getPoint(i + 1)) * (polygon.getPoint(i).x * polygon.getPoint(i + 1).y - polygon.getPoint(i+1).x * polygon.getPoint(i).y);
		com /= (3 * twoAreas);
		//Setting new verticies
		for (int i = 0; i < polygon.getPointCount(); i++)
			polygon.setPoint(i, polygon.getPoint(i) - com);
	}
	void Convex::setPosition(sf::Vector2f _pos)
	{
		polygon.setPosition(_pos);
	}
	sf::Vector2f Convex::getPosition() const
	{
		return polygon.getPosition();
	}

	void Convex::setRotation(float _rotation)
	{
		polygon.setRotation(_rotation);
		rotationRadians = Math::degToRadians(_rotation);

		//Update transform verticies
		for (int i = 0; i < polygon.getPointCount(); i++)
		{
			transformedVerticies[i] = Math::turnByAngle(polygon.getPoint(i), getRotationRadians());
		}
	}
	float Convex::getRotation() const
	{
		return polygon.getRotation();
	}
	float Convex::getRotationRadians() const
	{
		return rotationRadians;
	}

	sf::Vector2f Convex::getAbsolutePosition(size_t _index) const
	{
		return polygon.getPosition() + transformedVerticies[_index];
	}
	void Convex::setColor(sf::Color _color)
	{
		polygon.setFillColor(_color);
	}
	void Convex::draw(sf::RenderWindow& _window)
	{
		_window.draw(polygon);
	}
}